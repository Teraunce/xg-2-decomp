#include "ultra64.h"
extern s32 gGameState;
extern s32 gAudioQueueReadIdx;
extern s32 gAudioQueueWriteIdx;
extern s32 gSfxSampleRate;
extern s32 gSfxQueueDepth;
extern s32 gSfxMidiReady;
extern s32 gSfxQueueReady;
extern s32 gAudioQueueState;
extern s32 gSfxGameParams;
extern s32 gTrackNodePool;
extern s32 gRaceMax;
extern s32 gAudioNoteList;
extern s32 gAudioQueueBuf;
extern s32 gSfxAmbientIds;
extern s32 gSfxAmbientParams;
extern s32 gSfxAmbientSlot;
extern s32 gSfxAmbientCount;
extern s32 gSfxAmbientHandle;

/*
 * audioQueueDispatch — audio event sub-dispatcher (nonmatching).
 *
 * PERMANENTLY NONMATCHING — three reasons:
 *
 * 1. Non-standard ABI: $v1 is used as an input argument immediately after
 *    the prologue register saves: `sltiu $v0, $v1, 0x5`.  In standard MIPS
 *    ABI, $v0/$v1 are return-value registers, not argument registers.
 *    No C declaration can express this.
 *
 * 2. Three alabel markers: other functions branch INTO this function's body
 *    at three mid-body addresses.  m2c cannot represent cross-function
 *    entry points and rejects the file.
 *
 * 3. Dispatches via jr through jtbl_8004BDF0 (5 entries, index = v1,
 *    range check < 5): [0]=0x8005C9F4, [1]=..., [4]=0x8005CBC0.
 *    m2c marks any jr-from-table as nonmatching.
 *
 * Function size: 0x324 bytes.
 */
void audioQueueDispatch(void) { /* nonmatching — see asm stub */ }

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
            if (((Unk*)((char*)&gTrackNodePool + arg1 * 0x668))->unk450 == 0) {
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
