#include "ultra64.h"
s32 osRecvMesg(Unk*, s32*, s32);                         /* extern */
s32 osSiRawStartDma(s32, s32);                          /* extern */
s32 __siLock();                                  /* extern */
void __siUnlock();                                  /* extern */
u8 func_800890C8(u8*);                           /* extern */
void func_8008A114(s32, u16);                          /* extern */
s32 contPakProbe(s32, s32);                        /* extern */
extern s8 D_8018AD68;
extern s32 D_8018ADB8;

s32 osContPakRead(s32 arg0, s32 arg1, u16 arg2, u8 *arg3) {
    Unk *sp = NULL; /* $sp base — used as Unk byte-ptr into local stack (nonmatching) */
    s32 sp2E = 0; /* sp+0x2E — stack slot read before write (nonmatching) */
    s32 sp52 = 0; /* sp+0x52 — stack slot read before write (nonmatching) */
    s32 sp5C;
    s32 sp58;
    char *sp54;
    s32 sp2C;
    s32 sp28;
    u8 sp27;
    Unk *var_t6;
    Unk *var_t7;
    s32 temp_at;
    s32 temp_t2;
    s32 temp_t3;
    s32 temp_t4;
    char *temp_t9;

    sp5C = 0;
    sp54 = &D_8018ADB8;
    sp28 = 2;
    __siLock();
    D_8018AD68 = 2;
    func_8008A114(arg1, arg2);
    sp5C = osSiRawStartDma(1, &D_8018ADB8);
    osRecvMesg(arg0, 0, 1);
loop_1:
    sp5C = osSiRawStartDma(0, &D_8018ADB8);
    osRecvMesg(arg0, 0, 1);
    sp54 = &D_8018ADB8;
    if (arg1 != 0) {
        sp58 = 0;
        if (arg1 > 0) {
            do {
                temp_t4 = sp58 + 1;
                sp58 = temp_t4;
                sp54 += 1;
            } while (temp_t4 < arg1);
        }
    }
    var_t7 = sp54;
    var_t6 = &sp2C;
    temp_t9 = var_t7 + 0x24;
    do {
        temp_at = (s32) var_t7->unk0;
        var_t7 += 0xC;
        var_t6 += 0xC;
        *(s32*)((char*)var_t6 - 12) = temp_at;
        *(s32*)((char*)var_t6 - 8)= (s32) (s32) *(s32*)((char*)var_t7 - 8)
        *(s32*)((char*)var_t6 - 4)= (s32) (s32) *(s32*)((char*)var_t7 - 4)
    } while ((char*)var_t7 != temp_t9);
    var_t6->unk0 = (s32) (s32) var_t7->unk0;
    temp_t2 = (s32) (sp2E & 0xC0) >> 4;
    sp5C = temp_t2;
    if (temp_t2 == 0) {
        sp27 = func_800890C8(&sp2C + 6);
        if (sp27 != sp52) {
            sp5C = contPakProbe(arg0, arg1);
            if (sp5C != 0) {
                __siUnlock();
            } else {
                sp5C = 4;
                goto block_15;
            }
        } else {
            sp58 = 0;
            do {
                *arg3 = ((Unk *)(sp + sp58))->unk32;
                temp_t3 = sp58 + 1;
                sp58 = temp_t3;
                arg3 += 1;
            } while (temp_t3 < 0x20);
            goto block_15;
        }
    } else {
        sp5C = 1;
block_15:
        if ((sp5C != 4) || (sp28 -= 1, ((sp28 >= 0) == 0))) {
            __siUnlock();
        } else {
            goto loop_1;
        }
    }
    return sp5C;
}
