#include "ultra64.h"

/* -------------------------------------------------------------------------
 * contPakEventLoop — game event-queue dispatcher (0x35C bytes, nonmatching).
 *
 * Processes pending command entries from D_801887D0's event ring.  Each
 * entry has a stride of 0x2C bytes; entry->unk0 (cmd 1-7) selects one of
 * seven action functions to call with &gSfxChannelState as the first arg.
 *
 * Outer loop: calls osSetEventMesg(5, D_80188770, D_8017C890) each frame.
 * Inner poll: calls osRecvMesg(&D_801887B8, NULL, 1) until
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

void contPakHandlerInit(s32 *arg0);
void contPakHandlerDetect(s32 *arg0);
void contPakScanNotes(s32 arg0, s32 arg1);
void contPakHandlerRead(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void contPakLoadNote(s32 arg0, s32 arg1, s32 arg2);
void contPakSaveNote(s32 arg0, s32 arg1, s32 (*arg2)(s32, s32));
void contPakCreateNote(s32 arg0, s32 arg1, s32 arg2, s32 (*arg3)(s32));
void osSetEventMesg(s32 arg0, s32 arg1, s32 arg2);
s32  osRecvMesg(Unk *arg0, s32 *arg1, s32 arg2);
s32  sfxHasEntity(void *entity);

extern Unk D_801887D0;  /* game state; cmd entries at +0, stride 0x2C */
extern Unk D_801887B8;  /* CD08 queue object */
extern s32 gSfxChannelState;  /* scene/world context */
extern s32 D_80188770;  /* event table base */
extern s32 D_80188930;  /* frame limit (used when init flag $v0==0) */
extern s32 D_80093EF8;  /* global counter, cleared on entry */
extern s32 gInitFlag;  /* set to 1 each frame */
extern s32 D_8017C890;  /* scene config */
extern s32 gSessionActive;  /* secondary queue flag */
extern s32 D_801887A0;  /* secondary queue object */

void contPakEventLoop(void *arg0) {
    /* nonmatching: uses caller's $v0 as non-standard init flag;
     * cannot byte-match without SN64. */
    s32 s4_limit;
    Unk *entry;
    s32 cmd;
    s32 idx;

    /* init flag from $v0 (not expressible in C) — stub assumes $v0 != 0 */
    s4_limit = -1;

    D_80093EF8 = 0;
    gInitFlag = 1;

    do {
        /* frame tick */
        osSetEventMesg(5, D_80188770, D_8017C890);
        gInitFlag = 1;
        idx = D_801887D0.unk160;

        /* inner poll: wait for valid state (idx >= 0) */
        while (idx < 0) {
            osRecvMesg(&D_801887B8, NULL, 1);
            idx = D_801887D0.unk160;
        }

        /* process entity if still active */
        if (sfxHasEntity(arg0) != 0) {
            entry = (Unk *)((char *)&D_801887D0 + idx * 0x2C);
            cmd = *(s32 *)entry;   /* entry->unk0 = cmd type */

            if ((u32)(cmd - 1) < 7U) {  /* cmd 1-7 */
                switch (cmd) {
                case 1:
                    contPakHandlerInit(&gSfxChannelState);
                    break;
                case 2:
                    contPakHandlerDetect(&gSfxChannelState);
                    break;
                case 3:
                    contPakScanNotes((s32)&gSfxChannelState,
                                  *(s32 *)((char *)entry + 0x04));
                    break;
                case 4:
                    contPakHandlerRead((s32)&gSfxChannelState,
                                  *(s32 *)((char *)entry + 0x04),
                                  *(s32 *)((char *)entry + 0x08),
                                  *(s32 *)((char *)entry + 0x0C));
                    break;
                case 5:
                    contPakLoadNote((s32)&gSfxChannelState,
                                  *(s32 *)((char *)entry + 0x04),
                                  *(s32 *)((char *)entry + 0x08));
                    break;
                case 6:
                    contPakSaveNote((s32)&gSfxChannelState,
                                  *(s32 *)((char *)entry + 0x04),
                                  (s32 (*)(s32,s32))*(s32 *)((char *)entry + 0x1C));
                    break;
                case 7:
                    contPakCreateNote((s32)&gSfxChannelState,
                                  *(s32 *)((char *)entry + 0x04),
                                  *(s32 *)((char *)entry + 0x08),
                                  (s32 (*)(s32))*(s32 *)((char *)entry + 0x1C));
                    break;
                }
            }
        }

        /* secondary queue drain (when gSessionActive != 0) */
        if (gSessionActive != 0) {
            do {
                osRecvMesg((Unk *)&D_801887A0, NULL, 1);
            } while (gSessionActive != 0);
        }

        /* exit when idx >= s4_limit */
    } while (idx < s4_limit);
}
