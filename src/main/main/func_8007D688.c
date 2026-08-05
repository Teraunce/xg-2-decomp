#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x3];
    /* 0x03 */ s32 unk3;
    /* 0x07 */ u8 pad07[0x7];
    /* 0x0E */ s32 unkE;
} UnkStruct_arg0;
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad04[0x4];
    /* 0x08 */ s32 unk8;
    /* 0x09 */ s32 unk9;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_temp_t8;
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ char *unk8;
    /* 0x0C */ u8 pad0C[0x2];
    /* 0x0E */ s32 unkE;
} UnkStruct_temp_t9;
typedef struct {
    /* 0x00 */ u8 pad00[0x10];
    /* 0x10 */ char *unk10;
} UnkStruct_var_v1;

s32 func_8007D708(u32 arg0);                        /* static */

s32 osVirtualToPhysical(u32 arg0) {
    if ((arg0 >= 0x80000000U) && (arg0 < 0xA0000000U)) {
        return arg0 & 0x1FFFFFFF;
    }
    if ((arg0 >= 0xA0000000U) && (arg0 < 0xC0000000U)) {
        return arg0 & 0x1FFFFFFF;
    }
    return func_8007D708(arg0);
}

s32 func_8007D708(u32 arg0) {
    s32 var_v0;
    u32 temp_t3;

    /* mtc0 $t1, $10 — write COP0 EntryHi (VPN for TLB probe) */
    /* tlbp          — probe TLB for EntryHi match */
    if (!(0 /* mfc0 $0: COP0 Index — bit31 set = miss */ & 0x80000000)) {
        /* tlbr          — read matched TLB entry into EntryLo0/EntryLo1/PageMask */
        temp_t3 = (u32) ((s32)(0 /* mfc0 $5: COP0 PageMask */) + 0x2000) >> 1;
        if (!(temp_t3 & arg0)) {
            var_v0 = 0 /* mfc0 $2: COP0 EntryLo0 */;
        } else {
            var_v0 = 0 /* mfc0 $3: COP0 EntryLo1 */;
        }
        if (var_v0 & 2) {
            /* mtc0 $t0, $10 — restore COP0 EntryHi */
            return ((var_v0 & 0x3FFFFFC0) << 6) + (arg0 & (temp_t3 - 1));
        }
        goto block_6;
    }
block_6:
    /* mtc0 $t0, $10 — restore COP0 EntryHi */
    return -1;
}

void __osVirtualToPhysical_noop(void) {

}

void func_8007D7D8(UnkStruct_arg0 *arg0, s32 arg1, s32 arg3) {
    s32 temp_a2_2;
    s32 temp_a2_3;
    s32 var_v0;
    u8 temp_a2;
    UnkStruct_temp_t8 *temp_t8;
    UnkStruct_temp_t9 *temp_t9;
    UnkStruct_var_v1 *var_v1;

    if (arg0->unk3 == 0) {
        arg0->unk3 = 1U;
        var_v0 = 0;
        if (arg0->unkE > 0) {
            var_v1 = arg0;
            do {
                temp_t9 = var_v1->unk10 + arg1;
                var_v1->unk10 = temp_t9;
                if (temp_t9->unkE == 0) {
                    temp_t9->unkE = 1U;
                    temp_t9->unk0 = (s32) (temp_t9->unk0 + arg1);
                    temp_t8 = temp_t9->unk8 + arg1;
                    temp_t9->unk4 = (s32) (temp_t9->unk4 + arg1);
                    temp_t9->unk8 = temp_t8;
                    if (temp_t8->unk9 == 0) {
                        temp_a2 = temp_t8->unk8;
                        temp_t8->unk9 = 1U;
                        temp_t8->unk0 = (s32) (temp_t8->unk0 + arg3);
                        if (temp_a2 == 0) {
                            temp_a2_2 = temp_t8->unkC;
                            temp_t8->unk10 = (s32) (temp_t8->unk10 + arg1);
                            if (temp_a2_2 != 0) {
                                temp_t8->unkC = (s32) (temp_a2_2 + arg1);
                            }
                        } else if (temp_a2 == 1) {
                            temp_a2_3 = temp_t8->unkC;
                            if (temp_a2_3 != 0) {
                                temp_t8->unkC = (s32) (temp_a2_3 + arg1);
                            }
                        }
                    }
                }
                var_v0 += 1;
                var_v1 += 4;
            } while (var_v0 < arg0->unkE);
        }
    }
}
