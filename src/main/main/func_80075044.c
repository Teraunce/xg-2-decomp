#include "ultra64.h"
s32 __osPiRawReadIo(s32*);                              /* extern */
s32 func_80074FC4(s32);                              /* extern */

void func_80075044(s32 arg0, s8 *arg1, u32 arg2) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 var_s2;
    s32 var_v0;
    Unk *var_s0;
    u32 var_s1;
    u8 temp_v0;
    Unk *temp_s0;
    Unk *temp_s0_2;

    /* Flowgraph is not reducible, falling back to gotos-only mode. */
    var_s2 = arg0;
    var_s0 = arg1;
    var_s1 = arg2;
    if (var_s1 == 0) {
        goto block_5;
    }
loop_1:
    var_v0 = var_s1 < 4U;
    if (!(var_s2 & 3)) {
        goto block_6;
    }
    temp_a0 = var_s2;
    var_s2 += 1;
    var_s0->unk0 = func_80074FC4(temp_a0);
    var_s1 -= 1;
    var_s0 += 1;
    if (var_s1 != 0) {
        goto loop_1;
    }
    var_v0 = var_s1 < 4U;
    goto block_6;
block_4:
    temp_v0 = __osPiRawReadIo(var_s2);
    var_s0->unk0 = (s8) (temp_v0 >> 0x18);
    temp_s0 = var_s0 + 1;
    var_s0->unk1 = (s8) (temp_v0 >> 0x10);
    temp_s0_2 = temp_s0 + 1;
    temp_s0->unk1 = (s8) (temp_v0 >> 8);
    temp_s0_2->unk1 = temp_v0;
    var_s0 = temp_s0_2 + 1 + 1;
    var_s2 += 4;
    var_s1 -= 4;
block_5:
    var_v0 = var_s1 < 4U;
block_6:
    if (var_v0 == 0) {
        goto block_4;
    }
    if (var_s1 == 0) {
        goto block_9;
    }
loop_8:
    temp_a0_2 = var_s2;
    var_s2 += 1;
    var_s0->unk0 = func_80074FC4(temp_a0_2);
    var_s1 -= 1;
    var_s0 += 1;
    if (var_s1 != 0) {
        goto loop_8;
    }
block_9:
    return;
}

void func_80075120(s32 arg0, s32 arg1) {
    s32 temp_a0;
    s32 temp_a2;

    temp_a2 = (~arg0 & 3) * 8;
    temp_a0 = arg0 & ~3;
    *(s32 *)temp_a0 = (s32) ((*(s32 *)temp_a0 & ~(0xFF << temp_a2)) | ((arg1 & 0xFF) << temp_a2));
}
