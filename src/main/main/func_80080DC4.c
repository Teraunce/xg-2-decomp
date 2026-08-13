#include "ultra64.h"

/*
 * audioSeqUpdate — per-frame MIDI sequence node update dispatcher.
 * PERMANENTLY NONMATCHING — dispatches via jr through jtbl_8004CDF0 (24 entries).
 * Sibling of audioNodeUpdate (func_8007F5C4); same outer loop, same s5/sp50 layout.
 *
 * Register map:
 *   s2  = obj
 *   s5  = obj + 0x48   (pkt base; a0 for osStopTimer/osSetTimer)
 *   sp+0x50 = &obj->0x38  (a1 for osStopTimer; also passed as timer cmd buffer)
 *
 * Epilogue (shared by all cases):
 *   result = osStopTimer(s5, sp+0x50);
 *   obj->0x28 = result always;
 *   if result == 0: loop back to top;
 *   else: obj->0x1C += result; return.
 */

void  midiDecodeEvent(Unk *seq, Unk *buf);
void  audioRspDispatch(Unk *cmd, Unk *node);
void  audioStreamTick(Unk *obj);
void  midiProcessTempo(Unk *cmd, Unk *obj);
void  osSetTimer(void **ctx, s32 cmdBuf, s32 value);
s32   osStopTimer(Unk *ctx, s16 *cmdBuf);
void  sfxPlayNoteAtEntity(Unk *obj, Unk *node);
void  sfxStopAtEntity(Unk *obj, Unk *node);
void  audioNoteRelease(Unk *obj, Unk *note);
void  audioNoteUnlink(Unk *obj, Unk *buf);
s16   sfxComputeVolume(Unk *note, Unk *obj);
void  sfxPlayAtEntity(Unk *obj, Unk *buf, s16 vol, s32 ticks);
void  audioLoadNotes(Unk *obj, Unk *seq);
void  timerRelinkByType(Unk *ctx, s32 type);
u8    audioNoteActivate(Unk *obj, Unk *buf, s32 arg2);
void  sfxNoteRetrigger(Unk *obj, Unk *buf, s32 arg2);
void  sfxPlayLoopAtEntity(Unk *obj, Unk *buf, f32 vol);

extern f32 gTempoDurConst;  /* 0x8004CE50: float constant for tempo duration calc */

/* nonmatching: jtbl_8004CDF0 switch (permanently) */
void audioSeqUpdate(Unk *obj) {
    Unk  *ctx  = (Unk *)((u8 *)obj + 0x48);    /* s5 */
    s16  *sp50 = (s16 *)((u8 *)obj + 0x38);    /* sp+0x50: timer cmd buf / loop ptr */

    /* Stack cmd buffers for osSetTimer calls */
    s16   cmd88;        /* sp+0x88: midiDecodeEvent output / cmd */
    s16   cmdBC;        /* sp+0xBC: outgoing timer command short */
    Unk  *pktC0;        /* sp+0xC0: node ptr in timer packet */
    Unk  *pktC4;        /* sp+0xC4: voice ptr in timer packet */
    u8    pktC8;        /* sp+0xC8: channel index in timer packet */
    f32   stkA8;        /* sp+0xA8: float output from fn-ptr call */

    s32   result;

    while (1) {
        u16 type = *(u16 *)((u8 *)obj + 0x38);
        if (type >= 0x18) {
            goto epilogue;
        }

        switch (type) {

        case 0: {
            /* Decode next MIDI event from obj->0x18 sequence pointer. */
            Unk *seq = *(Unk **)((u8 *)obj + 0x18);
            if (seq == NULL) {
                goto epilogue;
            }
            midiDecodeEvent(seq, (Unk *)&cmd88);
            {
                s16 ev = cmd88;
                if (ev == 1) {
                    /* audioRspDispatch on the decoded cmd buffer, then tick. */
                    audioRspDispatch((Unk *)&cmd88, (Unk *)&cmd88);
                    audioStreamTick(obj);
                } else if (ev == 3) {
                    /* Tempo change: process tempo then tick. */
                    midiProcessTempo((Unk *)&cmd88, obj);
                    audioStreamTick(obj);
                } else if (ev == 4) {
                    /* Pause: enter state 2 and arm a max-duration timer. */
                    *(s32 *)((u8 *)obj + 0x2C) = 2;
                    cmd88 = 0x10;
                    osSetTimer((void **)ctx, (s32)&cmd88, 0x7FFFFFFF);
                }
                /* ev not in {1,3,4}: no-op, fall to epilogue */
            }
            break;
        }

        case 2: {
            /* RSP dispatch using the stored obj+0x38 command buffer. */
            audioRspDispatch((Unk *)sp50, NULL);
            goto epilogue_s5;
        }

        case 5: {
            /* Teardown single note: play/stop, optionally release, then unlink. */
            Unk *node = *(Unk **)((u8 *)obj + 0x3C);
            Unk *note = *(Unk **)((u8 *)node + 0x10);
            sfxPlayNoteAtEntity(*(Unk **)((u8 *)obj + 0x14), node);
            sfxStopAtEntity(*(Unk **)((u8 *)obj + 0x14), node);
            if (*(u8 *)((u8 *)note + 0x37) != 0) {
                audioNoteRelease(obj, note);
            }
            audioNoteUnlink(obj, node);
            break;
        }

        case 6: {
            /* Begin playing a note: set up initial state and submit to SFX. */
            Unk *node  = *(Unk **)((u8 *)obj + 0x3C);
            Unk *note  = *(Unk **)((u8 *)node + 0x10);
            s32  ticks = *(s32 *)((u8 *)obj + 0x40);
            s16  vol;
            if (*(u8 *)((u8 *)note + 0x34) == 0) {
                *(u8 *)((u8 *)note + 0x34) = 1;
            }
            *(u8 *)((u8 *)note + 0x30) = *(u8 *)((u8 *)obj + 0x44);
            *(s32 *)((u8 *)note + 0x24) = *(s32 *)((u8 *)obj + 0x1C) + ticks;
            vol = sfxComputeVolume(note, obj);
            sfxPlayAtEntity(*(Unk **)((u8 *)obj + 0x14), node, vol, ticks);
            break;
        }

        case 7: {
            /* Tempo command from stored timer buffer. */
            midiProcessTempo((Unk *)sp50, obj);
            break;
        }

        case 9: {
            /* Set timer with cmd=9 and obj->0x5C as tick count. */
            cmdBC = 9;
            osSetTimer((void **)ctx, (s32)&cmdBC, *(s32 *)((u8 *)obj + 0x5C));
            break;
        }

        case 0xA: {
            /* Walk linked note list; play each with volume/progress. */
            Unk *node = *(Unk **)((u8 *)obj + 0x64);
            *(s16 *)((u8 *)obj + 0x32) = *(s16 *)((u8 *)obj + 0x3C);
            if (node == NULL) {
                goto epilogue_s5;
            }
            do {
                Unk *buf  = (Unk *)((u8 *)node + 4);
                s32  diff = *(s32 *)((u8 *)node + 0x24) - *(s32 *)((u8 *)obj + 0x1C);
                s32  prog = (diff < 0) ? 0x3E8 : diff;
                s16  vol  = sfxComputeVolume(node, obj);
                sfxPlayAtEntity(*(Unk **)((u8 *)obj + 0x14), buf, vol, prog);
                node = *(Unk **)((u8 *)node + 0x0);
            } while (node != NULL);
            break;
        }

        case 0xB: {
            /* Snapshot obj->0x3C/0x40/0x44 into obj->0x7C/0x80/0x84. */
            *(s32 *)((u8 *)obj + 0x7C) = *(s32 *)((u8 *)obj + 0x3C);
            *(s32 *)((u8 *)obj + 0x80) = *(s32 *)((u8 *)obj + 0x40);
            *(s32 *)((u8 *)obj + 0x84) = *(s32 *)((u8 *)obj + 0x44);
            goto epilogue_s5;
        }

        case 0xC: {
            /* Write channel byte into wavetable slot. */
            u8   idx = *(u8 *)((u8 *)obj + 0x3C);
            u8   val = *(u8 *)((u8 *)obj + 0x3D);
            Unk *tbl = *(Unk **)((u8 *)obj + 0x60);
            *(u8 *)((u8 *)tbl + idx * 16 + 8) = val;
            goto epilogue_s5;
        }

        case 0xD: {
            /* Assign new sequence source and compute event duration. */
            Unk *seq = *(Unk **)((u8 *)obj + 0x3C);
            *(Unk **)((u8 *)obj + 0x18) = seq;
            if (seq != NULL) {
                *(s32 *)((u8 *)obj + 0x24) = (s32)(gTempoDurConst * *(f32 *)((u8 *)seq + 0x14));
            } else {
                *(s32 *)((u8 *)obj + 0x24) = 0x1E8;
            }
            if (*(Unk **)((u8 *)obj + 0x20) != NULL) {
                audioLoadNotes(obj, NULL);
            }
            break;
        }

        case 0xE: {
            /* Set obj->0x20 = obj->0x3C and load notes from new source. */
            Unk *seq = *(Unk **)((u8 *)obj + 0x3C);
            *(Unk **)((u8 *)obj + 0x20) = seq;
            audioLoadNotes(obj, seq);
            break;
        }

        case 0xF: {
            /* Initiate playback: if already in state 1 re-loop, else enter state 1 and tick. */
            if (*(s32 *)((u8 *)obj + 0x2C) == 1) {
                goto epilogue_s5;
            }
            *(s32 *)((u8 *)obj + 0x2C) = 1;
            audioStreamTick(obj);
            break;
        }

        case 0x10: {
            /* State 2 → teardown: unlink all notes in chain, reset state/tick-count. */
            Unk *node;
            if (*(s32 *)((u8 *)obj + 0x2C) != 2) {
                break;
            }
            node = *(Unk **)((u8 *)obj + 0x64);
            while (node != NULL) {
                Unk *buf  = (Unk *)((u8 *)node + 4);
                Unk *note = node;
                sfxPlayNoteAtEntity(*(Unk **)((u8 *)obj + 0x14), buf);
                sfxStopAtEntity(*(Unk **)((u8 *)obj + 0x14), buf);
                if (*(u8 *)((u8 *)note + 0x37) != 0) {
                    audioNoteRelease(obj, note);
                }
                audioNoteUnlink(obj, buf);
                node = *(Unk **)((u8 *)obj + 0x64); /* reload head after unlink */
            }
            *(s32 *)((u8 *)obj + 0x1C) = 0;
            *(s32 *)((u8 *)obj + 0x2C) = 0;
            goto epilogue_s5;
        }

        case 0x11: {
            /* State 1 → activate: relink timers, activate all notes, enter state 2 + timer. */
            Unk *node;
            if (*(s32 *)((u8 *)obj + 0x2C) != 1) {
                break;
            }
            timerRelinkByType(ctx, 0);
            timerRelinkByType(ctx, 2);
            node = *(Unk **)((u8 *)obj + 0x64);
            while (node != NULL) {
                Unk *buf = (Unk *)((u8 *)node + 4);
                if (audioNoteActivate(obj, buf, 0xC350)) {
                    sfxNoteRetrigger(obj, buf, 0xC350);
                }
                node = *(Unk **)((u8 *)node + 0x0);
            }
            *(s32 *)((u8 *)obj + 0x2C) = 2;
            cmdBC = 0x10;
            osSetTimer((void **)ctx, (s32)&cmdBC, 0x7FFFFFFF);
            break;
        }

        case 0x16: {
            /*
             * Pitch-driven playback: call fn-ptr for pitch, saturate to s8,
             * compute volume, submit note, then set repeating timer.
             *
             * The f32→s8 saturation is an IDO-style cvt.w.s with overflow
             * handling (values ≥ 2^31 → 0x80000000; infinite overflow → -1).
             * Simplified here as a direct cast.
             */
            s32 (*fn)(Unk *, Unk *) = *(s32(**)(Unk *, Unk *))((u8 *)obj + 0x74);
            Unk *voice = *(Unk **)((u8 *)obj + 0x40);
            Unk *node  = *(Unk **)((u8 *)obj + 0x3C);
            Unk *buf   = (Unk *)((u8 *)node + 4);
            s32  ret   = fn(voice, (Unk *)&stkA8);
            s32  diff, prog;
            s16  vol;
            *(s8 *)((u8 *)node + 0x36) = (s8)(s32)stkA8; /* saturating f32→s8 */
            vol  = sfxComputeVolume(node, obj);
            diff = *(s32 *)((u8 *)node + 0x24) - *(s32 *)((u8 *)obj + 0x1C);
            prog = (diff < 0) ? 0x3E8 : diff;
            sfxPlayAtEntity(*(Unk **)((u8 *)obj + 0x14), buf, vol, prog);
            cmdBC = 0x16;
            pktC0 = node;
            pktC4 = voice;
            osSetTimer((void **)ctx, (s32)&cmdBC, ret);
            break;
        }

        case 0x17: {
            /*
             * Loop-volume playback: call fn-ptr for amplitude, store to note,
             * multiply by wavetable entry, submit loop sample, then set timer.
             */
            s32 (*fn)(Unk *, Unk *) = *(s32(**)(Unk *, Unk *))((u8 *)obj + 0x74);
            Unk *voice = *(Unk **)((u8 *)obj + 0x40);
            Unk *node  = *(Unk **)((u8 *)obj + 0x3C);
            u8   chan  = *(u8  *)((u8 *)obj + 0x44);
            Unk *buf   = (Unk *)((u8 *)node + 4);
            Unk *tbl   = *(Unk **)((u8 *)obj + 0x60);
            f32  tblvol, amp;
            s32  ret   = fn(voice, (Unk *)&stkA8);
            *(f32 *)((u8 *)node + 0x2C) = stkA8;
            amp    = *(f32 *)((u8 *)node + 0x28) * *(f32 *)((u8 *)node + 0x2C);
            tblvol = *(f32 *)((u8 *)tbl + chan * 16 + 0xC);
            sfxPlayLoopAtEntity(*(Unk **)((u8 *)obj + 0x14), buf, tblvol * amp);
            cmdBC = 0x17;
            pktC0 = node;
            pktC4 = voice;
            pktC8 = chan;
            osSetTimer((void **)ctx, (s32)&cmdBC, ret);
            break;
        }

        default:
            break;
        }

epilogue:
epilogue_s5:
        result = osStopTimer(ctx, sp50);
        *(s32 *)((u8 *)obj + 0x28) = result;
        if (result == 0) {
            continue;
        }
        *(s32 *)((u8 *)obj + 0x1C) += result;
        return;
    }
}
