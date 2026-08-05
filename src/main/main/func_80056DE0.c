#include "ultra64.h"
extern f32 D_8004BD9C;

/*
 * func_80056DE0 — pack RDP command words from truncated float values (nonmatching).
 *
 * Heavily non-standard SN64 calling convention: six values from implicit registers:
 *   $fv1/$f2  — truncated integer (temp_fa0)
 *   $ft2/$f4  — truncated integer (temp_fa0_3)
 *   $ft3/$f6  — scale factor for arg0->unk38+arg4 (used in multiply)
 *   $ft4/$f8  — truncated integer (temp_fa0_2)
 *   $ft5/$f10 — scale factor for arg0->unk38+arg4 (temp_fa0_4)
 *   $t0       — integer mask (likely 0xFFFF0000)
 * All replaced with 0 as placeholder values below.
 */
void func_80056DE0(Unk *arg0, Unk *arg1, f32 arg4) {
    s32 temp_fa0   = 0 /* $fv1/$f2 implicit */;
    s32 temp_fa0_2 = 0 /* $ft4/$f8 implicit */;
    s32 temp_fa0_3 = 0 /* $ft2/$f4 implicit */;
    s32 temp_fa0_4 = (s32) ((arg0->unk38 + arg4) * 0 /* $ft5/$f10 implicit */);
    s32 mask_t0    = 0 /* $t0 implicit, likely 0xFFFF0000 */;

    arg1->unk18 = (s32) ((temp_fa0_2 & mask_t0) | ((u32) temp_fa0_3 >> 0x10));
    arg1->unk38 = (s32) ((temp_fa0_2 << 0x10) | (temp_fa0_3 & 0xFFFF));
    arg1->unk1C = (s32) ((temp_fa0_4 & mask_t0) | ((u32) temp_fa0 >> 0x10));
    arg1->unk3C = (s32) ((temp_fa0_4 << 0x10) | (temp_fa0 & 0xFFFF));
}

void func_80056E5C(Unk *arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg0->unk0 = arg1;
    arg0->unk4 = 0;
    arg0->unk8 = 0;
    arg0->unkC = 0;
    arg0->unk10 = 0;
    arg0->unk14 = arg2;
    arg0->unk18 = 0;
    arg0->unk1C = 0;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = arg3;
    arg0->unk2C = 0;
    arg0->unk30 = 0;
    arg0->unk34 = 0;
    arg0->unk38 = 0;
    arg0->unk3C = (f32) D_8004BD9C;
}

/* -------------------------------------------------------------------------
 * func_80056EA8 — single-instruction branch fragment (0x4 bytes).
 *
 * The only instruction is: beq $a0, $a2, .L80056EB8
 * The delay slot falls into the following function.  This cannot be
 * expressed in standard C; kept as a nonmatching stub.
 * ------------------------------------------------------------------------- */
void func_80056EA8(s32 arg0, s32 arg1, s32 arg2) {
    if (arg0 == arg2) {
        return;
    }
}
