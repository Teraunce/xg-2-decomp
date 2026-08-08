#include "ultra64.h"
void rdpFrameBegin(s32, s32);                              /* extern */
s32 func_8006030C();                                  /* extern */
s32 func_80060310();                                  /* extern */
s32 func_80060824(s32, void *);                            /* extern */
void contPakUpdate(s32);                               /* extern */
s32 osSendMesg(Unk*, s32, s32);                         /* extern */
extern s32 gContPakUpdateFlag;
extern s32 gEventQueueSize;
extern s32 gPiHandlerMsg;

/*
 * frameDispatchThread — polling-loop dispatcher (nonmatching).
 *
 * PERMANENTLY NONMATCHING — two reasons:
 *
 * 1. Five alabel markers: func_8006030C and func_80060310 (declared above as
 *    extern prototypes) are mid-body entry points — other functions branch INTO
 *    this function's code. m2c cannot represent branching into a function body
 *    from outside, so the entire file is rejected.
 *
 * 2. Dispatches via jr through jtbl_8004BF80.  Function calls osRecvMesg in
 *    a loop, then checks if (result - 0xB) < 0x11 to select a dispatch table
 *    entry.  m2c marks any function containing jr-from-table as nonmatching.
 *
 * The loop also references D_8004BFC8 (a parallel data table).
 * Function size: 0xD8 bytes.
 */
void frameDispatchThread(void) { /* nonmatching — see asm stub */ }

/* nonmatching func_80060378: Unable to determine jump table for jr instruction at func_80 */
void func_80060378(void) { /* nonmatching — see asm stub */ }

void func_800607E0(void) {
    s32 saved_reg_s0;
    s32 saved_reg_s1;
    s32 saved_reg_s2;
    rdpFrameBegin(saved_reg_s1, saved_reg_s0);
    func_80060824(saved_reg_s2, &gEventQueueSize);
}

void func_80060800(void) {
    func_8006030C();
}

void func_80060808(void) {
    s32 saved_reg_s2;
    contPakUpdate(gContPakUpdateFlag != 0);
    osSendMesg(saved_reg_s2, &gPiHandlerMsg, 0);
    func_80060310();
}
