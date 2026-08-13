#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of sfxComputeSpatial (initial). */

s16 midiAllocNote(Unk*, Unk*);                        /* extern */
void midiReleaseNote(Unk*, s16);                          /* extern */
void midiSetNote(Unk*, s16);                          /* extern */
void midiSeqStop(void *);                               /* extern */
void midiTimerReset(char*);                               /* extern */
s32 midiNoteIsPlaying(char*);                             /* extern */
void midiTimerSetNote(void *, f32);                          /* extern */
void midiNoteSetState(void *, s16, s32);                      /* extern */
void midiSetVolume(void *, s16);                          /* extern */
void midiSetExpression(void *, s8);                           /* extern */
void midiSetController(void *, s8);                           /* extern */
extern f32 gSfxSpatialDistThresh;
extern f32 gMidiVelThresh;
extern f32 gSfxSpatialParamB;
extern f32 gSfxSpatialParamC;
extern f64 gSfxSpatialParamD;
extern f64 gSfxSpatialParamE;
extern f64 gSfxSpatialParamF;
extern f32 gSfxDistClampA;
extern s32 gMidiCtx;
extern s32 gAudioQueueReadIdx;
extern s32 gAudioQueueWriteIdx;
extern s32 gSfxSampleRate;
extern s32 gSfxQueueDepth;
extern s32 gSfxMidiReady;
extern s32 gSfxQueueReady;
extern s32 gSfxSpatialCount;
extern s32 gMidiProgramTbl;
extern s32 gMidiVelocityTbl;
extern s32 gMidiFreqTable;
extern s32 gMidiNoteTable;
extern s32 gAudioNoteList;
extern s32 gAudioQueueBuf;
extern s32 gSfxVolumeF64;

void midiQueueProcess(void) {
    u8 sp10;
    Unk *var_s0;
    Unk *var_s0_2;
    Unk *var_s0_3;
    Unk *var_v1;
    Unk *var_v1_2;
    Unk *var_v1_3;
    f32 temp_fs3;
    f32 temp_fs4;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fv0;
    f32 var_fv0_2;
    f32 var_fv1;
    f64 temp_fs0;
    f64 temp_fs1;
    f64 temp_fs2;
    f64 var_ft0;
    f64 var_ft0_2;
    f64 var_fv1_2;
    f64 var_fv1_3;
    f64 var_fv1_4;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v1;
    s16 var_a1;
    s32 temp_a0;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 var_s2;
    s32 var_s2_2;
    s32 var_s2_3;
    s32 var_s3;
    s32 var_s3_2;
    s32 var_s3_3;
    s32 var_s3_4;
    s32 var_s3_5;
    s32 sp;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_7;
    s32 var_v0_8;
    u16 temp_v1_5;
    u8 *temp_s1_2;
    u8 *temp_s1_3;
    u8 *var_a2;
    u8 *var_v0;
    u8 temp_s2;
    u8 var_a1_2;
    u8 var_a1_3;
    Unk *temp_s1;
    Unk *var_v0_6;

    var_s3 = 0;
    var_v0 = &sp10;
    do {
        var_s3 += 1;
        *var_v0 = (gSfxMidiReady != 0) * 4;
        var_v0 = &(&sp10)[var_s3];
    } while (var_s3 < 0x1C);
    gSfxMidiReady = 0;
    var_s3_2 = 0;
    var_s0 = &gAudioNoteList;
    do {
        temp_v0 = var_s0->unk4;
        if (temp_v0 != 1) {
            if (temp_v0 != 3) {
                var_s3_2 += 1;
            } else {
                goto block_7;
            }
        } else {
block_7:
            midiSetNote(gMidiCtx, var_s0->unk12);
            var_s3_2 += 1;
            if (midiNoteIsPlaying(gMidiCtx) == 0) {
                midiReleaseNote(gMidiCtx, var_s0->unk12);
                var_s0->unk4 = 0;
                var_s0->unk0 = 0;
                gSfxSpatialCount -= 1;
            }
        }
        var_s0 += 0x14;
    } while (var_s3_2 < 0x1C);
    var_s3_3 = gAudioQueueReadIdx;
    if (var_s3_3 != gAudioQueueWriteIdx) {
        var_v0_2 = var_s3_3 * 4;
        do {
            temp_s1 = ((var_v0_2 + var_s3_3) * 4) + &gAudioQueueBuf;
            temp_v1 = temp_s1->unk4;
            if (temp_v1 != 1) {
                if (temp_v1 >= 2) {
                    if (temp_v1 != 2) {
                        if (temp_v1 == 3) {
                            var_s2 = 0;
                            var_v1 = &gAudioNoteList;
loop_59:
                            if (var_v1->unk0 != temp_s1->unk0) {
                                var_s2 += 1;
                                var_v1 += 0x14;
                                if (var_s2 < 0x1C) {
                                    goto loop_59;
                                }
                            } else if (var_v1->unk4 == 1) {
                                temp_s1_2 = &(&sp10)[var_s2];
                                if (!(*temp_s1_2 & 1)) {
                                    midiSetNote(gMidiCtx, var_v1->unk12);
                                    midiTimerReset(gMidiCtx);
                                }
                                *temp_s1_2 = 0;
                                var_v1->unk4 = 3;
                            }
                            goto block_67;
                        }
                        var_s3_3 += 1;
                    } else {
                        var_s2_2 = 0;
                        var_a2 = &sp10;
                        var_v1_2 = &gAudioNoteList;
loop_28:
                        if (var_v1_2->unk0 != temp_s1->unk0) {
                            var_a2 += 1;
                            var_s2_2 += 1;
                            var_v1_2 += 0x14;
                            if (var_s2_2 >= 0x1C) {
                                var_s3_3 += 1;
                            } else {
                                goto loop_28;
                            }
                        } else {
                            if (var_v1_2->unk4 == 1) {
                                if (gSfxSpatialDistThresh < fabsf(var_v1_2->unk8 - temp_s1->unk8)) {
                                    *var_a2 |= 2;
                                    temp_fv1 = var_v1_2->unk8;
                                    temp_fv0 = temp_s1->unk8;
                                    if (!(temp_fv0 < temp_fv1)) {
                                        temp_fv0_2 = temp_fv0 - temp_fv1;
                                        if (gMidiVelThresh <= temp_fv0_2) {
                                            var_fv0 = temp_fv1 + gMidiVelThresh;
                                        } else {
                                            var_fv0 = temp_fv1 + temp_fv0_2;
                                        }
                                    } else {
                                        temp_fv0_3 = temp_fv1 - temp_fv0;
                                        if (gMidiVelThresh <= temp_fv0_3) {
                                            var_fv0 = temp_fv1 - gMidiVelThresh;
                                        } else {
                                            var_fv0 = temp_fv1 - temp_fv0_3;
                                        }
                                    }
                                    *(f32*)((char*)var_v1_2 + 8) = var_fv0;
                                }
                                if (var_v1_2->unkC != temp_s1->unkC) {
                                    *var_a2 |= 4;
                                    temp_a0 = var_v1_2->unkC;
                                    temp_v1_2 = temp_s1->unkC;
                                    if (temp_v1_2 >= temp_a0) {
                                        temp_v1_3 = temp_v1_2 - temp_a0;
                                        var_v0_3 = temp_a0 + temp_v1_3;
                                        if (temp_v1_3 >= 0x2000) {
                                            var_v0_3 = temp_a0 + 0x2000;
                                        }
                                    } else {
                                        temp_v1_4 = temp_a0 - temp_v1_2;
                                        var_v0_3 = temp_a0 - temp_v1_4;
                                        if (temp_v1_4 >= 0x2000) {
                                            var_v0_3 = temp_a0 - 0x2000;
                                        }
                                    }
                                    var_v1_2->unkC = var_v0_3;
                                }
                                if (var_v1_2->unk10 != temp_s1->unk10) {
                                    *var_a2 |= 8;
                                    var_v1_2->unk10 = (u8) temp_s1->unk10;
                                }
                                if (var_v1_2->unk11 != temp_s1->unk11) {
                                    *var_a2 |= 0x10;
                                    var_v1_2->unk11 = (u8) temp_s1->unk11;
                                }
                            }
                            goto block_67;
                        }
                    }
                } else {
                    goto block_67;
                }
            } else {
                var_s2_3 = 0;
                var_v1_3 = &gAudioNoteList;
loop_20:
                if (var_v1_3->unk4 != 0) {
                    var_s2_3 += 1;
                    var_v1_3 += 0x14;
                    if (var_s2_3 >= 0x1C) {
                        var_s3_3 += 1;
                    } else {
                        goto loop_20;
                    }
                } else {
                    temp_v0_2 = midiAllocNote(gMidiCtx, ((Unk*)(s32)(gMidiNoteTable + (temp_s1->unk6 * 4)))->unk10);
                    if (temp_v0_2 >= 0) {
                        var_v1_3->unk0 = (s32) temp_s1->unk0;
                        var_v1_3->unk4 = (s32) temp_s1->unk4;
                        var_v1_3->unk8 = (f32) temp_s1->unk8;
                        var_v1_3->unkC = (s32) temp_s1->unkC;
                        var_v1_3->unk10 = (s32) temp_s1->unk10;
                        var_v1_3->unk12 = temp_v0_2;
                        (&sp10)[var_s2_3] = 1;
                        gSfxSpatialCount += 1;
                    }
block_67:
                    var_s3_3 += 1;
                }
            }
            if (var_s3_3 >= 0x80) {
                var_s3_3 = 0;
            }
            var_v0_2 = var_s3_3 * 4;
        } while (var_s3_3 != gAudioQueueWriteIdx);
    }
    gAudioQueueReadIdx = var_s3_3;
    if (gSfxQueueReady != 0) {
        var_s3_4 = 0;
        var_s0_2 = &gAudioNoteList;
        do {
            if (var_s0_2->unk4 == 1) {
                temp_s1_3 = &(&sp10)[var_s3_4];
                if (!(*temp_s1_3 & 1)) {
                    midiSetNote(gMidiCtx, var_s0_2->unk12);
                    midiTimerReset(gMidiCtx);
                }
                *temp_s1_3 = 0;
                var_s0_2->unk4 = 3;
            }
            var_s3_4 += 1;
            var_s0_2 += 0x14;
        } while (var_s3_4 < 0x1C);
        gSfxQueueReady = 0;
    }
    sp = 0;
    var_s3_5 = 0;
    var_s0_3 = &gAudioNoteList;
    temp_fs4 = gSfxSpatialParamB;
    temp_fs3 = gSfxSpatialParamC;
    temp_fs2 = gSfxSpatialParamD;
    temp_fs1 = gSfxSpatialParamE;
    temp_fs0 = gSfxSpatialParamF;
    do {
        temp_s2 = ((Unk*)(s32)(sp + var_s3_5))->unk10;
        if (var_s0_3->unk4 != 1) {
            var_s3_5 += 1;
        } else if (temp_s2 == 0) {
            var_s3_5 += 1;
        } else {
            midiSetNote(gMidiCtx, var_s0_3->unk12);
            var_v0_4 = temp_s2 & 5;
            if (temp_s2 & 3) {
                temp_fv1_2 = var_s0_3->unk8 * (f32) *(((var_s0_3->unk6 + 1) * 2) + &gMidiVelocityTbl);
                var_fv0_2 = temp_fv1_2 * temp_fs4;
                if (!(var_fv0_2 <= temp_fs3)) {
                    var_fv0_2 = temp_fs3;
                }
                if (var_fv0_2 <= gSfxDistClampA) {
                    var_fv1 = gSfxDistClampA;
                } else {
                    var_fv1 = temp_fv1_2 * temp_fs4;
                    if (!(var_fv1 <= temp_fs3)) {
                        var_fv1 = temp_fs3;
                    }
                }
                midiTimerSetNote(gMidiCtx, var_fv1);
                var_v0_4 = temp_s2 & 5;
            }
            var_v0_5 = temp_s2 & 9;
            if (var_v0_4 != 0) {
                temp_v1_5 = (u16) var_s0_3->unk6;
                if ((u32) (temp_v1_5 - 0x6A) < 0x22U) {
                    var_fv1_2 = (f64) gSfxQueueDepth * ((f64) var_s0_3->unkC * temp_fs2);
                    var_v0_6 = (s16) temp_v1_5 + &gMidiFreqTable;
                    goto block_97;
                }
                if (((u32) ((temp_v1_5 - 0x18) & 0xFFFF) < 2U) || ((u32) ((temp_v1_5 - 0xE) & 0xFFFF) < 2U) || ((s16) temp_v1_5 == 0x10)) {
                    var_fv1_2 = (f64) gSfxVolumeF64 * ((f64) var_s0_3->unkC * temp_fs2);
                    var_v0_6 = var_s0_3->unk6 + &gMidiFreqTable;
block_97:
                    var_fv1_3 = var_fv1_2 * (f64) var_v0_6->unk1;
                    var_ft0 = var_fv1_3 * temp_fs1;
                    if (!(var_ft0 <= temp_fs0)) {
                        var_ft0 = temp_fs0;
                    }
                    var_a1 = 0;
                    if (!(var_ft0 <= 0.0)) {
                        goto block_108;
                    }
                } else {
                    var_fv1_3 = (f64) gSfxSampleRate * ((f64) var_s0_3->unkC * temp_fs2) * (f64) ((Unk*)((char*)&gMidiFreqTable + (s16)temp_v1_5))->unk1;
                    var_ft0_2 = var_fv1_3 * temp_fs1;
                    if (!(var_ft0_2 <= temp_fs0)) {
                        var_ft0_2 = temp_fs0;
                    }
                    var_a1 = 0;
                    if (!(var_ft0_2 <= 0.0)) {
block_108:
                        var_fv1_4 = var_fv1_3 * temp_fs1;
                        if (!(var_fv1_4 <= temp_fs0)) {
                            var_fv1_4 = temp_fs0;
                        }
                        var_a1 = (s16) (s32) var_fv1_4;
                    }
                }
                midiSetVolume(gMidiCtx, var_a1);
                var_v0_5 = temp_s2 & 9;
            }
            var_v0_7 = temp_s2 & 0x11;
            if (var_v0_5 != 0) {
                var_a1_2 = 0x7F;
                if (var_s0_3->unk10 >= 0) {
                    var_a1_2 = (u8) var_s0_3->unk10;
                    if ((s32) var_a1_2 > 0) {
                        if (var_a1_2 & 0x80) {
                            var_a1_2 = 0x7F;
                        }
                    } else {
                        var_a1_2 = 0;
                    }
                }
                midiSetExpression(gMidiCtx, var_a1_2);
                var_v0_7 = temp_s2 & 0x11;
            }
            var_v0_8 = temp_s2 & 1;
            if (var_v0_7 != 0) {
                var_a1_3 = 0x7F;
                if (var_s0_3->unk11 >= 0) {
                    var_a1_3 = (u8) var_s0_3->unk11;
                    if ((s32) var_a1_3 > 0) {
                        if (var_a1_3 & 0x80) {
                            var_a1_3 = 0x7F;
                        }
                    } else {
                        var_a1_3 = 0;
                    }
                }
                midiSetController(gMidiCtx, var_a1_3);
                var_v0_8 = temp_s2 & 1;
            }
            var_s3_5 += 1;
            if (var_v0_8 != 0) {
                midiNoteSetState(gMidiCtx, var_s0_3->unk12, *(var_s0_3->unk6 + &gMidiProgramTbl));
                midiSeqStop(gMidiCtx);
            }
        }
        var_s0_3 += 0x14;
    } while (var_s3_5 < 0x1C);
}

s32 sfxComputeSpatialImpl(void);  /* forward: GETTER_NOJR fallthrough */
void sfxComputeSpatial(s32 arg2) {
    sfxComputeSpatialImpl();
}
