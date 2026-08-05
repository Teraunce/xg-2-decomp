#include "ultra64.h"
s32 __osEnqueueWait(void *);                            /* extern */
s32 __osPopQueue(void *);                          /* extern */
s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
void osStartThread(Unk*);                               /* extern */
extern Unk *__osRunningThread;
extern s32 D_80096480;
extern s32 D_80096488;

s32 func_8008E628(Unk *arg0, s32 arg1, s32 arg2) {
    s32 temp_s0;
    s32 temp_t7;

    temp_s0 = osDisableInt();
    if (arg0->unk8 >= arg0->unk10) {
loop_1:
        if (arg2 == 1) {
            __osRunningThread->unk10 = 8;
            __osEnqueueWait(arg0 + 4);
            if (arg0->unk8 < arg0->unk10) {
                goto block_5;
            }
            goto loop_1;
        }
        osRestoreInt(temp_s0);
        return -1;
    }
block_5:
    temp_t7 = arg0->unk10;
    arg0->unkC = (s32) ((s32) ((arg0->unkC + temp_t7) - 1) % temp_t7);
    *(s32*)(s32)(arg0->unk14 + (arg0->unkC * 4)) = arg1;
    arg0->unk8 = (s32) (arg0->unk8 + 1);
    if (((Unk*)(s32)arg0->unk0)->unk0 != 0) {
        osStartThread(__osPopQueue(arg0));
    }
    osRestoreInt(temp_s0);
    return 0;
}

s32 func_8008E778(void) {
    if (D_80096480 == 0) {
        return 0;
    }
    return D_80096488;
}

s32 func_8008E7A8(s32 arg0, s32 arg1, s32 arg2) {
    s16 temp_v0_11;
    s16 temp_v0_3;
    s16 temp_v1;
    s16 temp_v1_5;
    s32 temp_a3;
    s32 temp_t0;
    s32 temp_t0_2;
    s32 temp_t0_3;
    s32 temp_t0_4;
    s32 temp_t1;
    s32 temp_t1_2;
    s32 temp_t1_3;
    s32 temp_t1_4;
    s32 temp_t2;
    s32 temp_t2_2;
    s32 temp_t3;
    s32 temp_t3_2;
    s32 temp_t4;
    s32 temp_t4_2;
    s32 temp_t5;
    s32 temp_t5_2;
    s32 temp_v0;
    s32 temp_v0_13;
    s32 temp_v0_14;
    s32 temp_v0_15;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_9;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_6;
    s32 temp_v1_7;
    s32 temp_v1_8;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a2;
    s8 *var_a0_3;
    s8 temp_v0_10;
    s8 temp_v0_12;
    s8 temp_v0_16;
    s8 temp_v0_2;
    s8 temp_v0_4;
    s8 temp_v0_8;
    Unk *var_a1_3;

    var_a0 = arg0;
    var_a1 = arg1;
    var_a2 = arg2;
    temp_a3 = var_a1;
    if ((var_a2 != 0) && (var_a0 != var_a1)) {
        if ((var_a1 >= var_a0) && (var_a1 < (var_a0 + var_a2))) {
            var_a0_2 = var_a0 + var_a2;
            var_a1_2 = var_a1 + var_a2;
            if (var_a2 >= 0x10) {
                temp_v0 = var_a0_2 & 3;
                if (temp_v0 == (var_a1_2 & 3)) {
                    switch (temp_v0) {              /* switch 2; irregular */
                    case 0:                         /* switch 2 */
                        break;
                    default:                        /* switch 2 */
                        temp_v0_2 = *(u8*)((char*)(s32)var_a0_2 - 1)
                        var_a0_2 -= 1;
                        var_a1_2 -= 1;
                        var_a2 -= 1;
                        *(s8*)(s32)var_a1_2 = temp_v0_2;
                        break;
                    case 2:                         /* switch 2 */
                        temp_v0_3 = *(u16*)((char*)(s32)var_a0_2 - 2)
                        var_a0_2 -= 2;
                        var_a1_2 -= 2;
                        var_a2 -= 2;
                        *(s8*)(s32)var_a1_2 = temp_v0_3;
                        break;
                    case 3:                         /* switch 2 */
                        temp_v0_4 = *(u8*)((char*)(s32)var_a0_2 - 1)
                        temp_v1 = *(u8*)((char*)(s32)var_a0_2 - 3)
                        var_a0_2 -= 3;
                        var_a1_2 -= 3;
                        var_a2 -= 3;
                        ((Unk*)(s32)var_a1_2)->unk2 = temp_v0_4;
                        ((Unk*)(s32)var_a1_2)->unk0 = temp_v1;
                        break;
                    }
loop_35:
                    if (var_a2 >= 0x20) {
                        temp_v0_5 = *(s32*)((char*)(s32)var_a0_2 - 4)
                        temp_v1_2 = *(s32*)((char*)(s32)var_a0_2 - 8)
                        temp_t0 = *(s32*)((char*)(s32)var_a0_2 - 0xC);
                        temp_t1 = *(s32*)((char*)(s32)var_a0_2 - 10)
                        temp_t2 = *(s32*)((char*)(s32)var_a0_2 - 14)
                        temp_t3 = *(s32*)((char*)(s32)var_a0_2 - 18)
                        temp_t4 = *(s32*)((char*)(s32)var_a0_2 - 0x1C);
                        temp_t5 = *(s32*)((char*)(s32)var_a0_2 - 20)
                        var_a0_2 -= 0x20;
                        var_a1_2 -= 0x20;
                        var_a2 -= 0x20;
                        ((Unk*)(s32)var_a1_2)->unk1C = temp_v0_5;
                        ((Unk*)(s32)var_a1_2)->unk18 = temp_v1_2;
                        ((Unk*)(s32)var_a1_2)->unk14 = temp_t0;
                        ((Unk*)(s32)var_a1_2)->unk10 = temp_t1;
                        ((Unk*)(s32)var_a1_2)->unkC = temp_t2;
                        ((Unk*)(s32)var_a1_2)->unk8 = temp_t3;
                        ((Unk*)(s32)var_a1_2)->unk4 = temp_t4;
                        ((Unk*)(s32)var_a1_2)->unk0 = temp_t5;
                        goto loop_35;
                    }
loop_37:
                    if (var_a2 >= 0x10) {
                        temp_v0_6 = *(s32*)((char*)(s32)var_a0_2 - 4)
                        temp_v1_3 = *(s32*)((char*)(s32)var_a0_2 - 8)
                        temp_t0_2 = *(s32*)((char*)(s32)var_a0_2 - 0xC);
                        temp_t1_2 = *(s32*)((char*)(s32)var_a0_2 - 10)
                        var_a0_2 -= 0x10;
                        var_a1_2 -= 0x10;
                        var_a2 -= 0x10;
                        ((Unk*)(s32)var_a1_2)->unkC = temp_v0_6;
                        ((Unk*)(s32)var_a1_2)->unk8 = temp_v1_3;
                        ((Unk*)(s32)var_a1_2)->unk4 = temp_t0_2;
                        ((Unk*)(s32)var_a1_2)->unk0 = temp_t1_2;
                        goto loop_37;
                    }
loop_39:
                    if (var_a2 >= 4) {
                        temp_v0_7 = *(s32*)((char*)(s32)var_a0_2 - 4)
                        var_a0_2 -= 4;
                        var_a1_2 -= 4;
                        var_a2 -= 4;
                        *(s8*)(s32)var_a1_2 = temp_v0_7;
                        goto loop_39;
                    }
                }
            }
            if (var_a2 != 0) {
                var_a0_3 = (s8*)(s32)(var_a0_2 - 1);
                var_a1_3 = (Unk*)(s32)(var_a1_2 - 1);
                temp_v1_4 = (s32)(var_a0_3 - var_a2);
                do {
                    temp_v0_8 = *var_a0_3;
                    var_a0_3 -= 1;
                    var_a1_3 -= 1;
                    var_a1_3->unk1 = temp_v0_8;
                } while (var_a0_3 != (s8*)(s32)temp_v1_4);
                return temp_a3;
            }
            /* Duplicate return node #10. Try simplifying control flow for better match */
            return temp_a3;
        }
        if (var_a2 >= 0x10) {
            temp_v0_9 = var_a0 & 3;
            if (temp_v0_9 == (var_a1 & 3)) {
                switch (temp_v0_9) {                /* switch 1; irregular */
                case 0:                             /* switch 1 */
                    break;
                default:                            /* switch 1 */
                    temp_v0_10 = ((Unk*)(s32)var_a0)->unk0;
                    var_a0 += 1;
                    var_a1 += 1;
                    var_a2 -= 1;
                    *(u8*)((char*)(s32)var_a1 - 1)= temp_v0_10;
                    break;
                case 2:                             /* switch 1 */
                    temp_v0_11 = (s16) ((Unk*)(s32)var_a0)->unk0;
                    var_a0 += 2;
                    var_a1 += 2;
                    var_a2 -= 2;
                    *(u16*)((char*)(s32)var_a1 - 2)= temp_v0_11;
                    break;
                case 1:                             /* switch 1 */
                    temp_v0_12 = ((Unk*)(s32)var_a0)->unk0;
                    temp_v1_5 = ((Unk*)(s32)var_a0)->unk1;
                    var_a0 += 3;
                    var_a1 += 3;
                    var_a2 -= 3;
                    *(u8*)((char*)(s32)var_a1 - 3)= temp_v0_12;
                    *(u16*)((char*)(s32)var_a1 - 2)= temp_v1_5;
                    break;
                }
loop_17:
                if (var_a2 >= 0x20) {
                    temp_v0_13 = ((Unk*)(s32)var_a0)->unk0;
                    temp_v1_6 = ((Unk*)(s32)var_a0)->unk4;
                    temp_t0_3 = ((Unk*)(s32)var_a0)->unk8;
                    temp_t1_3 = ((Unk*)(s32)var_a0)->unkC;
                    temp_t2_2 = ((Unk*)(s32)var_a0)->unk10;
                    temp_t3_2 = ((Unk*)(s32)var_a0)->unk14;
                    temp_t4_2 = ((Unk*)(s32)var_a0)->unk18;
                    temp_t5_2 = ((Unk*)(s32)var_a0)->unk1C;
                    var_a0 += 0x20;
                    var_a1 += 0x20;
                    var_a2 -= 0x20;
                    *(s32*)((char*)(s32)var_a1 - 20)= temp_v0_13;
                    *(s32*)((char*)(s32)var_a1 - 0x1C) = temp_v1_6;
                    *(s32*)((char*)(s32)var_a1 - 18)= temp_t0_3;
                    *(s32*)((char*)(s32)var_a1 - 14)= temp_t1_3;
                    *(s32*)((char*)(s32)var_a1 - 10)= temp_t2_2;
                    *(s32*)((char*)(s32)var_a1 - 0xC) = temp_t3_2;
                    *(s32*)((char*)(s32)var_a1 - 8)= temp_t4_2;
                    *(s32*)((char*)(s32)var_a1 - 4)= temp_t5_2;
                    goto loop_17;
                }
loop_19:
                if (var_a2 >= 0x10) {
                    temp_v0_14 = ((Unk*)(s32)var_a0)->unk0;
                    temp_v1_7 = ((Unk*)(s32)var_a0)->unk4;
                    temp_t0_4 = ((Unk*)(s32)var_a0)->unk8;
                    temp_t1_4 = ((Unk*)(s32)var_a0)->unkC;
                    var_a0 += 0x10;
                    var_a1 += 0x10;
                    var_a2 -= 0x10;
                    *(s32*)((char*)(s32)var_a1 - 10)= temp_v0_14;
                    *(s32*)((char*)(s32)var_a1 - 0xC) = temp_v1_7;
                    *(s32*)((char*)(s32)var_a1 - 8)= temp_t0_4;
                    *(s32*)((char*)(s32)var_a1 - 4)= temp_t1_4;
                    goto loop_19;
                }
loop_21:
                if (var_a2 >= 4) {
                    temp_v0_15 = ((Unk*)(s32)var_a0)->unk0;
                    var_a0 += 4;
                    var_a1 += 4;
                    var_a2 -= 4;
                    *(s32*)((char*)(s32)var_a1 - 4)= temp_v0_15;
                    goto loop_21;
                }
            }
        }
        if (var_a2 != 0) {
            temp_v1_8 = var_a0 + var_a2;
            do {
                temp_v0_16 = ((Unk*)(s32)var_a0)->unk0;
                var_a0 += 1;
                var_a1 += 1;
                *(u8*)((char*)(s32)var_a1 - 1)= temp_v0_16;
            } while (var_a0 != temp_v1_8);
        }
        /* Duplicate return node #10. Try simplifying control flow for better match */
        return temp_a3;
    }
    return temp_a3;
}

void bzero(s32 arg0, s32 arg1) {
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a1_3;
    s32 temp_a3;
    s32 temp_a3_2;
    s32 temp_a3_3;
    s32 temp_a3_4;
    s32 temp_v1;
    s32 var_a0;
    s32 var_a1;

    var_a0 = arg0;
    var_a1 = arg1;
    if (var_a1 >= 0xC) {
        temp_v1 = -var_a0 & 3;
        temp_a1 = var_a1 - temp_v1;
        if (temp_v1 != 0) {
            ((Unk*)(s32)var_a0)->unk0 = 0;
            var_a0 += temp_v1;
        }
        temp_a3 = temp_a1 & ~0x1F;
        temp_a1_2 = temp_a1 - temp_a3;
        if (temp_a3 != 0) {
            temp_a3_2 = temp_a3 + var_a0;
            do {
                var_a0 += 0x20;
                *(s32*)((char*)(s32)var_a0 - 20)= 0;
                *(s32*)((char*)(s32)var_a0 - 0x1C) = 0;
                *(s32*)((char*)(s32)var_a0 - 18)= 0;
                *(s32*)((char*)(s32)var_a0 - 14)= 0;
                *(s32*)((char*)(s32)var_a0 - 10)= 0;
                *(s32*)((char*)(s32)var_a0 - 0xC) = 0;
                *(s32*)((char*)(s32)var_a0 - 8)= 0;
                *(s32*)((char*)(s32)var_a0 - 4)= 0;
            } while (var_a0 != temp_a3_2);
        }
        temp_a3_3 = temp_a1_2 & ~3;
        var_a1 = temp_a1_2 - temp_a3_3;
        if (temp_a3_3 != 0) {
            temp_a3_4 = temp_a3_3 + var_a0;
            do {
                var_a0 += 4;
                *(s32*)((char*)(s32)var_a0 - 4)= 0;
            } while (var_a0 != temp_a3_4);
        }
    }
    if (var_a1 > 0) {
        temp_a1_3 = var_a1 + var_a0;
        do {
            var_a0 += 1;
            *(u8*)((char*)(s32)var_a0 - 1)= 0;
        } while (var_a0 != temp_a1_3);
    }
}

s64 func_8008EB58(u64 arg0, s32 arg1, s64 arg2, s32 arg3) {
    return (s64) (arg0 >> arg2) >> 0x20;
}

s64 func_8008EB84(u64 arg0, s32 arg1, u64 arg2, s32 arg3) {
    return (s64) (arg0 % arg2) >> 0x20;
}

s64 __udivdi3(u64 arg0, s32 arg1, u64 arg2, s32 arg3) {
    return (s64) (arg0 / arg2) >> 0x20;
}

s64 func_8008EBFC(s64 arg0, s32 arg1, s64 arg2, s32 arg3) {
    return (s64) (arg0 << arg2) >> 0x20;
}

s64 func_8008EC28(u64 arg0, s32 arg1, u64 arg2, s32 arg3) {
    return (s64) (arg0 % arg2) >> 0x20;
}

s64 func_8008EC64(s64 arg0, s32 arg1, s64 arg2, s32 arg3) {
    if ((arg2 == -1) && (arg0 == (1 << 0x3F))) {
        M2C_BREAK(6);
    }
    return (s64) (arg0 / arg2) >> 0x20;
}

s64 __muldi3(s64 arg0, s32 arg1, s64 arg2, s32 arg3) {
    return (s64) (arg0 * arg2) >> 0x20;
}

void func_8008ECF0(u64 *arg0, u64 *arg1, u64 arg2, s32 arg3, s16 arg4) {
    *arg0 = arg2 / (u64) arg4;
    *arg1 = arg2 % (u64) arg4;
}
