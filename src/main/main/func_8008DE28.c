#include "ultra64.h"

/* -------------------------------------------------------------------------
 * gfxDmaEventLoop — GPU command-queue event loop (0x490 bytes, nonmatching).
 *
 * Infinite event-processing loop driven by two command queues embedded in
 * the arg0 dispatch-context struct.  Never returns (no epilogue reached
 * under normal flow; exits only if the runtime unwinds the stack).
 *
 * Outer loop (.L8008DE48):
 *   1. Dequeues an event from arg0->unk8 into sp44.
 *   2. If sp44->unk14 is valid (type 2, done=0 or 1): processes geometry
 *      data (adjusts vertex buffer, writes D_A4600010, etc.) [stubbed below].
 *   3. Dispatches on sp44->unk0 (event type 10-16) via jtbl_8004CFB8.
 *   4. If dispatch result == 0: drains arg0->unkC queue, releases event,
 *      loops; otherwise loops directly.
 *
 * Jump table: jtbl_8004CFB8 (7 entries, type-10 = 0-6).
 *   type 10 → cancel event (osSendMesg), sp38 = -1
 *   type 11 → arg0->unk14(0, ev.unkC, ev.unk8, ev.unk10)
 *   type 12 → arg0->unk14(1, ev.unkC, ev.unk8, ev.unk10)
 *   type 13, 14, default → sp38 = -1
 *   type 15 → arg0->unk18(ev.unk14, 0, ev.unkC, ev.unk8, ev.unk10)
 *   type 16 → arg0->unk18(ev.unk14, 1, ev.unkC, ev.unk8, ev.unk10)
 * -------------------------------------------------------------------------
 */

s32  osRecvMesg(void *arg0, void *arg1, s32 arg2);
s32  osSendMesg(void *arg0, void *arg1, s32 arg2);
void func_8008E2B8(s32 arg0);
void func_8008E408(void *arg0, s32 arg1, s32 arg2);
void func_8008E3B8(void *arg0, s32 arg1, s32 arg2);
void func_8008E318(s32 arg0);
void func_8008E368(void);

extern s32 D_A4600010;  /* RSP/RDP register */

void gfxDmaEventLoop(Unk *arg0) {
    /* nonmatching: geometry update section and full loop body —
     * see asm/main/main/gfxDmaEventLoop.s */

    Unk *sp44 = NULL;   /* dequeued event */
    s32 sp38 = 0;       /* dispatch result */
    s32 sp30 = 0;       /* geometry-done flag */

    for (;;) {
        /* --- dequeue event from arg0->unk8 --- */
        osRecvMesg((void *)arg0->unk8, &sp44, 1);

        /* --- check for geometry-type event --- */
        if (sp44 != 0 && sp44->unk14 != 0) {
            Unk *geo = (Unk *)(s32)sp44->unk14;
            if (geo->unk4 == 2 && (geo->unk14 == 0 || geo->unk14 == 1)) {
                /* nonmatching: GPU geometry update (vertex stride calc,
                 * polygon type check, D_A4600010 write, func_8008E318 call).
                 * See asm stub .L8008DE90–.L8008E070 for full impl. */
                (void)sp30;
                goto dispatch;
            }
        }

    dispatch:
        /* --- dispatch on event type (10-16) --- */
        if (sp44 != 0) {
            u16 type = *(u16 *)sp44;
            u16 idx  = type - 10;
            if (idx >= 7U) {
                sp38 = -1;
            } else {
                switch (idx) {
                case 0: /* type 10: cancel */
                    osSendMesg((void *)sp44->unk4, sp44, 0);
                    sp38 = -1;
                    break;
                case 1: /* type 11: call unk14(0, ...) */
                    osRecvMesg((void *)arg0->unk10, &sp44, 1);
                    sp38 = ((s32 (*)(s32, s32, s32, s32))arg0->unk14)(
                               0, sp44->unkC, sp44->unk8, sp44->unk10);
                    break;
                case 2: /* type 12: call unk14(1, ...) */
                    osRecvMesg((void *)arg0->unk10, &sp44, 1);
                    sp38 = ((s32 (*)(s32, s32, s32, s32))arg0->unk14)(
                               1, sp44->unkC, sp44->unk8, sp44->unk10);
                    break;
                case 3: /* type 13 */
                case 4: /* type 14 */
                default:
                    sp38 = -1;
                    break;
                case 5: /* type 15: call unk18(ev.unk14, 0, ...) */
                    osRecvMesg((void *)arg0->unk10, &sp44, 1);
                    sp38 = ((s32 (*)(s32, s32, s32, s32, s32))arg0->unk18)(
                               sp44->unk14, 0, sp44->unkC, sp44->unk8, sp44->unk10);
                    break;
                case 6: /* type 16: call unk18(ev.unk14, 1, ...) */
                    osRecvMesg((void *)arg0->unk10, &sp44, 1);
                    sp38 = ((s32 (*)(s32, s32, s32, s32, s32))arg0->unk18)(
                               sp44->unk14, 1, sp44->unkC, sp44->unk8, sp44->unk10);
                    break;
                }
            }
        }

        /* --- on success (sp38 == 0): drain secondary queue and release --- */
        if (sp38 != 0) continue;

        osRecvMesg((void *)arg0->unkC, &sp44, 1);
        osSendMesg((void *)sp44->unk4, sp44, 0);
        osSendMesg((void *)arg0->unk10, NULL, 0);
        /* loop */
    }
}
