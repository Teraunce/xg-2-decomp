#include "ultra64.h"
void __osInvalICache_full(void);                             /* extern */
extern s32 gPlayerList;
extern s32 gOverlayDL2;
extern s32 gOverlayState;
extern Unk *gDLPtr;
extern s32 gRenderIdx;

void gfxDLEnd(void) {
    Unk *temp_a0;
    Unk *temp_a1;
    Unk *temp_v0;

    if (gOverlayState == 2) {
        temp_a0 = gDLPtr;
        gDLPtr += 8;
        temp_a0->unk0 = 0xDE000000;
        temp_a0->unk4 = &gOverlayDL2;
    }
    temp_a1 = gDLPtr;
    temp_v0 = gDLPtr + 8;
    temp_a1->unk0 = 0xE9000000;
    gDLPtr = temp_v0;
    gDLPtr = temp_v0 + 8;
    temp_a1->unk4 = 0;
    gDLPtr->unk8 = 0xDF000000;
    temp_v0->unk4 = 0;
    __osInvalICache_full();
    gRenderIdx = 0;
    gPlayerList ^= 1;
}

/* D_80070264: rodata — defined in entry.s */

/*
 * func_80070354 — ASCII char-to-code converter (nonmatching).
 *
 * PERMANENTLY NONMATCHING — jr dispatch through jtbl_8004C608, AND the
 * jump-table entries point to IDO-generated out-of-line case stubs
 * (func_800703E4, func_800703EC, … each 8 bytes, returning one constant).
 * These stubs appear as separate linker symbols immediately after the
 * function.  A C switch statement cannot reproduce this layout: IDO would
 * inline the case bodies rather than emitting them as separately-addressed
 * stubs, producing different bytecode.
 *
 * Converts an ASCII character to an internal token code:
 *   '0'-'9' (0x30-0x39) → (char + 0xE0) & 0xFF
 *   'A'-'Z' (0x41-0x5A) → (char + 0xD9) & 0xFF
 *   'a'-'z' (0x61-0x7A) → (char + 0xB9) & 0xFF
 *   other < 0x41        → jtbl_8004C608[char] (special-char map, see below)
 *   default             → 0xF
 */
u32 func_80070354(u32 arg0) {
    /* nonmatching: jtbl_8004C608 switch — see asm stub */
    if ((u16)(arg0 - 0x30) < 0xAU)  return (u8)(arg0 + 0xE0); /* '0'-'9' */
    if ((u16)(arg0 - 0x41) < 0x1AU) return (u8)(arg0 + 0xD9); /* 'A'-'Z' */
    if ((u16)(arg0 - 0x61) < 0x1AU) return (u8)(arg0 + 0xB9); /* 'a'-'z' */
    if (arg0 < 0x41U) {
        /* jtbl_8004C608[arg0]: each entry tail-jumps to a 2-instruction stub */
        switch (arg0) {
        case 0x00: return 0;
        case 0x21: return 0x34;  /* '!' */
        case 0x22: return 0x35;  /* '"' */
        case 0x23: return 0x36;  /* '#' */
        case 0x27: return 0x37;  /* '\'' */
        case 0x2A: return 0x38;  /* '*' */
        case 0x2B: return 0x39;  /* '+' */
        case 0x2C: return 0x3A;  /* ',' */
        case 0x2D: return 0x3B;  /* '-' */
        case 0x2E: return 0x3C;  /* '.' */
        case 0x2F: return 0x3D;  /* '/' */
        case 0x3A: return 0x3E;  /* ':' */
        case 0x3D: return 0x3F;  /* '=' */
        case 0x3F: return 0x40;  /* '?' */
        case 0x40: return 0x41;  /* '@' */
        default:   return 0xF;
        }
    }
    return 0xF;
}

s32 func_800703E4(void) {
    return 0x34;
}

s32 func_800703EC(void) {
    return 0x35;
}

s32 func_800703F4(void) {
    return 0x36;
}

s32 func_800703FC(void) {
    return 0x37;
}

s32 func_80070404(void) {
    return 0x38;
}

s32 func_8007040C(void) {
    return 0x39;
}

s32 func_80070414(void) {
    return 0x3A;
}

s32 func_8007041C(void) {
    return 0x3B;
}

s32 func_80070424(void) {
    return 0x3C;
}

s32 func_8007042C(void) {
    return 0x3D;
}

s32 func_80070434(void) {
    return 0x3E;
}

s32 func_8007043C(void) {
    return 0x3F;
}

s32 func_80070444(void) {
    return 0x40;
}

s32 func_8007044C(void) {
    return 0x41;
}
