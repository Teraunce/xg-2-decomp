#include "ultra64.h"
s32 func_80074EA0();                                /* extern */
void func_80074ED8(s32);                               /* extern */
void __osPiRawWriteIo(s32*, s32);                              /* extern */
void func_80076070();                                  /* extern */
extern u32 osTvType;
extern s32 D_80093F50;
extern s32 D_80093F60;
extern s8 D_80189168;
extern s8 D_8018916A;

void func_8007583C(void) {
    s32 temp_a0;
    s32 temp_s0;

    temp_s0 = func_80074EA0();
    func_80076070();
    __osPiRawWriteIo(0xB1FFFFF0, 0);
    __osPiRawWriteIo(0xB1FFFFFC, 0);
    D_80189168 = 1;
    D_8018916A = 0xFF;
    if ((u32) osTvType > 0x3FFFFFU) {
        temp_a0 = osTvType - 1;
        if (!(osTvType & 0x1FFFF) & ((u32) osTvType <= 0x02000000U)) {
            D_80093F50 = temp_a0 - 0x80000000;
            D_80093F60 = temp_a0 + 0xA0000000;
        }
    }
    func_80074ED8(temp_s0);
}
