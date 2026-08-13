#include "ultra64.h"

/*
 * audioRspDispatchNode — MIDI event handler / audio note dispatcher.
 *
 * PERMANENTLY NONMATCHING — two reasons:
 *   1. Non-standard ABI: $t0 = MIDI event ptr (ev), $s2 = audio ctx (ctx).
 *      No C compiler generates code that reads $t0/$s2 as implicit inputs.
 *   2. jtbl_8004C9D8 jump table (jr $t7); m2c marks all such functions nonmatching.
 *
 * Rewritten as audioRspDispatchNode(ev, ctx) for readability.
 * Dispatches on (ev->status & 0xF0):
 *   0x80 Note Off, 0x90 Note On, 0xA0 Aftertouch,
 *   0xB0 Control Change, 0xC0 Program Change,
 *   0xD0 Channel Pressure, 0xE0 Pitch Bend.
 */

f32   audioSemitoneRatio(s16 cents);
s32   sfxNoteAssign(Unk *arg0, Unk *arg1, Unk *arg2);
void  sfxNoteRetrigger(Unk *ctx, Unk *buf, s32 arg2);
void  sfxNotePlay(Unk *arg0, Unk *arg1, s32 arg2, f32 arg3, s16 arg4, u8 arg5, u8 arg6, s32 arg7);
char *audioNoteLookup(Unk *ctx, s32 note_num, s32 chan);
Unk  *audioBankLookup(Unk *ctx, s32 note_num, s32 velocity, s32 chan);
Unk  *audioNoteFind(Unk *ctx, s32 note_num, s32 velocity, s32 chan);
s16   sfxComputePan(Unk *note, Unk *ctx);
s16   sfxComputeVolume(Unk *note, Unk *ctx);
s32   sfxComputeDist(Unk *note, Unk *sfx_obj);
void  sfxPlayAtEntity(Unk *obj, Unk *buf, s16 vol, s32 ticks);
void  sfxPlayPanAtEntity(Unk *obj, Unk *buf, u8 pan);
void  sfxPlayAbsAtEntity(Unk *obj, Unk *buf, s32 val);
void  sfxPlayLoopAtEntity(Unk *obj, Unk *buf, f32 vol);
void  audioSetNoteSlot(Unk *ctx, Unk *slot_entry, s32 chan);
void  osSetTimer(void **ctx, s32 cmdBuf, s32 value);

/* nonmatching: non-standard ABI ($t0/$s2) + jtbl_8004C9D8 (permanently) */
void audioRspDispatchNode(Unk *ev, Unk *ctx) {
    u8  status  = *(u8 *)((u8 *)ev + 0x8);
    u8  data1   = *(u8 *)((u8 *)ev + 0x9);
    u8  data2   = *(u8 *)((u8 *)ev + 0xA);
    u8  chan    = status & 0xF;
    u8  msg     = status & 0xF0;
    u32 msg_idx = msg - 0x80;

    /* Stack cmd buffers for osSetTimer packets */
    s16  cmd8C;          /* sp+0x8C: timer cmd type */
    Unk *cmd90;          /* sp+0x90: note ptr in timer packet */
    u8   cmd94;          /* sp+0x94: midi byte in packet */
    u8   cmd95;          /* sp+0x95: note num in packet */
    u8   cmd96;          /* sp+0x96: pad */
    Unk *cmd98;          /* sp+0x98: field in timer packet */

    Unk  *note, *note_buf;
    Unk  *voice, *wavetable_chan;
    s16   vol, pan_s16;
    u8    pan;
    s32   dist;

    if (msg_idx >= 0x61) {
        return;
    }

    switch (msg) {

    case 0x90: {
        /*
         * Note On: velocity==0 is treated as Note Off.
         * Allocates a voice slot, finds/assigns a note slot, computes pitch/volume,
         * sets up optional pitch+amplitude envelopes, then submits to sfxNotePlay.
         */
        Unk *wt_entry;
        Unk *note_slot;
        u8   wt_byte, sustain_flag, wt_pan;
        f32  amplitude;
        f32  pitch_vol_amp;
        s16  vol_computed;

        /* cmd buf at sp+0x74 for sfxNoteAssign */
        s16  cmd74[4];

        if (data2 == 0) {
            /* velocity 0 = Note Off */
            goto note_off;
        }

        if (*(s32 *)((u8 *)ctx + 0x2C) != 1) {
            return;
        }

        /* Allocate voice from bank */
        voice = audioBankLookup(ctx, data1 & 0xFF, data2 & 0xFF, chan & 0xFF);
        if (voice == NULL) {
            return;
        }

        /* Load wavetable cmd byte for this channel */
        wavetable_chan = (Unk *)((u8 *)(*(Unk **)((u8 *)ctx + 0x60)) + chan * 16);
        wt_byte = *(u8 *)((u8 *)wavetable_chan + 0x8);
        cmd74[0] = 0;
        *(u8 *)((u8 *)cmd74 + 2) = 0;
        cmd74[2] = (s16)wt_byte;  /* store wavetable byte at sp+0x74 */

        /* Find or allocate a note slot */
        note = audioNoteFind(ctx, data1 & 0xFF, data2 & 0xFF, chan & 0xFF);
        if (note == NULL) {
            return;
        }
        note_buf = (Unk *)((u8 *)note + 4);

        /* Register the note with the SFX system */
        sfxNoteAssign(*(Unk **)((u8 *)ctx + 0x14), note_buf, (Unk *)cmd74);

        /* Initialize note state */
        *(Unk **)((u8 *)note + 0x20) = voice;
        *(u8  *)((u8 *)note + 0x34) = 0;

        /* Set note->0x35 (sustain state) based on wavetable[chan].0xB */
        sustain_flag = *(u8 *)((u8 *)(*(Unk **)((u8 *)ctx + 0x60)) + chan * 16 + 0xB);
        *(u8 *)((u8 *)note + 0x35) = (sustain_flag < 0x40) ? 0 : 2;

        /* Compute pitch: semitone offset in cents from voice root note + transpose */
        {
            Unk *voice_sub = *(Unk **)((u8 *)voice + 0x4);
            u8   root_note = *(u8  *)((u8 *)voice_sub + 0x4);
            s8   transpose = *(s8  *)((u8 *)voice_sub + 0x5);
            s16  cents     = (s16)((data1 - root_note) * 100 + transpose);
            *(f32 *)((u8 *)note + 0x28) = audioSemitoneRatio(cents);
        }

        /* Copy instrument byte from voice, set duration base, clear flags */
        {
            Unk *voice_base = *(Unk **)((u8 *)voice + 0x0);
            Unk *voice_data = *(Unk **)voice_base;
            *(u8 *)((u8 *)note + 0x30) = *(u8 *)((u8 *)voice_base + 0xC);
            *(u8 *)((u8 *)note + 0x37) = 0;
            *(s32 *)((u8 *)note + 0x24) = *(s32 *)((u8 *)ctx + 0x1C) + *(s32 *)voice_data;
        }

        /* Optional pitch envelope: call fn ptr at ctx->0x70 with s1->0x4..0x7 */
        amplitude = 127.0f;
        {
            Unk *wt_ptr = *(Unk **)((u8 *)(*(Unk **)((u8 *)ctx + 0x60)) + chan * 16);
            Unk *env_fn_ptr = *(Unk **)((u8 *)ctx + 0x70);
            u8   pitch_use = *(u8 *)((u8 *)wt_ptr + 0x4);

            if (pitch_use != 0 && env_fn_ptr != NULL) {
                s32 (*env_fn)(Unk *, f32 *, u8, u8, u8) =
                    (s32(*)(Unk *, f32 *, u8, u8, u8))env_fn_ptr;
                s32  timer_val;
                Unk *timer_out_ptr;  /* sp+0x5C */
                u8   p5 = *(u8 *)((u8 *)wt_ptr + 0x5);
                u8   p6 = *(u8 *)((u8 *)wt_ptr + 0x6);
                u8   p7 = *(u8 *)((u8 *)wt_ptr + 0x7);
                timer_val = env_fn((Unk *)&timer_out_ptr, &amplitude, p5, p6, p7);
                if (timer_val != 0) {
                    cmd8C = 0x16;
                    cmd90 = note;
                    cmd98 = (Unk *)(uintptr_t)(s32)timer_out_ptr;
                    osSetTimer((void **)((u8 *)ctx + 0x48), (s32)&cmd8C, timer_val);
                    *(u8 *)((u8 *)note + 0x37) |= 1;
                }
            }
        }

        /* Optional amplitude envelope: same fn ptr, bytes 0x8..0xB */
        {
            Unk *wt_ptr = *(Unk **)((u8 *)(*(Unk **)((u8 *)ctx + 0x60)) + chan * 16);
            Unk *env_fn_ptr = *(Unk **)((u8 *)ctx + 0x70);
            u8   amp_use = *(u8 *)((u8 *)wt_ptr + 0x8);

            if (amp_use != 0 && env_fn_ptr != NULL) {
                s32 (*env_fn)(Unk *, f32 *, u8, u8, u8) =
                    (s32(*)(Unk *, f32 *, u8, u8, u8))env_fn_ptr;
                s32  timer_val;
                Unk *timer_out_ptr;
                u8   p9  = *(u8 *)((u8 *)wt_ptr + 0x9);
                u8   pA  = *(u8 *)((u8 *)wt_ptr + 0xA);
                u8   pB  = *(u8 *)((u8 *)wt_ptr + 0xB);
                timer_val = env_fn((Unk *)&timer_out_ptr, &amplitude, p9, pA, pB);
                if (timer_val != 0) {
                    cmd8C = 0x17;
                    cmd90 = note;
                    cmd94 = (u8)chan;
                    cmd98 = (Unk *)(uintptr_t)(s32)timer_out_ptr;
                    osSetTimer((void **)((u8 *)ctx + 0x48), (s32)&cmd8C, timer_val);
                    *(u8 *)((u8 *)note + 0x37) |= 2;
                }
            }
        }

        /* Store amplitude, compute pitch*vol_scale*amplitude composite */
        *(f32 *)((u8 *)note + 0x2C) = amplitude;
        {
            Unk *chan_slot = (Unk *)((u8 *)(*(Unk **)((u8 *)ctx + 0x60)) + chan * 16);
            f32  vol_scale = *(f32 *)((u8 *)chan_slot + 0xC);
            f32  pitch     = *(f32 *)((u8 *)note + 0x28);
            f32  amp       = *(f32 *)((u8 *)note + 0x2C);
            pitch_vol_amp  = vol_scale * pitch * amp;
            wt_pan         = *(u8  *)((u8 *)chan_slot + 0xA);
        }

        /* Compute pan and volume for initial playback */
        pan_s16 = sfxComputePan(note, ctx);
        pan     = (u8)(pan_s16 & 0xFF);
        vol_computed = sfxComputeVolume(note, ctx);

        /* Submit note to the audio/SFX engine */
        {
            Unk *voice_base = *(Unk **)((u8 *)voice + 0x0);
            Unk *voice_data = *(Unk **)voice_base;
            sfxNotePlay(
                *(Unk **)((u8 *)ctx + 0x14),
                note_buf,
                *(s32 *)((u8 *)voice + 0x8),
                pitch_vol_amp,
                vol_computed,
                pan,
                wt_pan,
                *(s32 *)voice_data
            );

            /* Set repeating timer for this note (cmd 6 = active note tick) */
            cmd8C = 6;
            cmd90 = note_buf;
            cmd94 = *(u8 *)((u8 *)voice_base + 0xD);
            cmd98 = *(Unk **)((u8 *)voice + 0x4);
            osSetTimer((void **)((u8 *)ctx + 0x48), (s32)&cmd8C, *(s32 *)voice_data);
        }

        /* If this event has a follow-up (ev->0xC != 0): schedule note-off */
        {
            Unk *ev_next = *(Unk **)((u8 *)ev + 0xC);
            if (ev_next != NULL) {
                Unk *ev2 = (Unk *)((u8 *)ev + 4);
                s32  duration = *(s32 *)((u8 *)ctx + 0x24) * *(s32 *)((u8 *)ev2 + 0x8);
                cmd8C  = 0x15;
                cmd94  = (u8)(chan | 0x80);
                cmd95  = data1;
                cmd96  = 0;
                osSetTimer((void **)((u8 *)ctx + 0x48), (s32)&cmd8C, duration);
            }
        }
        return;
    }

note_off:
    case 0x80: {
        /*
         * Note Off: find active note, update sustain state.
         * If note->0x35 == 2 (sustained): mark as 4 (pending release), return.
         * Otherwise set state=3 and retrigger release.
         */
        note = (Unk *)audioNoteLookup(ctx, data1 & 0xFF, chan & 0xFF);
        if (note == NULL) {
            return;
        }
        if (*(u8 *)((u8 *)note + 0x35) == 2) {
            *(u8 *)((u8 *)note + 0x35) = 4;
            return;
        }
        {
            Unk *voice_ptr  = *(Unk **)((u8 *)note + 0x20);
            Unk *voice_data = *(Unk **)voice_ptr;
            *(u8 *)((u8 *)note + 0x35) = 3;
            sfxNoteRetrigger(ctx, (Unk *)((u8 *)note + 4), *(s32 *)((u8 *)voice_data + 0x8));
        }
        return;
    }

    case 0xA0: {
        /*
         * Aftertouch (Poly Key Pressure): update note pressure and resubmit volume.
         */
        note = (Unk *)audioNoteLookup(ctx, data1 & 0xFF, chan & 0xFF);
        if (note == NULL) {
            return;
        }
        *(u8 *)((u8 *)note + 0x33) = data2;
        vol = sfxComputeVolume(note, ctx);
        dist = sfxComputeDist(note, *(Unk **)((u8 *)ctx + 0x1C));
        sfxPlayAtEntity(*(Unk **)((u8 *)ctx + 0x14), (Unk *)((u8 *)note + 4),
                        vol, (s32)(s16)dist);
        return;
    }

    case 0xD0: {
        /*
         * Channel Pressure: walk note list, resubmit volume for all notes on channel.
         */
        Unk *nd = *(Unk **)((u8 *)ctx + 0x64);
        if (nd == NULL) {
            return;
        }
        do {
            if (*(u8 *)((u8 *)nd + 0x31) == chan) {
                *(u8 *)((u8 *)nd + 0x33) = data1;
                vol  = sfxComputeVolume(nd, ctx);
                dist = sfxComputeDist(nd, *(Unk **)((u8 *)ctx + 0x1C));
                sfxPlayAtEntity(*(Unk **)((u8 *)ctx + 0x14),
                                (Unk *)((u8 *)nd + 4), vol, (s32)(s16)dist);
            }
            nd = *(Unk **)nd;
        } while (nd != NULL);
        return;
    }

    case 0xB0: {
        /*
         * Control Change — inner switch on data1 (controller number).
         */
        Unk *wt_base = *(Unk **)((u8 *)ctx + 0x60);
        Unk *nd;

        switch (data1) {

        case 0x07: {
            /* Volume: update wavetable volume byte, resubmit all matching notes */
            *(u8 *)((u8 *)wt_base + chan * 16 + 0x9) = data2;
            nd = *(Unk **)((u8 *)ctx + 0x64);
            if (nd == NULL) { return; }
            do {
                if (*(u8 *)((u8 *)nd + 0x31) == chan &&
                    *(u8 *)((u8 *)nd + 0x34) != 3) {
                    vol  = sfxComputeVolume(nd, ctx);
                    dist = sfxComputeDist(nd, *(Unk **)((u8 *)ctx + 0x1C));
                    sfxPlayAtEntity(*(Unk **)((u8 *)ctx + 0x14),
                                    (Unk *)((u8 *)nd + 4), vol, (s32)(s16)dist);
                }
                nd = *(Unk **)nd;
            } while (nd != NULL);
            return;
        }

        case 0x0A: {
            /* Pan: update wavetable pan byte, resubmit pan for all matching notes */
            *(u8 *)((u8 *)wt_base + chan * 16 + 0x7) = data2;
            nd = *(Unk **)((u8 *)ctx + 0x64);
            if (nd == NULL) { return; }
            do {
                if (*(u8 *)((u8 *)nd + 0x31) == chan) {
                    pan_s16 = sfxComputePan(nd, ctx);
                    sfxPlayPanAtEntity(*(Unk **)((u8 *)ctx + 0x14),
                                       (Unk *)((u8 *)nd + 4), (u8)(pan_s16 & 0xFF));
                }
                nd = *(Unk **)nd;
            } while (nd != NULL);
            return;
        }

        case 0x10:
            /* Attack: write to wavetable byte 0x8, no note walk */
            *(u8 *)((u8 *)wt_base + chan * 16 + 0x8) = data2;
            return;

        case 0x40: {
            /*
             * Sustain pedal: update sustain byte, then update state for each
             * matching note based on sustain on/off and current note->0x35.
             *   sustain on  (>= 0x40): note->0x35==0 → set 2 (held)
             *   sustain off (< 0x40):  note->0x35==2 → set 0 (release); ==4 → retrigger
             */
            *(u8 *)((u8 *)wt_base + chan * 16 + 0xB) = data2;
            nd = *(Unk **)((u8 *)ctx + 0x64);
            if (nd == NULL) { return; }
            do {
                if (*(u8 *)((u8 *)nd + 0x31) == chan &&
                    *(u8 *)((u8 *)nd + 0x35) != 3) {
                    u8 state = *(u8 *)((u8 *)nd + 0x35);
                    if (data2 < 0x40) {
                        /* Sustain off */
                        if (state == 2) {
                            *(u8 *)((u8 *)nd + 0x35) = 0;
                        } else if (state == 4) {
                            Unk *vp   = *(Unk **)((u8 *)nd + 0x20);
                            Unk *vd   = *(Unk **)vp;
                            *(u8 *)((u8 *)nd + 0x35) = 3;
                            sfxNoteRetrigger(ctx, (Unk *)((u8 *)nd + 4),
                                             *(s32 *)((u8 *)vd + 0x8));
                        }
                    } else {
                        /* Sustain on */
                        if (state == 0) {
                            *(u8 *)((u8 *)nd + 0x35) = 2;
                        }
                    }
                }
                nd = *(Unk **)nd;
            } while (nd != NULL);
            return;
        }

        case 0x5B: {
            /* Effect depth (reverb): update wavetable byte 0xA, resubmit abs for matching notes */
            *(u8 *)((u8 *)wt_base + chan * 16 + 0xA) = data2;
            nd = *(Unk **)((u8 *)ctx + 0x64);
            if (nd == NULL) { return; }
            do {
                if (*(u8 *)((u8 *)nd + 0x31) == chan) {
                    sfxPlayAbsAtEntity(*(Unk **)((u8 *)ctx + 0x14),
                                       (Unk *)((u8 *)nd + 4), data2 & 0xFF);
                }
                nd = *(Unk **)nd;
            } while (nd != NULL);
            return;
        }

        default:
            return;
        }
    }

    case 0xC0: {
        /*
         * Program Change: look up new wavetable entry, assign to channel if in range.
         */
        Unk *prog_table = *(Unk **)((u8 *)ctx + 0x20);
        s16  prog_count = *(s16 *)prog_table;
        if (data1 >= (u8)prog_count) {
            return;
        }
        {
            Unk *entry = (Unk *)((u8 *)prog_table + data1 * 4);
            audioSetNoteSlot(ctx, *(Unk **)((u8 *)entry + 0xC), chan);
        }
        return;
    }

    case 0xE0: {
        /*
         * Pitch Bend: compute semitone offset from 14-bit bend value,
         * store pitch ratio in wavetable[chan].0xC, resubmit loop for matching notes.
         *
         * Bend value is 14-bit signed: (data2 << 7) + data1 - 8192.
         * Multiplied by bend_range (s16 at wavetable[chan].0x4), then / 8192 = cents.
         */
        Unk *wt_base_e = *(Unk **)((u8 *)ctx + 0x60);
        Unk *chan_slot  = (Unk *)((u8 *)wt_base_e + chan * 16);
        s16  bend_range = *(s16 *)((u8 *)chan_slot + 0x4);
        s32  bend_raw   = (data2 << 7) + data1 - 0x2000;
        s32  bend_cents = ((bend_range * bend_raw) >= 0)
                          ? ((bend_range * bend_raw) >> 13)
                          : ((bend_range * bend_raw + 0x1FFF) >> 13);
        f32  bend_ratio = audioSemitoneRatio((s16)bend_cents);

        /* Store computed bend ratio into the channel wavetable slot */
        *(f32 *)((u8 *)chan_slot + 0xC) = bend_ratio;

        /* Resubmit loop playback for all notes on this channel */
        {
            Unk *nd = *(Unk **)((u8 *)ctx + 0x64);
            if (nd == NULL) { return; }
            do {
                if (*(u8 *)((u8 *)nd + 0x31) == chan) {
                    f32 base_pitch = *(f32 *)((u8 *)nd + 0x28);
                    f32 amp        = *(f32 *)((u8 *)nd + 0x2C);
                    sfxPlayLoopAtEntity(*(Unk **)((u8 *)ctx + 0x14),
                                        (Unk *)((u8 *)nd + 4),
                                        base_pitch * bend_ratio * amp);
                }
                nd = *(Unk **)nd;
            } while (nd != NULL);
        }
        return;
    }

    default:
        return;
    }
}
