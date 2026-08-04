#include "ultra64.h"

/* -------------------------------------------------------------------------
 * func_800707B0 — game event-queue dispatcher (0x35C bytes, nonmatching).
 *
 * Processes pending command entries from D_801887D0's event ring.  Each
 * entry has a stride of 0x2C bytes; entry->unk0 (cmd 1-7) selects one of
 * seven action functions to call with &D_801820D8 as the first arg.
 *
 * Outer loop: calls func_8007CF98(5, D_80188770, D_8017C890) each frame.
 * Inner poll: calls func_8007CD08(&D_801887B8, NULL, 1) until
 *   D_801887D0.unk160 >= 0.
 * After dispatch, loops back if frame index < s4_limit.
 *
 * Non-standard entry: caller's $v0 is used as an init flag:
 *   $v0 == 0 → s4_limit = D_80188930   (run for that many frames)
 *   $v0 != 0 → s4_limit = -1           (no limit / always loop)
 * Cannot be expressed in C; function is permanently nonmatching.
 *
 * Jump table: jtbl_8004C710 (7 entries, cmd-1 = 0-6).
 * -------------------------------------------------------------------------
 */

void func_80071A28(s32 *arg0);
void func_80071D04(s32 *arg0);
void func_80071EA4(s32 arg0, s32 arg1);
void func_800721A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80072550(s32 arg0, s32 arg1, s32 arg2);
void func_800727EC(s32 arg0, s32 arg1, s32 (*arg2)(s32, s32));
void func_80072AD4(s32 arg0, s32 arg1, s32 arg2, s32 (*arg3)(s32));
void func_8007CF98(s32 arg0, s32 arg1, s32 arg2);
s32  func_8007CD08(Unk *arg0, s32 *arg1, s32 arg2);
s32  func_8006216C(void *entity);

extern Unk D_801887D0;  /* game state; cmd entries at +0, stride 0x2C */
extern Unk D_801887B8;  /* CD08 queue object */
extern s32 D_801820D8;  /* scene/world context */
extern s32 D_80188770;  /* event table base */
extern s32 D_80188930;  /* frame limit (used when init flag $v0==0) */
extern s32 D_80093EF8;  /* global counter, cleared on entry */
extern s32 D_80091E80;  /* set to 1 each frame */
extern s32 D_8017C890;  /* scene config */
extern s32 D_80091E84;  /* secondary queue flag */
extern s32 D_801887A0;  /* secondary queue object */

void func_800707B0(void *arg0) {
    /* nonmatching: uses caller's $v0 as non-standard init flag;
     * cannot byte-match without SN64. */
    s32 s4_limit;
    Unk *entry;
    s32 cmd;
    s32 idx;

    /* init flag from $v0 (not expressible in C) — stub assumes $v0 != 0 */
    s4_limit = -1;

    D_80093EF8 = 0;
    D_80091E80 = 1;

    do {
        /* frame tick */
        func_8007CF98(5, D_80188770, D_8017C890);
        D_80091E80 = 1;
        idx = D_801887D0.unk160;

        /* inner poll: wait for valid state (idx >= 0) */
        while (idx < 0) {
            func_8007CD08(&D_801887B8, NULL, 1);
            idx = D_801887D0.unk160;
        }

        /* process entity if still active */
        if (func_8006216C(arg0) != 0) {
            entry = (Unk *)((char *)&D_801887D0 + idx * 0x2C);
            cmd = *(s32 *)entry;   /* entry->unk0 = cmd type */

            if ((u32)(cmd - 1) < 7U) {  /* cmd 1-7 */
                switch (cmd) {
                case 1:
                    func_80071A28(&D_801820D8);
                    break;
                case 2:
                    func_80071D04(&D_801820D8);
                    break;
                case 3:
                    func_80071EA4((s32)&D_801820D8,
                                  *(s32 *)((char *)entry + 0x04));
                    break;
                case 4:
                    func_800721A8((s32)&D_801820D8,
                                  *(s32 *)((char *)entry + 0x04),
                                  *(s32 *)((char *)entry + 0x08),
                                  *(s32 *)((char *)entry + 0x0C));
                    break;
                case 5:
                    func_80072550((s32)&D_801820D8,
                                  *(s32 *)((char *)entry + 0x04),
                                  *(s32 *)((char *)entry + 0x08));
                    break;
                case 6:
                    func_800727EC((s32)&D_801820D8,
                                  *(s32 *)((char *)entry + 0x04),
                                  (s32 (*)(s32,s32))*(s32 *)((char *)entry + 0x1C));
                    break;
                case 7:
                    func_80072AD4((s32)&D_801820D8,
                                  *(s32 *)((char *)entry + 0x04),
                                  *(s32 *)((char *)entry + 0x08),
                                  (s32 (*)(s32))*(s32 *)((char *)entry + 0x1C));
                    break;
                }
            }
        }

        /* secondary queue drain (when D_80091E84 != 0) */
        if (D_80091E84 != 0) {
            do {
                func_8007CD08((Unk *)&D_801887A0, NULL, 1);
            } while (D_80091E84 != 0);
        }

        /* exit when idx >= s4_limit */
    } while (idx < s4_limit);
}
