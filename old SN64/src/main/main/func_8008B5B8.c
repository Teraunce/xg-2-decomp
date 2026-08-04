#include "ultra64.h"
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad04[0x5C];
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 unk64;
} UnkStruct_arg0;

s32 func_80089A68(UnkStruct_arg0*);                          /* extern */
s32 func_80089B64(Unk*, Unk*, u8, u8);              /* extern */

s32 func_8008B5B8(UnkStruct_arg0 *arg0, s32 *arg1) {
    s32 sp12C;
    s32 sp128;
    s32 sp28[66];
    s32 sp24;
    u8 sp23;
    s32 sp1C;
    s32 temp_t3;
    u8 temp_t5;

    sp128 = 0;
    sp24 = 0;
    if (!(arg0->unk0 & 1)) {
        return 5;
    }
    if (func_80089A68(arg0) == 2) {
        return 2;
    }
    sp23 = 0;
    if ((s32) arg0->unk64 > 0) {
loop_5:
        sp24 = func_80089B64(arg0, &sp28, 0, sp23);
        if (sp24 != 0) {
            return sp24;
        }
        if ((s32) sp23 > 0) {
            sp1C = 1;
        } else {
            sp1C = arg0->unk60;
        }
        sp12C = sp1C;
        if (sp1C < 0x80) {
            do {
    Unk *sp = M2C_ERROR(/* sp register */);
                if ((sp + (sp12C * 2))->unk28 == 3) {
                    sp128 += 1;
                }
                temp_t3 = sp12C + 1;
                sp12C = temp_t3;
            } while (temp_t3 < 0x80);
        }
        temp_t5 = sp23 + 1;
        sp23 = temp_t5;
        if ((temp_t5 & 0xFF) >= (s32) arg0->unk64) {
            goto block_15;
        }
        goto loop_5;
    }
block_15:
    *arg1 = (sp128 * 8) << 5;
    return 0;
}
