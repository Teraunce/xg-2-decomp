#include "ultra64.h"

/* -------------------------------------------------------------------------
 * sramHwDispatch — hardware controller command-dispatch loop (0x250 bytes,
 * nonmatching).
 *
 * Polls the status register at 0xB1FFFFF0 in an outer loop, then dispatches
 * on the status code (0x10-0x19) via a 10-entry jump table (jtbl_8004C7D0,
 * index = status - 0x10).  After dispatch, deasserts the control register at
 * 0xB1FFFFFC and waits for status to leave 1 before looping back.
 *
 * The loop exits only when case 1 (status 0x11) is seen AND gSramReady != 0
 * on re-entry to the top-of-loop check.
 *
 * Outer poll: wait until read(0xB1FFFFF0) != 0.
 *   status == 2 → deassert, sleep 0x3E8, retry outer loop.
 *   else → write 0x101 to control, wait for status to change, then dispatch.
 *
 * Jump table: jtbl_8004C7D0 (10 entries, index = status - 0x10):
 *   [0] default path (deassert)
 *   [1] s1 = 0 (sets exit condition), then default path
 *   [2] clear gSramInit/gSramReady, mask gSramHwFlags bit0, update PLL
 *   [3] clear gSramReady and gSramInit
 *   [4] set gSramReady = 0xFF
 *   [5] clear gSramReady
 *   [6] write packed colour bytes to 0xB1FE0000
 *   [7] sramBlockRead(2)
 *   [8] sramBlockRead(1)
 *   [9] sramCopyData(), then default path
 * -------------------------------------------------------------------------
 */

u32  __osPiRawReadIo(u32 addr);
void __osPiRawWriteIo(u32 addr, u32 val);
void __osPiResetCount(s32 delay);
s32  getCOP0Status(void);
void setCOP0Status(s32 arg0);
void sramBlockRead(s32 arg0);
void sramCopyData(void);

extern s32 gSramHwFlags;
extern u8  gSramInit;
extern u8  gSramReady;

void sramHwDispatch(void) {
    /* nonmatching: bnel/beql branch-likely idioms + jump table — see asm stub */
    s32 s1 = 1;
    s32 s0;
    s32 v1;

top:
    /* Poll status register until nonzero */
    while ((s0 = (s32)__osPiRawReadIo(0xB1FFFFF0)) == 0) {
        __osPiResetCount(0x3E8);
    }

    if (s0 == 2) {
        /* Status == 2: deassert, sleep, retry */
        __osPiRawWriteIo(0xB1FFFFFC, 0);
        __osPiResetCount(0x3E8);
        goto done_wait;
    }

    /* Assert command, then wait for status to change from s0 */
    __osPiRawWriteIo(0xB1FFFFFC, 0x101);
    while ((s32)__osPiRawReadIo(0xB1FFFFF0) == s0) {
        __osPiResetCount(0x1F4);
    }

    /* Re-read status and compute jump-table index */
    {
        s32 new_v = (s32)__osPiRawReadIo(0xB1FFFFF0);
        v1 = s0 - 0x10;

        if (new_v == 2) {
            __osPiRawWriteIo(0xB1FFFFFC, 0);
            goto done_wait;
        }

        if ((u32)v1 < 10U) {
            switch (v1) {
            default:
            case 0:
                break;
            case 1:
                s1 = 0;
                break;
            case 2: {
                s32 tmp = gSramHwFlags & -2;
                gSramInit = 0;
                gSramReady = 0;
                gSramHwFlags = tmp;
                setCOP0Status(getCOP0Status() & -2);
                break;
            }
            case 3:
                gSramReady = 0;
                gSramInit = 0;
                break;
            case 4:
                gSramReady = 0xFF;
                break;
            case 5:
                gSramReady = 0;
                break;
            case 6:
                __osPiRawWriteIo(0xB1FE0000,
                    ((u32)gSramReady << 24) | ((u32)gSramInit << 16));
                break;
            case 7:
                sramBlockRead(2);
                break;
            case 8:
                sramBlockRead(1);
                break;
            case 9:
                sramCopyData();
                break;
            }
        }
    }

    /* Deassert control, then wait until status leaves 1 */
    __osPiRawWriteIo(0xB1FFFFFC, 0);
    while ((s32)__osPiRawReadIo(0xB1FFFFF0) == 1) {
        __osPiResetCount(0x1F4);
    }

done_wait:
    /* bnel: if s1 != 0, reset s1=1 and loop (branch-likely executes delay slot) */
    if (s1 != 0) {
        s1 = 1;
        goto top;
    }
    /* beql: if gSramReady == 0, set s1=1 and loop */
    if (gSramReady == 0) {
        s1 = 1;
        goto top;
    }
    /* gSramReady != 0 and s1 == 0: clear status reg and return */
    __osPiRawWriteIo(0xB1FFFFF0, 0);
}

s32 strlen(u8 *arg0) {
    u8 *var_v1;

    var_v1 = arg0 + 1;
    if (*arg0 != 0) {
        do {
            var_v1 += 1;
        } while (*var_v1 != 0);
    }
    return var_v1 - arg0;
}
