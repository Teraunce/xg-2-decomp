#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x4];
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
} UnkStruct_arg0;
typedef struct {
    /* 0x00 */ s32 unk0;
} UnkStruct_var_t4;
typedef struct {
    /* 0x00 */ s32 unk0;
} UnkStruct_var_t6;

s32 osRecvMesg(Unk*, s32*, s32);                         /* extern */
s32 osSiRawStartDma(s32, s32);                          /* extern */
s32 __siLock();                                  /* extern */
void __siUnlock();                                  /* extern */
extern s8 gSiLocked;
extern s32 gSiReadBuf;
extern s32 gContPakDmaBufB;

s32 contPakSiWrite(UnkStruct_arg0 *arg0) {
    s32 sp4C;
    s32 sp48;
    char *sp44;
    s32 sp1C[13];
    UnkStruct_var_t4 *var_t4;
    UnkStruct_var_t6 *var_t6;
    s32 temp_at;
    s32 temp_t0;
    s32 temp_t1;
    s32 sp1E;
    s32 sp42;
    char *temp_t7;

    sp44 = &gSiReadBuf;
    __siLock();
    gSiLocked = 3;
    osSiRawStartDma(1, (arg0->unk8 << 6) + &gContPakDmaBufB);
    osRecvMesg(arg0->unk4, 0, 1);
    sp48 = osSiRawStartDma(0, &gSiReadBuf);
    osRecvMesg(arg0->unk4, 0, 1);
    sp44 = &gSiReadBuf;
    if (arg0->unk8 != 0) {
        sp4C = 0;
        if (arg0->unk8 > 0) {
            do {
                temp_t1 = sp4C + 1;
                sp4C = temp_t1;
                sp44 += 1;
            } while (temp_t1 < arg0->unk8);
        }
    }
    var_t6 = sp44;
    var_t4 = &sp1C;
    temp_t7 = var_t6 + 0x24;
    do {
        temp_at = (s32) var_t6->unk0;
        var_t6 += 0xC;
        var_t4 += 0xC;
        (*(f32 *)((char *)(var_t4) - 0xC)) = temp_at;
        (*(f32 *)((char *)(var_t4) - 0x8)) = (s32) (s32) (*(f32 *)((char *)(var_t6) - 0x8));
        (*(f32 *)((char *)(var_t4) - 0x4)) = (s32) (s32) (*(f32 *)((char *)(var_t6) - 0x4));
    } while ((char*)var_t6 != temp_t7);
    var_t4->unk0 = (s32) (s32) var_t6->unk0;
    temp_t0 = (s32) (sp1E & 0xC0) >> 4;
    sp48 = temp_t0;
    if ((temp_t0 == 0) && (sp42 != 0xEB)) {
        sp48 = 4;
    }
    __siUnlock();
    return sp48;
}
