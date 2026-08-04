#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of func_8004D4A8 (initial). */

void func_8007BA98(u32, s32);                         /* extern */
void func_8007BCA8(void);                             /* extern */
s32 func_8007CD08(Unk*, s32*, s32);                       /* extern */
s32 func_8008E518(Unk*, s32, s32, s32, s32, s32, s32);    /* extern */
extern char *D_80090CF8;
extern char *D_80090CFC;
extern s32 D_80090D00;
extern s32 D_80090D04;
extern char *D_80090D08;
extern s32 D_80090D0C;
extern char *D_80090D10;
extern u8 D_8016DBD0;
extern s32 D_8016DF70;
extern s32 D_801A3000;
extern s32 D_803DA400;

void func_8004D1C8(s32 arg0, u8 *arg1, s32 arg2) {
    s32 sp38;
    s32 sp20;
    s32 temp_a1;
    s32 temp_s4;
    s32 var_s2;
    s32 var_s3;
    s32 var_v1;
    u8 *var_s1;
    u8 temp_v0;
    u8 temp_v0_2;

    var_s3 = arg0;
    var_s2 = arg2;
    var_s1 = arg1;
    temp_s4 = var_s3 & 0x3F;
    if (temp_s4 != 0) {
        func_8007BA98(&D_8016DBD0, 0x40);
        func_8008E518(&sp20, 0, 0, var_s3 & ~0x3F, &D_8016DBD0, 0x40, &D_8016DF70);
        func_8007CD08(&D_8016DF70, &sp38, 1);
        temp_a1 = var_s2 + temp_s4;
        var_v1 = temp_s4;
        if (temp_a1 < 0x41) {
            if (var_v1 < temp_a1) {
                do {
                    temp_v0 = (&D_8016DBD0)[var_v1];
                    var_v1 += 1;
                    *var_s1 = temp_v0;
                    var_s1 += 1;
                } while (var_v1 < temp_a1);
            }
        } else {
            if (var_v1 < 0x40) {
                do {
                    var_s2 -= 1;
                    var_s3 += 1;
                    temp_v0_2 = (&D_8016DBD0)[var_v1];
                    var_v1 += 1;
                    *var_s1 = temp_v0_2;
                    var_s1 += 1;
                } while (var_v1 < 0x40);
            }
            func_8007BCA8();
            goto block_8;
        }
    } else {
block_8:
        func_8007BA98(var_s1, var_s2);
        func_8008E518(&sp20, 0, 0, var_s3, var_s1, var_s2, &D_8016DF70);
        func_8007CD08(&D_8016DF70, &sp38, 1);
    }
}

void func_8004D330(void) {
    D_80090D10 = D_80090CF8;
}

void func_8004D344(void) {
    D_80090CF8 = D_80090D10;
}

void func_8004D358(void) {
    if (D_80090CFC != NULL) {
        D_80090CF8 = D_80090CFC;
        return;
    }
    D_80090CF8 = &D_801A3000;
}

char *func_8004D380(void) {
    if (D_80090D08 == NULL) {
        return D_80090CF8;
    }
    return D_80090D08;
}

void func_8004D3A8(s32 arg0, s32 arg1) {
    s32 temp_v0_2;
    s32 var_v1;
    s8 *temp_v0;

    var_v1 = 0;
    D_80090D00 = arg0;
    D_80090D04 = arg1;
    if (arg1 > 0) {
        do {
            temp_v0 = D_80090D00 + var_v1;
            var_v1 += 1;
            *temp_v0 = 0;
        } while (var_v1 < arg1);
    }
    if (D_80090D00 & 0xF) {
        do {
            temp_v0_2 = D_80090D00 + 1;
            D_80090D00 = temp_v0_2;
            D_80090D04 -= 1;
        } while (temp_v0_2 & 0xF);
    }
}

void func_8004D420(void) {
    D_80090D00 = 0;
    D_80090D04 = 0;
}

char *func_8004D434(s32 arg0) {
    char *temp_a0_2;
    char *temp_v0;
    char *temp_v0_2;
    s32 temp_a0;

    temp_a0 = (arg0 + 0xF) & ~0xF;
    if ((D_80090D08 != NULL) && (D_80090D0C >= temp_a0)) {
        temp_v0_2 = D_80090D08;
        D_80090D08 = temp_v0_2 + temp_a0;
        D_80090D0C -= temp_a0;
        return temp_v0_2;
    }
    temp_a0_2 = D_80090CF8 + temp_a0;
    temp_v0 = D_80090CF8;
    if ((s32) &D_803DA400 >= (s32) temp_a0_2) {
        D_80090CF8 = temp_a0_2;
        return temp_v0;
    }
    return NULL;
}

void func_8004D4A8(void) {

}
