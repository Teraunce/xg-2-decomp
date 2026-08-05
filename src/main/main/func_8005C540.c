#include "ultra64.h"
#define M2C_ERROR(x) ((Unk *)0)
void func_8005C010();                                  /* extern */
void func_8007BCA8();                                  /* extern */
s32 func_8007CD08(Unk*, s32*, s32);                         /* extern */
s32 func_80086848(s32, s32);                          /* extern */
void func_80086A44(void *);                               /* extern */
void func_80086BD4(s32);                               /* extern */
extern s32 D_800927D0;
extern s32 D_800927D8;
extern s32 D_800927DC;
extern s32 D_800927E0;
extern u32 D_800927FC;
extern s32 D_8017EFC8;
extern s32 D_8017F438;
extern s32 D_80180884;
extern s32 D_801816A8;

s32 func_8005C540(void) {
    s32 temp_a1;
    s32 var_s0;

    if ((s32)M2C_ERROR(/* Read from unset register $v0 */) != 0) {
        D_800927FC = (u32) *(u32 *)0xA4500004 >> 2;
        temp_a1 = (D_800927E0 - 1) % 3;
        func_80086848(*((temp_a1 * 4) + &D_8017F438), *((temp_a1 * 2) + &D_800927D0) * 4);
        var_s0 = 0;
        if (D_800927D8 > 0) {
            do {
                func_8007CD08(&D_8017EFC8, 0, 0);
                var_s0 += 1;
            } while (var_s0 < D_800927D8);
        }
        func_8007BCA8();
        func_80086A44(D_80180884);
        func_80086BD4(D_80180884);
        func_8005C010();
        D_800927D8 = 0;
        D_801816A8 += 1;
        D_800927E0 += 1;
        D_800927DC ^= 1;
    }
    return 0;
}
