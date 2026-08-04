#include "ultra64.h"
extern s32 D_80091E5C;
extern s32 D_80092828;
extern s32 D_8009282C;
extern s32 D_80092830;
extern s32 D_80092834;
extern s32 D_80092838;
extern s32 D_8009283C;
extern s32 D_80092840;
extern s32 D_80092A94;
extern s32 D_80170880;
extern s32 D_80173C28;
extern s32 D_80180908;
extern s32 D_80180B38;
extern s32 D_80181538;
extern s32 D_80181558;
extern s32 D_80181578;
extern s32 D_8018157C;
extern s32 D_80181580;

/*
 * func_8005C9BC — audio event sub-dispatcher (nonmatching).
 *
 * PERMANENTLY NONMATCHING — three reasons:
 *
 * 1. Non-standard ABI: $v1 is used as an input argument immediately after
 *    the prologue register saves: `sltiu $v0, $v1, 0x5`.  In standard MIPS
 *    ABI, $v0/$v1 are return-value registers, not argument registers.
 *    No C declaration can express this.
 *
 * 2. Three alabel markers: other functions branch INTO this function's body
 *    at three mid-body addresses.  m2c cannot represent cross-function
 *    entry points and rejects the file.
 *
 * 3. Dispatches via jr through jtbl_8004BDF0 (5 entries, index = v1,
 *    range check < 5): [0]=0x8005C9F4, [1]=..., [4]=0x8005CBC0.
 *    m2c marks any jr-from-table as nonmatching.
 *
 * Function size: 0x324 bytes.
 */
void func_8005C9BC(void) { /* nonmatching — see asm stub */ }

s32 func_8005CCE0(s16 arg0, f32 arg1, s32 arg2, s8 arg3, s32 arg4) {
    s32 temp_a0;
    s32 temp_v0;
    s32 var_t0;
    Unk *temp_v1;

    var_t0 = D_8009282C + 1;
    if (var_t0 >= 0x80) {
        var_t0 = 0;
    }
    if (var_t0 == D_80092828) {
        return 0;
    }
    temp_a0 = D_80092840;
    temp_v0 = temp_a0 + 1;
    D_80092840 = temp_v0;
    if (temp_v0 <= 0) {
        D_80092840 = 1;
    }
    temp_v1 = (D_8009282C * 0x14) + &D_80180B38;
    temp_v1->unk10 = arg3;
    temp_v1->unk0 = temp_a0;
    temp_v1->unk4 = 1;
    temp_v1->unk6 = arg0;
    temp_v1->unk8 = arg1;
    temp_v1->unkC = arg2;
    ((Unk*)((char*)&D_80180B38 + D_8009282C * 0x14))->unk11 = (s8) arg4;
    D_8009282C = var_t0;
    return temp_a0;
}

void func_8005CD90(s32 arg0, f32 arg1, s32 arg2, s8 arg3, s32 arg4) {
    s32 var_t0;
    Unk *temp_v0;

    var_t0 = D_8009282C + 1;
    if (var_t0 >= 0x80) {
        var_t0 = 0;
    }
    if (var_t0 != D_80092828) {
        temp_v0 = (D_8009282C * 0x14) + &D_80180B38;
        temp_v0->unk10 = arg3;
        temp_v0->unk0 = arg0;
        temp_v0->unk4 = 2;
        temp_v0->unk8 = arg1;
        temp_v0->unkC = arg2;
        ((Unk*)((char*)&D_80180B38 + D_8009282C * 0x14))->unk11 = (s8) arg4;
        D_8009282C = var_t0;
    }
}

void func_8005CE14(s32 arg0) {
    s32 var_a2;
    Unk *temp_v1;

    var_a2 = D_8009282C + 1;
    if (var_a2 >= 0x80) {
        var_a2 = 0;
    }
    if (var_a2 != D_80092828) {
        temp_v1 = (D_8009282C * 0x14) + &D_80180B38;
        temp_v1->unk0 = arg0;
        temp_v1->unk4 = 3;
        D_8009282C = var_a2;
    }
}

s32 func_8005CE68(s32 arg0, f32 *arg1, s32 *arg2, s32 *arg3) {
    Unk *var_v1;
    s32 var_t0;
    s32 var_t0_2;
    s32 var_t0_3;

    var_t0 = 0;
    var_v1 = &D_80180908;
loop_1:
    if (var_v1->unk0 != arg0) {
        var_t0 += 1;
        goto block_14;
    }
    if (var_v1->unk4 != 1) {
        var_t0 += 1;
block_14:
        var_v1 += 0x14;
        if (var_t0 >= 0x1C) {
            var_t0_2 = D_80092828;
            if (var_t0_2 != D_8009282C) {
                var_v1 = (var_t0_2 * 0x14) + &D_80180B38;
loop_17:
                if ((var_v1->unk0 != arg0) || (var_v1->unk4 != 1)) {
                    var_t0_2 += 1;
                    var_v1 += 0x14;
                    if (var_t0_2 >= 0x80) {
                        var_v1 = &D_80180B38;
                        var_t0_2 = 0;
                    }
                    if (var_t0_2 == D_8009282C) {
                        goto block_22;
                    }
                    goto loop_17;
                }
                goto block_7;
            }
block_22:
            var_t0_3 = 0;
            var_v1 = &D_80180908;
loop_23:
            if ((var_v1->unk0 != arg0) || (var_v1->unk4 != 1)) {
                var_t0_3 += 1;
                var_v1 += 0x14;
                if (var_t0_3 >= 0x1C) {
                    return 0;
                }
                goto loop_23;
            }
            goto block_7;
        }
        goto loop_1;
    }
block_7:
    if (arg1 != NULL) {
        *arg1 = var_v1->unk8;
    }
    if (arg2 != NULL) {
        *arg2 = var_v1->unkC;
    }
    if (arg3 != NULL) {
        *arg3 = (s32) var_v1->unk10;
    }
    return arg0;
}

void func_8005CF84(s32 arg0) {
    D_80092830 = arg0;
    D_80092838 = 1;
}

void func_8005CF9C(s32 arg0) {
    D_80092834 = arg0;
    D_80092838 = 1;
}

void func_8005CFB4(void) {
    D_8009283C = 1;
}

void func_8005CFC4(void) {
    D_80181578 = 0;
    D_8018157C = 0;
    D_80181580 = 0;
}

void func_8005CFE0(s32 arg0, s32 arg1) {
    s32 temp_v1;
    s32 var_a0;
    s32 var_a2;

    var_a2 = 0x40;
    if ((D_80092834 > 0) && (arg1 < D_80173C28)) {
        if (arg1 >= 0) {
            if (((Unk*)((char*)&D_80170880 + arg1 * 0x668))->unk450 == 0) {
                var_a2 = ((s32) (*(arg1 + (D_80091E5C * 4) + &D_80092A94) * 3) / 2) + 0x40;
                goto block_5;
            }
        } else {
block_5:
            var_a0 = D_8018157C + 1;
            if (var_a0 >= 8) {
                var_a0 = 0;
            }
            if (var_a0 != D_80181578) {
                temp_v1 = D_8018157C * 4;
                *(temp_v1 + &D_80181538) = arg0;
                *(temp_v1 + &D_80181558) = var_a2;
                D_8018157C = var_a0;
            }
        }
    }
}
