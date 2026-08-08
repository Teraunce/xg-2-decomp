#include "ultra64.h"
#include "os.h"

/*
 * osCreateThread — initialise a thread control block (osCreateThread equivalent).
 *
 * Arguments
 *   arg0  thread   — OSThread* to initialise
 *   arg1  id       — OSId (s32)
 *   arg2  entry    — thread entry-point PC (stored into context.epc)
 *   arg3  a0arg    — initial $a0 value (sign-extended to 64-bit in context.a0)
 *   arg4  stack    — initial stack pointer (sp = arg4 - 0x10, sign-extended to 64-bit)
 *   arg5  pri      — OSPri scheduler priority
 *
 * The thread is pushed onto the head of the __osAllThreadList creation-order list via
 * unk_0C before being handed to the scheduler.
 *
 * __osException and __osIntHandler (same splat-merged asm file) are the N64
 * exception/interrupt handler written entirely in handwritten privileged
 * assembly ($k0/$k1, mfc0/mtc0, sd/ld for all registers, eret).  They cannot
 * be expressed in portable C and are retained in
 * asm/main/main/func_8007BD08_merged.s.
 */

s32  osDisableInt(void);
void osRestoreInt(s32);

/*
 * gThreadExitStub — default thread return address.  When the thread entry function
 * returns, execution falls here (typically a cleanup / self-terminate stub).
 */
extern s32 gThreadExitStub;

/*
 * __osAllThreadList — creation-order all-threads list head (address 0x800952AC,
 * 4 bytes after __osRunQueue).  Threads are singly-linked through unk_0C.
 */
extern OSThread *__osAllThreadList;

void osCreateThread(OSThread *arg0, OSId arg1, u32 arg2, s32 arg3, u32 arg4, OSPri arg5) {
    s32 temp_s0;

    /* --- Thread header fields --- */
    arg0->id       = arg1;
    arg0->priority = arg5;
    arg0->next     = NULL;
    arg0->unk_08   = NULL;

    /* --- CP0 / FPU context fields --- */
    arg0->context.epc = arg2;                              /* initial PC */

    /* context.a0 — sign-extend arg3 to 64-bit via two 32-bit half-word stores */
    *(s32 *)&arg0->context.a0        = (s32)(arg3 >> 0x1F);  /* high word */
    *((s32 *)&arg0->context.a0 + 1)  = arg3;                  /* low  word */

    /* context.sp — sp = arg4 - 0x10, sign-extended to 64-bit */
    *((s32 *)&arg0->context.sp + 1)  = (s32)(arg4 - 0x10);                              /* low  word */
    *(s32 *)&arg0->context.sp        = (s32)(((s32)arg4 >> 0x1F) - (arg4 < 0x10U));     /* high word */

    /* context.ra — return address when entry function exits */
    *(s32 *)&arg0->context.ra        = (s32)((s32)&gThreadExitStub >> 0x1F);  /* high word */
    *((s32 *)&arg0->context.ra + 1)  = (s32)&gThreadExitStub;                  /* low  word */

    arg0->context.sr          = 0xFF03;         /* CP0 Status: IE + coprocessor enables */
    arg0->context.mi_intr_mask = (u32)((u32)(0x3FFF01 & 0x3F0000) >> 0x10); /* 0x3F */
    arg0->context.fpu_csr     = 0x01000800;     /* FCR31 initial value */

    arg0->fp     = 0;   /* FPU not active for this thread */
    arg0->status = OS_STATE_RUNNABLE;
    arg0->flags  = 0;

    /* --- Link into creation-order all-threads list via unk_0C --- */
    temp_s0    = osDisableInt();
    arg0->unk_0C = (void *)__osAllThreadList;
    __osAllThreadList  = arg0;
    osRestoreInt(temp_s0);
}
