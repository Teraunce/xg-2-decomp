#include "ultra64.h"
void func_80074F08(s32*, s32);                            /* extern */
s32 func_80074F40(s32*);                               /* extern */
void func_80074F7C(s32);                                 /* extern */

s32 func_80075B78(s32 arg0, s32 arg2, s32 arg3) {
    func_80074F08(0xB1FFFFE4, 0);
    func_80074F08(0xB1FFFFE8, arg2);
    func_80074F08(0xB1FFFFEC, arg3);
    func_80074F08(0xB1FFFFE0, arg0);
    do {
        func_80074F7C(0x3E8);
        if (func_80074F40(0xB1FFFFF0) != 0) {
            M2C_BREAK(1);
        }
    } while (func_80074F40(0xB1FFFFE0) != 0);
    func_80074F40(0xB1FFFFDC);
}
