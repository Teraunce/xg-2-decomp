#include "ultra64.h"
s32 func_80074EA0();                                /* extern */
void func_80074ED8(s32);                               /* extern */
void func_80074F08(s32*, s32);                              /* extern */
void func_80076070();                                  /* extern */
extern u32 D_80000318;
extern s32 D_80093F50;
extern s32 D_80093F60;
extern s8 D_80189168;
extern s8 D_8018916A;

void func_8007583C(void) {
    s32 temp_a0;
    s32 temp_s0;

    temp_s0 = func_80074EA0();
    func_80076070();
    func_80074F08(0xB1FFFFF0, 0);
    func_80074F08(0xB1FFFFFC, 0);
    D_80189168 = 1;
    D_8018916A = 0xFF;
    if ((u32) D_80000318 > 0x3FFFFFU) {
        temp_a0 = D_80000318 - 1;
        if (!(D_80000318 & 0x1FFFF) & ((u32) D_80000318 <= 0x02000000U)) {
            D_80093F50 = temp_a0 - 0x80000000;
            D_80093F60 = temp_a0 + 0xA0000000;
        }
    }
    func_80074ED8(temp_s0);
}
