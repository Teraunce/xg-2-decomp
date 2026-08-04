#include "ultra64.h"
s32 func_8007CD08(Unk*, s32*, s32);                       /* extern */
s32 func_80087C78(s32, s32);                          /* extern */
void func_8008B3E8(s32);                                 /* extern */
s32 func_8008B4E4(void *, s32 (*)[]);                    /* extern */
extern s32 D_8018ADB8;

s32 func_8008C788(s32 arg0, s32 arg1) {
    Unk sp_buf[8];
    char *sp = (char*)sp_buf; /* FIXME: raw stack pointer */
    s32 sp34;
    s32 sp30[2];
    s32 sp2F;
    Unk *temp_t4;
    u8 temp_t8;
    s32 sp1C;

    sp34 = 0;
    func_8008B3E8(0);
    sp34 = func_80087C78(1, &D_8018ADB8);
    func_8007CD08(arg0, &sp30, 1);
    sp34 = func_80087C78(0, &D_8018ADB8);
    func_8007CD08(arg0, &sp30, 1);
    func_8008B4E4(&sp2F, (s32 (*)[]) &sp1C);
    temp_t8 = ((Unk*)(sp + (arg1 * 4)))->unk1E;
    if ((temp_t8 & 1) && (temp_t8 & 2)) {
        return 2;
    }
    temp_t4 = (Unk*)((char*)&sp1C + arg1);
    if ((temp_t4->unk3 != 0) || !(temp_t4->unk2 & 1)) {
        return 1;
    }
    if (((Unk*)(sp + (arg1 * 4)))->unk1E & 4) {
        return 4;
    }
    return sp34;
}
