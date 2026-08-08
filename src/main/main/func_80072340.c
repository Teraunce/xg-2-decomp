#include "ultra64.h"

/* -------------------------------------------------------------------------
 * entityStepState — entity state-machine step (0x210 bytes, nonmatching).
 *
 * Advances the animation/state for entity 'entity_idx' (arg1) according
 * to command code 'cmd' (arg0, 0-8).  Calls handlerPostCmd for sound/event
 * triggers and contPakReadEntry for path/action queries; may retry the switch
 * with a new command code returned by contPakReadEntry.
 *
 * Writes to gHandlerCtx[entity_idx*4].unk31C (entity state slot) and
 * gHandlerCtx->unk168 (shared cleared flag).
 *
 * Returns 1 on "keep waiting", 0 on "done / transition".
 *
 * Jump table: jtbl_8004C760 (9 entries, arg0 0-8).
 *   [0]→return 0   [1][4][5][6]→default   [2]→set state 6 return 1
 *   [3]→complex    [7][8]→sound check
 * -------------------------------------------------------------------------
 */

s32  handlerPostCmd(s32, s32, s32, s32, s32, s32, s32);
s32  handlerPostSfxCmd(s32, s32);
s32  contPakReadEntry(void *);

extern Unk gHandlerCtx;   /* game state struct; stride 0x2C per cmd entry */

/* Helper: set entity state and clear shared flag, return 0. */
static s32 set_state3(s32 entity_idx) {
    ((s32 *)&gHandlerCtx)[entity_idx + 0x31C/4] = 3;
    gHandlerCtx.unk168 = 0;
    return 0;
}

s32 entityStepState(s32 cmd, s32 entity_idx, s32 arg2) {
    /* nonmatching: jump table + retry loop — see asm/main/main/entityStepState.s */

retry:
    if ((u32)cmd >= 9U) goto default_case;

    switch (cmd) {

    /* ---- case 0: immediate done ---- */
    case 0:
        return 0;

    /* ---- cases 1, 4, 5, 6 → default path ---- */
    case 1: case 4: case 5: case 6:
        goto default_case;

    /* ---- case 2: set entity state to 6, return 1 ---- */
    case 2:
        ((s32 *)&gHandlerCtx)[entity_idx + 0x31C/4] = 6;
        return 1;

    /* ---- case 3: query animation; on success retry with new cmd ---- */
    case 3: {
        s32 result;
        if (gHandlerCtx.unk170 == 0) {
            /* unk170 not yet set: ask for animation slot */
            result = handlerPostCmd(0x3F, entity_idx, 0x52, 0x50, 0x36, 0, 0);
            if (result == 0)  return 1;            /* still waiting */
            if (result != 1) return set_state3(entity_idx); /* error → state 3 */
            gHandlerCtx.unk170 = 1;
        } else {
            /* unk170 already set: check progress */
            result = handlerPostCmd(0x40, entity_idx, 0x53, 0x36, 0, 0, 0);
            if (result == 0) return set_state3(entity_idx);
        }
        /* both paths converge here: query path command */
        {
            void *base = (char *)&gHandlerCtx + 0x17C + entity_idx * 0x68;
            cmd = contPakReadEntry(base);
            if (cmd != 0) {
                goto retry;
            }
            return 1;
        }
    }

    /* ---- cases 7 & 8: play directional sound, then wait or commit ---- */
    case 7: case 8: {
        s32 sound_id = (cmd == 7) ? 0x4C : 0x4E;
        s32 result = handlerPostCmd(sound_id, entity_idx, 0x37, 0x49, 0x36, 0, 0);
        if (result == 0) return 1;                     /* still waiting */
        if (result == 1) {                             /* confirmed */
            handlerPostSfxCmd(entity_idx, arg2);
            return 1;
        }
        if (result == 2) {                             /* transition */
            /* set entity state to 4 */
            ((s32 *)&gHandlerCtx)[entity_idx + 0x31C/4] = 4;
            gHandlerCtx.unk168 = 0;
            return 0;
        }
        return 0;                                      /* any other result */
    }

    } /* switch */

default_case: {
        /* Fallback: trigger default sound/event, then set state 3 if busy */
        s32 result = handlerPostCmd(0x3C, entity_idx, 0x52, 0x31, 0, 0, 0);
        if (result == 0) return 1;
        return set_state3(entity_idx);
    }
}
