#include "ultra64.h"
void func_8007DA48(Unk*, void**);                       /* extern */

void func_8007E8E4(Unk *arg0, s32 arg1, s32 arg2) {
    s32 var_s0;
    s32 var_s1;

    arg0->unk10 = 0;
    arg0->unk8 = 0;
    arg0->unkC = 0;
    arg0->unk0 = 0;
    arg0->unk4 = 0;
    var_s0 = 0;
    if (arg2 > 0) {
        var_s1 = arg1;
        do {
            func_8007DA48(var_s1, arg0);
            var_s0 += 1;
            var_s1 += 0x1C;
        } while (var_s0 != arg2);
    }
}

void func_8007E958(Unk *arg0, char *arg1, s32 arg2) {
    s32 temp_a1;
    s32 var_a3;
    Unk *var_v0;
    u8 temp_t6;
    u8 temp_t8;
    Unk *var_v1;

    var_v0 = arg0;
    var_v1 = arg1;
    var_a3 = 0;
    if (arg2 > 0) {
        temp_a1 = arg2 & 3;
        if (temp_a1 != 0) {
            do {
                temp_t6 = var_v0->unk0;
                var_a3 += 1;
                var_v1 += 1;
                var_v0 += 1;
                *(u8*)((char*)var_v1 - 1)= temp_t6;
            } while (temp_a1 != var_a3);
            if (var_a3 != arg2) {
                goto loop_4;
            }
        } else {
            do {
loop_4:
                var_a3 += 4;
                var_v1 += 4;
                *(s32*)((char*)var_v1 - 4)= (u8) var_v0->unk0;
                temp_t8 = var_v0->unk1;
                var_v0 += 4;
                *(u8*)((char*)var_v1 - 3)= temp_t8;
                *(u16*)((char*)var_v1 - 2)= (u8) *(u16*)((char*)var_v0 - 2)
                *(u8*)((char*)var_v1 - 1)= (u8) *(u8*)((char*)var_v0 - 1)
            } while (var_a3 != arg2);
        }
    }
}
