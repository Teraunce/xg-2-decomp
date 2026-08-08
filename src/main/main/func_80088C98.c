#include "ultra64.h"
s32 osRecvMesg(Unk*, s32*, s32);                         /* extern */
s32 osSiRawStartDma(s32, s32);                          /* extern */
s32 __siLock();                                  /* extern */
void __siUnlock();                                  /* extern */
void siSetupWriteCmd(s32, u16, u8*);                     /* extern */
u8 crc8Calc(u8*);                             /* extern */
s32 contPakProbe(s32, s32);                        /* extern */
extern s8 D_8018AD68;
extern s32 D_8018ADB8;

s32 osContPakWrite(s32 arg0, s32 arg1, u16 arg2, s32 arg3, s32 arg4) {
    s32 sp5C;
    s32 sp58;
    char *sp54;
    s32 sp2C;
    s32 sp28;
    Unk *var_t8;
    Unk *var_t9;
    s32 temp_at;
    s32 temp_t4;
    s32 temp_t6;
    char *temp_t1;
    u8 sp2E; s32 sp52;

    sp5C = 0;
    sp54 = &D_8018ADB8;
    sp28 = 2;
    if ((arg4 != 1) && ((s32) arg2 < 7) && (arg2 != 0)) {
        return 0;
    }
    __siLock();
    D_8018AD68 = 3;
    siSetupWriteCmd(arg1, arg2, arg3);
    sp5C = osSiRawStartDma(1, &D_8018ADB8);
    osRecvMesg(arg0, 0, 1);
loop_5:
    sp5C = osSiRawStartDma(0, &D_8018ADB8);
    osRecvMesg(arg0, 0, 1);
    sp54 = &D_8018ADB8;
    if (arg1 != 0) {
        sp58 = 0;
        if (arg1 > 0) {
            do {
                temp_t6 = sp58 + 1;
                sp58 = temp_t6;
                sp54 += 1;
            } while (temp_t6 < arg1);
        }
    }
    var_t9 = sp54;
    var_t8 = &sp2C;
    temp_t1 = var_t9 + 0x24;
    do {
        temp_at = (s32) var_t9->unk0;
        var_t9 += 0xC;
        var_t8 += 0xC;
        *(s32*)((char*)var_t8 - 12) = temp_at;
        *(s32*)((char*)var_t8 - 8)= (s32) (s32) *(s32*)((char*)var_t9 - 8)
        *(s32*)((char*)var_t8 - 4)= (s32) (s32) *(s32*)((char*)var_t9 - 4)
    } while ((char*)var_t9 != temp_t1);
    var_t8->unk0 = (s32) (s32) var_t9->unk0;
    temp_t4 = (s32) (sp2E & 0xC0) >> 4;
    sp5C = temp_t4;
    if (temp_t4 == 0) {
        if (crc8Calc(arg3) != sp52) {
            sp5C = contPakProbe(arg0, arg1);
            if (sp5C != 0) {
                __siUnlock();
            } else {
                sp5C = 4;
                goto block_16;
            }
        } else {
            goto block_16;
        }
    } else {
        sp5C = 1;
block_16:
        if ((sp5C != 4) || (sp28 -= 1, ((sp28 >= 0) == 0))) {
            __siUnlock();
        } else {
            goto loop_5;
        }
    }
    return sp5C;
}
