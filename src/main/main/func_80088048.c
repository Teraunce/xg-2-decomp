#include "ultra64.h"
void func_80088240(s32, s32);
/* Warning: missing "jr $ra" in last block of func_80088240 (initial). */

void func_8007BCD8(Unk*, s32, s32);                       /* extern */
s32 func_8007C948();                                /* extern */
s32 func_8007CD08(Unk*, s32*, s32);                       /* extern */
s32 func_80087C78(s32, s32);                          /* extern */
void func_80088310(s32);                                 /* extern */
s32 func_80088408(void *, s32, s32, s32, s32, s32, s32);       /* extern */
u64 func_8008EBC0(s32, u32, s32, s32);                  /* extern */
s32 func_8008ECC0(s32, s32, s32, s32);                  /* extern */
extern s32 D_80095280;
extern s32 D_80095284;
extern s32 D_80096380;
extern s32 D_8018AD28;
extern s8 D_8018AD68;
extern u8 D_8018AD69;
extern s32 D_8018AD90;
extern s32 D_8018ADA8;

s32 func_80088048(char *arg0, s32 arg1, s32 arg2) {
    s32 sp7C;
    s32 sp78;
    u32 sp74;
    u32 sp70;
    s32 sp50;
    s32 sp38;
    u32 sp34;
    s32 sp30;
    u32 sp2C;
    s32 sp28;
    s32 temp_ret_2;
    s32 temp_ret_4;
    u32 temp_ret;
    u64 temp_ret_3;
    u64 temp_ret_5;
    u64 temp_v0;

    sp78 = 0;
    if (D_80096380 != 0) {
        return 0;
    }
    D_80096380 = 1;
    temp_ret = func_8007C948();
    sp70 = temp_ret;
    sp74 = (u32) (u64) temp_ret;
    temp_ret_2 = func_8008ECC0(0, 0x7A120, D_80095280, D_80095284);
    sp30 = temp_ret_2;
    sp34 = (u32) (u64) temp_ret_2;
    temp_ret_3 = func_8008EBC0(sp30, sp34, 0, 0xF4240);
    temp_v0 = temp_ret_3;
    if ((temp_v0 >= sp70) && ((sp70 < temp_v0) || (sp74 < (u32) temp_ret_3))) {
        func_8007BCD8(&sp38, &sp7C, 1);
        temp_ret_4 = func_8008ECC0(0, 0x7A120, D_80095280, D_80095284);
        sp28 = temp_ret_4;
        sp2C = (u32) (u64) temp_ret_4;
        temp_ret_5 = func_8008EBC0(sp28, sp2C, 0, 0xF4240);
        sp30 = temp_ret_5;
        sp34 = (u32) temp_ret_5;
        func_80088408(&sp50, sp30 - (s32)sp70, sp34 - sp74, 0, 0, (s32)&sp38, (s32)&sp7C);
        func_8007CD08(&sp38, &sp7C, 1);
    }
    D_8018AD69 = 4;
    func_80088310(0);
    sp78 = func_80087C78(1, &D_8018AD28);
    func_8007CD08(arg0, &sp7C, 1);
    sp78 = func_80087C78(0, &D_8018AD28);
    func_8007CD08(arg0, &sp7C, 1);
    func_80088240(arg1, arg2);
    D_8018AD68 = 0;
    func_80087D28();
    func_8007BCD8(&D_8018AD90, &D_8018ADA8, 1);
    return sp78;
}

void func_80088240(s32 arg1, s32 arg2) {

}
