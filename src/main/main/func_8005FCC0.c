#include "ultra64.h"
void sfxMarkAllActive(void);                              /* extern */
void sfxPlay(u16);                               /* extern */
char *sfxGetEntry(s32);                           /* extern */
s32 sfxGetFrameOutput(s32);                             /* extern */
s32 trackSegmentOffset(s32, s32, void *, s32);              /* extern */
s32 sfxHandlerEnsure(void *, s32 (*)(void *, s32));                /* extern */
extern s32 gRaceCtrl;
extern s32 gGameFlags;
extern s32 gRaceFlags;
extern s32 gRaceEntityVal;
extern s32 gRaceEntityIdx;
extern s32 *gRaceEntityPtr;
extern s32 gLoopCount;
extern s32 gSfxChannelState;
extern Unk gRaceCtx;

void sfxRaceUpdate(s32 arg3) {
    s32 sp60;
    s32 sp10;
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_v1_2;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;
    s32 sp;
    s32 var_t0;
    s8 *temp_v0;
    s8 *temp_v1;
    s8 var_a0;
    s8 var_a3_2;
    Unk *temp_v0_2;

    var_a3 = arg3;
    if ((s32)0 /* implicit $v0 from caller */ != 0) {
        gGameFlags = 0;
    } else {
        gGameFlags = gRaceFlags;
    }
    if (gGameFlags & 0x200) {
        var_a2 = 0;
        if (gRaceCtx.unk16DC >= 0xD) {
            gRaceCtx.unk16E0 = 0;
            gRaceCtx.unk16DC = (s32) ((gLoopCount % 6) + 0xD);
        } else {
            var_a3_2 = 0;
            var_t0 = 0;
            do {
                var_a0 = 0;
                var_a1 = var_t0;
loop_8:
                if ((void *)((var_a1 + &gRaceCtx))->unk4 != 0) {
                    temp_v0 = &sp10 + var_a2;
                    temp_v1 = &sp60 + var_a2;
                    var_a2 += 1;
                    *temp_v0 = var_a3_2;
                    *temp_v1 = var_a0;
                }
                var_a0 += 1;
                var_a1 += 4;
                if (var_a0 < 6) {
                    goto loop_8;
                }
                var_a3_2 += 1;
                var_t0 += 0xD8;
            } while (var_a3_2 < 0xC);
            var_a3 = (s32) gLoopCount % var_a2;
            sp = 0; gRaceCtx.unk16DC = (s32) ((Unk*)(s32)(sp + var_a3))->unk10;
            gRaceCtx.unk16E0 = (s32) ((Unk*)(s32)(sp + var_a3))->unk60;
        }
    }
    temp_s1 = gRaceCtx.unk16D8;
    gRaceEntityIdx = 0;
    gRaceEntityPtr = (gRaceCtx.unk16DC * 0xD8) + (&gRaceCtx + 0x1C) + (gRaceCtx.unk16E0 * 0x10);
    if (temp_s1 == 1) {
        temp_v1_2 = ((Unk*)gRaceCtx.unk16F8)->unk8;
        if ((temp_v1_2 >= 0xA) && (temp_v1_2 < 0xD)) {
            temp_s0 = sfxGetFrameOutput(trackSegmentOffset(gRaceCtx.unk16DC, gRaceCtx.unk16E0, &gRaceCtx, var_a3)) & 0xFFFF;
            temp_v0_2 = sfxGetEntry(temp_s0);
            if (temp_v0_2->unkC < *gRaceEntityPtr) {
                gRaceEntityIdx = temp_s1;
                gRaceEntityPtr = &gRaceEntityVal;
                gRaceEntityVal = temp_v0_2->unkC;
            }
            sfxPlay(temp_s0);
        }
    }
    if (gRaceCtrl != 0) {
        sfxMarkAllActive();
        return;
    }
    sfxHandlerEnsure(&gSfxChannelState, sfxMarkAllActive);
}

void func_8005FF2C(void) {

}
