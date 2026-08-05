#include "ultra64.h"
s32 func_8008F5A8(void *, s32, s32, void *);              /* extern */
extern s32 byteCopyEnd;

s32 func_8008EE3C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;

    temp_v0 = func_8008F5A8(&byteCopyEnd, arg0, arg1, &arg2);
    if (temp_v0 >= 0) {
        *((char*)(s32)arg0 + temp_v0) = 0;
    }
    return temp_v0;
}

char *byteCopy(char *arg0, u8 *arg1, s32 arg2) {
    s32 var_a2;
    Unk *var_v1;
    u8 temp_t6;
    char *var_v0;

    var_a2 = arg2;
    var_v0 = arg0;
    var_v1 = arg1;
    if (var_a2 != 0) {
        do {
            temp_t6 = var_v1->unk0;
            var_a2 -= 1;
            var_v0 += 1;
            var_v1 += 1;
            (*(f32 *)((char *)(var_v0) - 0x1)) = temp_t6;
        } while (var_a2 != 0);
    }
    return arg0;
}

s32 func_8008EEC4(u8 *arg0) {
    Unk *var_v1;
    u8 temp_t7;

    var_v1 = arg0;
    if (*arg0 != 0) {
        do {
            temp_t7 = var_v1->unk1;
            var_v1 += 1;
        } while (temp_t7 != 0);
    }
    return (char*)var_v1 - (char*)arg0;
}

u8 *func_8008EEEC(u8 *arg0, s32 arg1) {
    Unk *var_a0;
    u8 var_v1;

    var_a0 = arg0;
    var_v1 = var_a0->unk0;
    if ((arg1 & 0xFF) != var_v1) {
loop_1:
        if (var_v1 == 0) {
            return NULL;
        }
        var_v1 = var_a0->unk1;
        var_a0 += 1;
        if ((arg1 & 0xFF) == var_v1) {
            /* Duplicate return node #4. Try simplifying control flow for better match */
            return var_a0;
        }
        goto loop_1;
    }
    return var_a0;
}
