#include "ultra64.h"
void func_80052C88(s32, s32, s32);                           /* extern */
void func_80062878(s32);                               /* extern */
void func_80062A6C();                                  /* extern */
void func_80062F4C(s32, s32, s32, s32);                      /* extern */
s32 func_800B1558(s32);                             /* extern */
extern s32 D_80092B58;
extern s32 D_80092BB8;
extern u32 D_80092CA8;
extern Unk *D_80173CC0;
extern s32 D_80173D08;
extern s32 D_80181E48;
extern s32 D_80181E4C;
extern u16 D_801822D8;

void func_800600D8(s32 arg0, s32 arg1) {
    s32 var_a0;
    s32 var_a1;
    s32 var_v0;
    Unk *temp_v1;

    temp_v1 = D_80173CC0 + 8;
    D_80173CC0->unk0 = 0xDE000000;
    D_80173CC0->unk4 = &D_80092BB8;
    D_80173CC0 = temp_v1;
    D_80173CC0 = temp_v1 + 8;
    D_80173CC0->unk8 = 0xDB0E0000;
    temp_v1->unk4 = (s32) D_801822D8;
    if (D_80181E48 == 1) {
        goto block_25;
    }
    switch (D_80181E48) {                           /* irregular */
    case 0:
        if (((u32) (arg0 - 5) >= 2U) && (arg0 != 3)) {
            if (arg0 == 4) {
                if (D_80092B58 != 0) {
                    goto block_12;
                }
                goto block_13;
            }
        } else {
block_12:
            func_80052C88(0, 0, 0);
block_13:
            if (arg0 == 4) {
                func_80062878((u32) D_80092CA8 >= 5U);
            }
        }
        if (arg1 != 0) {
            var_v0 = arg1;
            if (arg1 < 0) {
                var_v0 = arg1 + 0xFF;
            }
            var_a0 = var_v0 >> 8;
            if (var_a0 >= 0x100) {
                var_a0 = 0xFF;
            }
            var_a1 = arg1 / 256;
            if (var_a1 >= 0x100) {
                var_a1 = 0xFF;
            }
            if (var_a1 <= 0) {
                var_a0 = 0;
            }
            func_80062F4C(var_a0, 0, 0, 0);
        }
        break;
    case 3:
block_25:
        func_80052C88(0, 0, 0);
        break;
    case 2:
        func_80052C88(0, 0, 0);
        if (func_800B1558(D_80173D08 - D_80181E4C) == 0) {
            D_80181E48 = 3;
        }
        break;
    }
    func_80062A6C();
    D_80092CA8 += 1;
}
