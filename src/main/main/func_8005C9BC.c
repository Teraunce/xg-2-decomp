#include "ultra64.h"
#include "render.h"
extern s32 gGameState;
extern s32 gAudioQueueReadIdx;
extern s32 gAudioQueueWriteIdx;
extern s32 gSfxSampleRate;
extern s32 gSfxQueueDepth;
extern s32 gSfxMidiReady;
extern s32 gSfxQueueReady;
extern s32 gAudioQueueState;
extern s32 gSfxGameParams;
extern RenderNode gTrackNodePool[];
extern s32 gRaceMax;
extern s32 gAudioNoteList;
extern s32 gAudioQueueBuf;
extern s32 gSfxAmbientIds;
extern s32 gSfxAmbientParams;
extern s32 gSfxAmbientSlot;
extern s32 gSfxAmbientCount;
extern s32 gSfxAmbientHandle;

/* Audio-frame state globals (0x80092804–0x80092824 cluster, between gAudioStatus and gAudioQueueReadIdx) */
extern s32 gAudioSampleRate;    /* s32 sample-rate factor (integer; cvt.d.w then mul in timing tail) */
extern s32 gAudioBufTarget;    /* audio buffer target size */
extern s32 gAudioBufRunning;    /* audio buffer running size (synced to gAudioBufTarget each tail call) */
extern s32 gAudioDecodeTick;    /* decode-tick counter (incremented by gAudioDecodeInc each cmd-1 tick) */
extern s32 gAudioDecodeDecr;    /* decode-tick decrement per cmd-3 call */
extern s32 gAudioDecodeInc;    /* decode-tick increment per cmd-1 call */
extern s32 gAudioRetryCountdown;    /* retry-countdown (starts 0x2A on cmd-1 overflow; decremented by cmd-2) */
extern s32 gAudioFramePending;    /* pending audio-frame flag (nonzero forces tail to submit task) */

/* Audio mode / DMA globals (BSS pointers, runtime-assigned) */
extern s32 gAudioModeConfig;    /* audio mode config value (passed as arg to RSP setup calls) */
extern s32 gAudioDmaBufBase;    /* audio DMA-buffer table base pointer */
extern s32 gAudioWorkBufA;    /* static work buffer A (passed by address to func_8008E518) */
extern s32 gAudioWorkBufB;    /* static work buffer B */
extern s32 gAudioUcodeBase;    /* audio ucode offset base (pointer into ROM/RDRAM) */

/* f64 timing constants (rodata at 0x8004BE08) */
extern f64 gAudioTimingScale;    /* timing scale factor 1 */
extern f64 gAudioTimingMax;    /* timing upper-clamp bound */
extern f64 gAudioTimingThresh;    /* timing threshold for secondary clamp */

extern s32 gAudioStatus;     /* 0x80092800 — audio FSM state (0=idle,1=init,2=overflow,4=done) */
extern s32 gAudioCallback;   /* 0x80092810 — current callback index; <0 means inactive */
extern s32 gAudioOutputCtx;  /* 0x800927E4 — audio output context handle */

/* extern function prototypes */
void func_8007BA98(s32, s32);
void func_8008E518(void *, s32, s32, s32, s32, s32, void *);
void func_8007CD08(void *, s32, s32);
void func_8007E074(s32, s32);
void func_8007EA68(s32, s32);
void func_8007E5E8(s32);
s32  func_8007E5D8(s32);
void func_8007EAE8(s32);
void func_8007EAA8(s32, s32);

/*
 * audioQueueTail — shared post-dispatch tail (func_8005CBE4 body).
 *
 * If gAudioFramePending == 0 and the buffer sizes already match, returns immediately.
 * Otherwise computes a per-frame timing value from the decode counter and
 * calls func_8007EAA8 to submit the audio RSP task, then resets the flag.
 *
 * This is the code shared by alabel entry points func_8005CBE0 and
 * func_8005CBE4 (both enter at the same C-level logic).
 */
static void audioQueueTail(void) {
    f64 fv1, ft0;
    s16 a1;

    if (gAudioFramePending == 0 && gAudioBufTarget == gAudioBufRunning) {
        return;
    }

    /* Compute timing: decode_count * scale1 * sample_factor * buf_size */
    fv1 = (f64)(s32)gAudioDecodeTick * gAudioTimingScale;
    fv1 = (f64)(s32)gAudioSampleRate * fv1;
    fv1 = fv1 * (f64)(s32)gAudioBufTarget;

    ft0 = fv1 * gAudioTimingMax;
    if (!(ft0 <= gAudioTimingThresh)) {
        ft0 = gAudioTimingThresh; /* clamp to upper bound */
    }

    if (ft0 <= 0.0) {
        a1 = 0;
    } else {
        fv1 = fv1 * gAudioTimingMax;
        if (!(fv1 <= gAudioTimingThresh)) {
            fv1 = gAudioTimingThresh;
        }
        a1 = (s16)(s32)fv1;
    }

    func_8007EAA8(gAudioOutputCtx, (s32)a1);
    gAudioFramePending = 0;
    gAudioBufRunning = gAudioBufTarget;
}

/*
 * func_8005CBB0 — alabel entry: set pending flag then run tail.
 * Referenced in jump tables (jtbl_8004BDF0) and branched to from cases 1, 3.
 */
void func_8005CBB0(void) {
    gAudioFramePending = 1;
    audioQueueTail();
}

/* func_8005CBE0 / func_8005CBE4 — alabel entries: plain tail (no state pre-set).
 * Both enter the same C logic; the single-instruction ABI difference between
 * them (one lui before the lw of gAudioFramePending) is invisible at C level. */
void func_8005CBE0(void) { audioQueueTail(); }
void func_8005CBE4(void) { audioQueueTail(); }

/*
 * audioQueueDispatch — audio frame state-machine dispatcher (0x324 bytes).
 *
 * Original function receives cmd in $v1 (SN64 non-standard ABI).
 * Rewritten with cmd as a normal first argument ($a0).
 * All callers must be updated to pass cmd in the first argument position.
 *
 * Jump table jtbl_8004BDF0 (5 entries): cmd maps 0..4 to the 5 cases below.
 * Out-of-range cmd (>= 5) falls through to the shared tail.
 *
 * cmd 0: Initialize audio DMA — look up mode entry, alloc buffers, kick AI/RSP.
 * cmd 1: Increment decode-tick counter; on overflow set gAudioStatus=2, arm retry.
 * cmd 2: Countdown; on expire poll RSP via func_8007E5D8, update state.
 * cmd 3: Decrement tick counter; when zero call func_8007EAE8, set gAudioStatus=4.
 * cmd 4: Poll RSP done; on success clear gAudioStatus.
 */
void audioQueueDispatch(s32 cmd) {
    s32 temp_v0, temp_v1;
    Unk *entry;
    s32 bufSize, bufOffset;

    if ((u32)cmd >= 5U) {
        audioQueueTail();
        return;
    }

    switch (cmd) {
    case 0: {
        /* Initialize audio frame: look up mode entry by callback index, set up DMA */
        s32 sp14, sp18;
        if (gAudioCallback < 0) {
            audioQueueTail();
            return;
        }
        entry   = (Unk*)(gAudioDmaBufBase + gAudioCallback * 16);
        bufSize = (entry->unk8 + 7) & ~7;
        bufOffset = gAudioUcodeBase + entry->unk0;

        sp14 = bufSize;
        func_8007BA98(bufSize, 0);

        sp18 = (s32)&gAudioWorkBufB;
        func_8008E518((void*)&gAudioWorkBufA, 0, 0, bufOffset,
                      gAudioModeConfig, sp14, (void*)&gAudioWorkBufB);
        func_8007CD08((void*)&gAudioWorkBufB, 0, 1);
        func_8007E074(gAudioQueueBuf, gAudioModeConfig);
        func_8007EA68(gAudioOutputCtx, gAudioQueueBuf);
        func_8007E5E8(gAudioOutputCtx);

        gAudioBufRunning  = 0x100;
        gAudioBufTarget  = 0x100;
        gAudioDecodeTick  = 0;
        gAudioStatus = 1;
        gAudioFramePending  = 1;
        audioQueueTail();
        return;
    }

    case 1:
        /* Increment decode-tick counter; overflow check */
        temp_v1 = gAudioDecodeTick + gAudioDecodeInc;
        if (temp_v1 <= 0xFFFF) {
            gAudioDecodeTick = temp_v1;
        } else {
            gAudioStatus = 2;
            gAudioDecodeTick = 0x10000;
            gAudioRetryCountdown = 0x2A;
        }
        func_8005CBB0();
        return;

    case 2:
        /* Countdown delay; on expire poll RSP done */
        temp_v0 = gAudioRetryCountdown;
        if (temp_v0 != 0) {
            gAudioRetryCountdown = temp_v0 - 1;
            audioQueueTail();
            return;
        }
        temp_v0 = func_8007E5D8(gAudioOutputCtx);
        if (temp_v0 != 0) {
            audioQueueTail();
            return;
        }
        if (gAudioCallback != 0x11) {
            gAudioStatus = 0;
        }
        audioQueueTail();
        return;

    case 3:
        /* Decrement decode counter; when exhausted, RSP done */
        temp_v1 = gAudioDecodeTick - gAudioDecodeDecr;
        gAudioDecodeTick = temp_v1;
        if (temp_v1 > 0) {
            func_8005CBB0();
            return;
        }
        func_8007EAE8(gAudioOutputCtx);
        gAudioStatus = 4;
        gAudioDecodeTick = 0;
        func_8005CBB0();
        return;

    case 4:
        /* Poll RSP done */
        temp_v0 = func_8007E5D8(gAudioOutputCtx);
        if (temp_v0 != 0) {
            audioQueueTail();
            return;
        }
        gAudioStatus = 0;
        audioQueueTail();
        return;
    }
}

s32 sfxQueueCmd(s16 arg0, f32 arg1, s32 arg2, s8 arg3, s32 arg4) {
    s32 temp_a0;
    s32 temp_v0;
    s32 var_t0;
    Unk *temp_v1;

    var_t0 = gAudioQueueWriteIdx + 1;
    if (var_t0 >= 0x80) {
        var_t0 = 0;
    }
    if (var_t0 == gAudioQueueReadIdx) {
        return 0;
    }
    temp_a0 = gAudioQueueState;
    temp_v0 = temp_a0 + 1;
    gAudioQueueState = temp_v0;
    if (temp_v0 <= 0) {
        gAudioQueueState = 1;
    }
    temp_v1 = (gAudioQueueWriteIdx * 0x14) + &gAudioQueueBuf;
    temp_v1->unk10 = arg3;
    temp_v1->unk0 = temp_a0;
    temp_v1->unk4 = 1;
    temp_v1->unk6 = arg0;
    temp_v1->unk8 = arg1;
    temp_v1->unkC = arg2;
    ((Unk*)((char*)&gAudioQueueBuf + gAudioQueueWriteIdx * 0x14))->unk11 = (s8) arg4;
    gAudioQueueWriteIdx = var_t0;
    return temp_a0;
}

void audioQueuePlay(s32 arg0, f32 arg1, s32 arg2, s8 arg3, s32 arg4) {
    s32 var_t0;
    Unk *temp_v0;

    var_t0 = gAudioQueueWriteIdx + 1;
    if (var_t0 >= 0x80) {
        var_t0 = 0;
    }
    if (var_t0 != gAudioQueueReadIdx) {
        temp_v0 = (gAudioQueueWriteIdx * 0x14) + &gAudioQueueBuf;
        temp_v0->unk10 = arg3;
        temp_v0->unk0 = arg0;
        temp_v0->unk4 = 2;
        temp_v0->unk8 = arg1;
        temp_v0->unkC = arg2;
        ((Unk*)((char*)&gAudioQueueBuf + gAudioQueueWriteIdx * 0x14))->unk11 = (s8) arg4;
        gAudioQueueWriteIdx = var_t0;
    }
}

void audioQueueStop(s32 arg0) {
    s32 var_a2;
    Unk *temp_v1;

    var_a2 = gAudioQueueWriteIdx + 1;
    if (var_a2 >= 0x80) {
        var_a2 = 0;
    }
    if (var_a2 != gAudioQueueReadIdx) {
        temp_v1 = (gAudioQueueWriteIdx * 0x14) + &gAudioQueueBuf;
        temp_v1->unk0 = arg0;
        temp_v1->unk4 = 3;
        gAudioQueueWriteIdx = var_a2;
    }
}

s32 audioQueueFind(s32 arg0, f32 *arg1, s32 *arg2, s32 *arg3) {
    Unk *var_v1;
    s32 var_t0;
    s32 var_t0_2;
    s32 var_t0_3;

    var_t0 = 0;
    var_v1 = &gAudioNoteList;
loop_1:
    if (var_v1->unk0 != arg0) {
        var_t0 += 1;
        goto block_14;
    }
    if (var_v1->unk4 != 1) {
        var_t0 += 1;
block_14:
        var_v1 += 0x14;
        if (var_t0 >= 0x1C) {
            var_t0_2 = gAudioQueueReadIdx;
            if (var_t0_2 != gAudioQueueWriteIdx) {
                var_v1 = (var_t0_2 * 0x14) + &gAudioQueueBuf;
loop_17:
                if ((var_v1->unk0 != arg0) || (var_v1->unk4 != 1)) {
                    var_t0_2 += 1;
                    var_v1 += 0x14;
                    if (var_t0_2 >= 0x80) {
                        var_v1 = &gAudioQueueBuf;
                        var_t0_2 = 0;
                    }
                    if (var_t0_2 == gAudioQueueWriteIdx) {
                        goto block_22;
                    }
                    goto loop_17;
                }
                goto block_7;
            }
block_22:
            var_t0_3 = 0;
            var_v1 = &gAudioNoteList;
loop_23:
            if ((var_v1->unk0 != arg0) || (var_v1->unk4 != 1)) {
                var_t0_3 += 1;
                var_v1 += 0x14;
                if (var_t0_3 >= 0x1C) {
                    return 0;
                }
                goto loop_23;
            }
            goto block_7;
        }
        goto loop_1;
    }
block_7:
    if (arg1 != NULL) {
        *arg1 = var_v1->unk8;
    }
    if (arg2 != NULL) {
        *arg2 = var_v1->unkC;
    }
    if (arg3 != NULL) {
        *arg3 = (s32) var_v1->unk10;
    }
    return arg0;
}

void audioSetChanA(s32 arg0) {
    gSfxSampleRate = arg0;
    gSfxMidiReady = 1;
}

void audioSetChanB(s32 arg0) {
    gSfxQueueDepth = arg0;
    gSfxMidiReady = 1;
}

void func_8005CFB4(void) {
    gSfxQueueReady = 1;
}

void func_8005CFC4(void) {
    gSfxAmbientSlot = 0;
    gSfxAmbientCount = 0;
    gSfxAmbientHandle = 0;
}

void func_8005CFE0(s32 arg0, s32 arg1) {
    s32 temp_v1;
    s32 var_a0;
    s32 var_a2;

    var_a2 = 0x40;
    if ((gSfxQueueDepth > 0) && (arg1 < gRaceMax)) {
        if (arg1 >= 0) {
            if (gTrackNodePool[arg1].active == 0) {
                var_a2 = ((s32) (*(arg1 + (gGameState * 4) + &gSfxGameParams) * 3) / 2) + 0x40;
                goto block_5;
            }
        } else {
block_5:
            var_a0 = gSfxAmbientCount + 1;
            if (var_a0 >= 8) {
                var_a0 = 0;
            }
            if (var_a0 != gSfxAmbientSlot) {
                temp_v1 = gSfxAmbientCount * 4;
                *(temp_v1 + &gSfxAmbientIds) = arg0;
                *(temp_v1 + &gSfxAmbientParams) = var_a2;
                gSfxAmbientCount = var_a0;
            }
        }
    }
}
