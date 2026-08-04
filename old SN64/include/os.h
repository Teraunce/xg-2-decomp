/**
 * os.h — N64 OS thread / message queue types for xg2-decomp
 *
 * OSThread layout reverse-engineered from func_8007C0F4 (exception handler +
 * context save/restore), func_8007C584 (priority insert), func_8007C5DC
 * (context switch / dispatch), and func_8007BD08 (thread management).
 *
 * All offsets verified against MIPS sd/ld/sw/lw field access patterns.
 */

#ifndef _OS_H_
#define _OS_H_

#include "ultra64.h"   /* u8, u16, u32, u64, s16, s32, f32, f64, OSPri, OSId */

/* ---- OSThread context save block ----------------------------------------
 * Saved by the exception handler at func_8007C484 / restored at func_8007C5DC.
 * Offsets are relative to the OSThread base pointer.
 * Total context region: 0x20 – 0x1B0
 * -------------------------------------------------------------------------- */
typedef struct {
    /* GP integer register saves (64-bit each; $zero is not saved) */
    /* +0x00 */ u64 at;          /* $at  (assembler temporary) */
    /* +0x08 */ u64 v0;          /* $v0  return value */
    /* +0x10 */ u64 v1;          /* $v1  return value */
    /* +0x18 */ u64 a0;          /* $a0  argument */
    /* +0x20 */ u64 a1;          /* $a1  argument */
    /* +0x28 */ u64 a2;          /* $a2  argument */
    /* +0x30 */ u64 a3;          /* $a3  argument */
    /* +0x38 */ u64 t0;          /* $t0  caller-saved */
    /* +0x40 */ u64 t1;          /* $t1 */
    /* +0x48 */ u64 t2;          /* $t2 */
    /* +0x50 */ u64 t3;          /* $t3 */
    /* +0x58 */ u64 t4;          /* $t4 */
    /* +0x60 */ u64 t5;          /* $t5 */
    /* +0x68 */ u64 t6;          /* $t6 */
    /* +0x70 */ u64 t7;          /* $t7 */
    /* +0x78 */ u64 s0;          /* $s0  callee-saved */
    /* +0x80 */ u64 s1;          /* $s1 */
    /* +0x88 */ u64 s2;          /* $s2 */
    /* +0x90 */ u64 s3;          /* $s3 */
    /* +0x98 */ u64 s4;          /* $s4 */
    /* +0xA0 */ u64 s5;          /* $s5 */
    /* +0xA8 */ u64 s6;          /* $s6 */
    /* +0xB0 */ u64 s7;          /* $s7 */
    /* +0xB8 */ u64 t8;          /* $t8  caller-saved */
    /* +0xC0 */ u64 t9;          /* $t9  (also call target in jalr) */
    /* +0xC8 */ u64 gp;          /* $gp  global pointer */
    /* +0xD0 */ u64 sp;          /* $sp  stack pointer */
    /* +0xD8 */ u64 s8;          /* $s8 / $fp frame pointer */
    /* +0xE0 */ u64 ra;          /* $ra  return address */

    /* Multiply / divide result registers */
    /* +0xE8 */ u64 lo;          /* LO register */
    /* +0xF0 */ u64 hi;          /* HI register */

    /* CP0 coprocessor registers */
    /* +0xF8 */ u32 sr;          /* CP0 Status Register (c0_sr) */
    /* +0xFC */ u32 epc;         /* CP0 Exception Program Counter (return PC) */
    /* +0x100 */ u32 cause;      /* CP0 Cause register (unk_120 in older analysis) */
    /* +0x104 */ u32 count;      /* CP0 Count register */
    /* +0x108 */ u32 mi_intr_mask; /* saved MI_INTR_MASK_REG value */

    /* FPU state */
    /* +0x10C */ u32 fpu_csr;    /* FCR31 — FPU control/status register */

    /* FPU caller-saved registers (paired double-precision) */
    /* +0x110 */ f64 fv0;        /* $f0  / $f1 */
    /* +0x118 */ f64 fv1;        /* $f2  / $f3 */
    /* +0x120 */ f64 ft0;        /* $f4  / $f5 */
    /* +0x128 */ f64 ft1;        /* $f6  / $f7 */
    /* +0x130 */ f64 ft2;        /* $f8  / $f9 */
    /* +0x138 */ f64 ft3;        /* $f10 / $f11 */
    /* +0x140 */ f64 fa0;        /* $f12 / $f13 */
    /* +0x148 */ f64 fa1;        /* $f14 / $f15 */
    /* +0x150 */ f64 ft4;        /* $f16 / $f17 */
    /* +0x158 */ f64 ft5;        /* $f18 / $f19 */

    /* FPU callee-saved registers */
    /* +0x160 */ f64 fs0;        /* $f20 / $f21 */
    /* +0x168 */ f64 fs1;        /* $f22 / $f23 */
    /* +0x170 */ f64 fs2;        /* $f24 / $f25 */
    /* +0x178 */ f64 fs3;        /* $f26 / $f27 */
    /* +0x180 */ f64 fs4;        /* $f28 / $f29 */
    /* +0x188 */ f64 fs5;        /* $f30 / $f31 */
    /* +0x190 — end of context block */
} __OSThreadContext;  /* size: 0x190 bytes */

/* ---- OSThread -----------------------------------------------------------
 * Full thread control block.  The context block begins at offset +0x20,
 * so __OSThreadContext starts at (OSThread *)t + 0x20.
 *
 * Header fields confirmed from scheduler functions:
 *   next     — priority-insert walk in func_8007C584
 *   priority — OSPri compare in func_8007C584
 *   status   — 4 = running (func_8007C5DC), 1 = queued
 *   id       — loaded in func_8007BD08 as unk14 (offset 0x14)
 *   fp       — zero test at +0x18 gates FPU save/restore
 * -------------------------------------------------------------------- */
typedef struct OSThread_s {
    /* +0x00 */ struct OSThread_s *next;  /* run-queue link (NULL = tail) */
    /* +0x04 */ OSPri              priority;
    /* +0x08 */ void              *unk_08;  /* unknown pointer (queue?) */
    /* +0x0C */ void              *unk_0C;  /* unknown pointer */
    /* +0x10 */ s16                status;  /* 0=free, 1=queued, 4=running */
    /* +0x12 */ s16                flags;   /* misc flags */
    /* +0x14 */ OSId               id;
    /* +0x18 */ s32                fp;      /* 0 = no FPU; non-zero = FPU active */
    /* +0x1C */ u32                unk_1C;

    /* +0x20 */ __OSThreadContext  context; /* register save block — 0x190 bytes */
    /* = 0x1B0 total */
} OSThread;  /* size: 0x1B0 bytes */

/* OSThread status values */
#define OS_STATE_STOPPED   0
#define OS_STATE_RUNNABLE  1
#define OS_STATE_RUNNING   4
#define OS_STATE_WAITING   8

/* ---- OSMesgQueue --------------------------------------------------------
 * Confirmed fields from osCreateMesgQueue usage.
 * ----------------------------------------------------------------------- */
typedef struct OSMesgQueue_s {
    /* +0x00 */ u32     flag;
    /* +0x04 */ u32     count;       /* message-slot count (capacity) */
    /* +0x08 */ OSMesg *msg;         /* pointer to message array */
    /* +0x0C */ s32     validCount;  /* messages currently queued */
    /* +0x10 */ s32     first;       /* read-head index */
} OSMesgQueue;

/* ---- Viewport struct (RSP segment 2, D_800933A0 = gViewports) ----------
 * Standard N64 Vp — two s16[4] vectors (scale then translate).
 * Loaded into RSP via G_MOVEWORD (opcode 0xDC), not G_MTX.
 * ----------------------------------------------------------------------- */
typedef struct {
    s16 vscale[4];   /* viewport scale  (x, y, z, 0) in 2-frac fixed-point */
    s16 vtrans[4];   /* viewport offset (x, y, z, 0) in 2-frac fixed-point */
} Vp;

#endif /* _OS_H_ */
