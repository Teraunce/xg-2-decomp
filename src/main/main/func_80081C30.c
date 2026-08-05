#include "ultra64.h"

/*
 * func_80081C30 — MIDI SMF header parser (initialises stream context).
 *
 * Jal delay-slot ABI fix: `or $a3, $a0, $zero` at entry saves arg0 into $a3.
 * Every subsequent jal uses `or $a0, $a3, $zero` in its delay slot to restore
 * arg0 into $a0. m2c saw $a3 as "unset" after each call.
 * Fixed: all 9 M2C_ERROR($a3) occurrences replaced with arg0.
 *
 * Reads and validates the SMF header chunk:
 *   - Expects chunk type  0x4D546864 ("MThd")
 *   - Reads 16-bit format word (must be 0) and 16-bit track count (must be 1)
 *   - Reads 16-bit division → arg0->unk18
 *   - If bit 15 clear: computes arg0->unk14 = 1.0 / (float)division
 *   - Expects chunk type  0x4D54726B ("MTrk") to follow
 *   - Reads track length → arg0->unk4 = arg0->unk8 (current stream position)
 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
} UnkStruct_arg0;

s32 streamReadU32(UnkStruct_arg0 *);
s16 func_80081C00(UnkStruct_arg0 *);

void func_80081C30(UnkStruct_arg0 *arg0, s32 arg1, s32 arg2) {
    s16 temp_v1;

    arg0->unk0 = arg1;
    arg0->unk10 = arg2;
    arg0->unk1A = 0;
    arg0->unkC = 0;
    arg0->unk8 = arg1;
    if (streamReadU32(arg0) == 0x4D546864) {
        streamReadU32(arg0);
        if ((func_80081C00(arg0) == 0) && (func_80081C00(arg0) == 1)) {
            arg0->unk18 = func_80081C00(arg0);
            temp_v1 = arg0->unk18;
            if (!(temp_v1 & 0x8000)) {
                arg0->unk14 = (f32) (1.0 / (f64) (f32) temp_v1);
                if (streamReadU32(arg0) == 0x4D54726B) {
                    streamReadU32(arg0);
                    arg0->unk4 = arg0->unk8;
                }
            }
        }
    }
}
