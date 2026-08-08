#include "ultra64.h"
void entitySlotReset(void *, void *, s32);                 /* extern */
s32 func_80097F10(void *, s32);                         /* extern */
s32 func_800F1604(void *, f32 *, void *);                /* extern */
extern f32 gViScreenSz;
extern f32 gVelInitParamA;
extern f32 gVelInitParamB;
extern f32 gVelInitParamC;
extern f32 gVelInitParamD;
extern f32 gVelInitParamE;
extern f32 gVelInitParamF;
extern f32 gVelInitParamG;
extern f32 gVelInitParamH;
extern f32 gVelInitParamI;
extern f32 gVelInitParamJ;
extern f32 gVelInitParamK;
extern f32 gVelInitParamL;
extern f32 gVelInitParamM;
extern s32 gGameFlags;
extern s32 gRaceSlotCount;
extern Unk gRaceCtx;

void entityPhysicsInit(Unk *arg0, Unk *arg1, s32 arg3) {
    s32 sp20;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 temp_fv1;
    f32 var_fv0;
    s32 temp_a0;
    s32 var_a0;
    s32 var_a3;
    s32 var_v0;
    char *temp_s0;
    Unk *temp_v0;
    Unk *var_v1;

    var_a3 = arg3;
    var_a0 = 0;
    var_v1 = arg0;
    arg0->unkB4 = 0x398;
    arg0->unkB0 = 0x1770;
    arg0->unk18 = 0;
    arg0->unk20 = 0;
    arg0->unkB8 = 1;
    arg0->unkD0 = arg1;
    arg0->unk0 = (f32) gViScreenSz;
    arg0->unk4 = (f32) gVelInitParamA;
    arg0->unk8 = (f32) gVelInitParamB;
    arg0->unkC = (f32) gViScreenSz;
    arg0->unk10 = (f32) gVelInitParamC;
    arg0->unk14 = (f32) gVelInitParamD;
    arg0->unk1C = (f32) gVelInitParamE;
    arg1->unk568 = arg0;
    do {
        temp_v0 = arg0 + var_a0;
        temp_v0->unkD4 = 0;
        temp_v0->unkDC = 0;
        var_v1->unkE4 = 0xFFFF;
        var_v1->unk104 = 0;
        var_a0 += 1;
        temp_v0->unk124 = 0;
        var_v1 += 4;
    } while (var_a0 < 8);
    arg0->unk12C = -1;
    arg0->unk1D4 = 0xFF;
    arg0->unk134 = 0;
    arg0->unk144 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk130 = (f32) gVelInitParamF;
    arg0->unk148 = (f32) gVelInitParamG;
    if (gRaceCtx.unk16D8 == 0xE) {
        var_a3 = MULT_HI(gRaceSlotCount, 0x38E38E39);
        temp_a0 = gRaceSlotCount % 9;
        switch (temp_a0) {                          /* irregular */
        case 2:
            var_fv0 = gVelInitParamH;
            arg0->unk1DC = 0;
block_14:
            arg0->unk1F8 = var_fv0;
            break;
        case 6:
            var_fv0 = gVelInitParamI;
            arg0->unk1DC = 0;
            goto block_14;
        case 8:
            arg0->unk1DC = 0;
            var_fv0 = gVelInitParamJ;
            goto block_14;
        default:
            arg0->unk1DC = 4;
            arg0->unk1F8 = (f32) gVelInitParamK;
            break;
        }
    } else {
        temp_fv1 = ((Unk*)((Unk*)((arg1->unk560 * 4) + &gRaceCtx)->unk16F8))->unk54;
        arg0->unk1F8 = temp_fv1;
        if (gGameFlags & 8) {
            var_v0 = 5;
        } else {
            var_v0 = 1;
            if (temp_fv1 >= 0.0f) {
                var_v0 = 0;
            }
        }
        arg0->unk1DC = var_v0;
    }
    temp_s0 = arg0 + 0x14C;
    arg0->unk1E0 = 0;
    arg0->unk1E4 = 0;
    sp10 = arg0->unk0;
    sp14 = arg0->unk4;
    sp18 = arg0->unk8;
    entitySlotReset(&sp10, temp_s0, 1);
    func_800F1604(temp_s0, &sp10, &sp20);
    func_80097F10(arg0, 1);
    sp10 = arg0->unk0;
    sp14 = arg0->unk4;
    sp18 = arg0->unk8;
    entitySlotReset(&sp10, temp_s0, 1);
    func_800F1604(temp_s0, &sp10, &sp20);
    arg0->unk1E8 = 0;
    arg0->unk1EC = 0;
    arg0->unk1F0 = 0;
    arg0->unk1F4 = 0;
    arg0->unk1FC = 0;
    arg0->unk200 = 0;
    arg0->unk208 = 0;
    arg0->unk20C = 0;
    arg0->unk210 = 0;
    arg0->unk214 = 0;
    arg0->unk218 = 0;
    arg0->unk204 = (f32) gVelInitParamL;
    arg0->unk21C = (f32) gVelInitParamM;
}

void sfxEntryReset(Unk *arg0) {
    arg0->unk0 = 0;
    arg0->unk4 = 0;
    arg0->unk8 = 0;
    arg0->unkC = 0;
    arg0->unk10 = 0;
    arg0->unk14 = 0;
    arg0->unk18 = -1;
    arg0->unk1C = 0;
    arg0->unk20 = -1;
}
