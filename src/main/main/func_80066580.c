#include "ultra64.h"
extern f32 gEntityFieldF;
extern s32 gSceneObjFuncTable;

/*
 * sceneObjectDispatch — scene-object sub-dispatcher (nonmatching).
 *
 * PERMANENTLY NONMATCHING — two reasons:
 *
 * 1. Five alabel markers: other functions branch INTO this function's body at
 *    five mid-body addresses.  m2c cannot represent cross-function entry points.
 *
 * 2. Dispatches via jr through jtbl_8004C0F0.  The table base is loaded into
 *    $t0 inside the function body (not an ABI violation; $t0 is set from a
 *    computed index), then `jr $t0` fires.  m2c marks any jr-from-table as
 *    nonmatching.
 *
 * Function size: 0x474 bytes.
 */
void sceneObjectDispatch(void) { /* nonmatching — see asm stub */ }

/* D_800669F4: rodata/jtbl — defined in .s file */

void audioSetBeatPos(Unk *arg0, s32 arg1, s32 arg2) {
    s32 var_a1;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v1;
    s8 *var_a3_2;
    Unk *var_a3;
    u8 *var_v0_6;
    u8 var_v1_2;
    Unk *temp_a3;
    Unk *temp_a3_2;
    Unk *temp_a3_3;
    Unk *temp_a3_4;
    Unk *temp_a3_5;
    Unk *var_v0_5;

    var_a3 = arg0 + 0x15;
    arg0->unk0 = 0;
    if (arg2 != 0) {
        var_v0 = arg1;
        if (arg1 < 0) {
            var_v0 = arg1 + 7;
        }
        var_v0_2 = (var_v0 >> 3) * 8;
    } else {
        var_v0_2 = (arg1 / 7) * 7;
    }
    arg0->unk8 = (s32) (arg1 - var_v0_2);
    if (arg2 != 0) {
        var_v0_3 = arg1;
        if (arg1 < 0) {
            var_v0_3 = arg1 + 3;
        }
        var_v0_4 = arg1 - ((var_v0_3 >> 2) * 4);
    } else {
        var_v0_4 = -1;
    }
    arg0->unk4 = var_v0_4;
    var_v1 = 7;
    var_v0_5 = arg0 + 7;
    do {
        var_v0_5->unkC = 0;
        var_v1 -= 1;
        var_v0_5 -= 1;
    } while (var_v1 >= 0);
    arg0->unk14 = 0;
    if (arg2 != 0) {
        arg0->unk15 = 0x50;
        temp_a3 = var_a3 + 1;
        var_a3->unk1 = 0x6C;
        temp_a3_2 = temp_a3 + 1;
        temp_a3->unk1 = 0x61;
        temp_a3_3 = temp_a3_2 + 1;
        temp_a3_2->unk1 = 0x79;
        temp_a3_4 = temp_a3_3 + 1;
        temp_a3_3->unk1 = 0x65;
        temp_a3_5 = temp_a3_4 + 1;
        temp_a3_4->unk1 = 0x72;
        var_a1 = arg1 + 1;
        var_a3_2 = temp_a3_5 + 1;
        if (var_a1 >= 0xA) {
            temp_a3_5->unk1 = (s8) (((arg1 + 1) / 10) + 0x30);
            var_a3_2 += 1;
            var_a1 = (arg1 + 1) % 10;
        }
        *var_a3_2 = var_a1 + 0x30;
        var_a3 = var_a3_2 + 1;
    } else {
        var_v0_6 = *((arg1 * 4) + &gSceneObjFuncTable);
        var_v1_2 = *var_v0_6;
        if (var_v1_2 != 0) {
            do {
                var_v0_6 += 1;
                var_a3->unk0 = var_v1_2;
                var_v1_2 = *var_v0_6;
                var_a3 += 1;
            } while (var_v1_2 != 0);
        }
    }
    var_a3->unk0 = 0;
    arg0->unk28 = 0x2000;
    arg0->unk2C = 0x10;
    arg0->unk30 = 0x800;
    arg0->unk34 = 0x400;
    arg0->unk38 = 0x4000;
    arg0->unk3C = 4;
    arg0->unk40 = 0x8000;
    arg0->unk44 = 1;
    arg0->unk48 = 2;
    arg0->unk4C = 0x20;
    arg0->unk20 = 0;
    arg0->unk24 = arg2;
    arg0->unk50 = 8;
    arg0->unk58 = 0;
    arg0->unk54 = (f32) gEntityFieldF;
}
