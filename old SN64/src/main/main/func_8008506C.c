#include "ultra64.h"

/*
 * func_8008506C — object command dispatch (nonmatching).
 *
 * PERMANENTLY NONMATCHING — two reasons:
 * 1. Non-standard ABI: command code arrives in $t6, not $a0-$a3.
 *    No C declaration can pass an argument in $t6.
 * 2. jr dispatch through jtbl_8004CF38 (9 entries, index = $t6 & 0xF).
 *
 * $a0 (saved to $a3) is the target object; $a2 is a value argument.
 * All paths return 0.
 *
 * jtbl_8004CF38 active cases:
 *   case 0: obj->unk00 = a2
 *   case 3: obj->unk24=1; obj->unk30=0; obj->unk1C=0; obj->unk20=0.0f;
 *           if (obj->unk00) obj->unk00->vtbl[2](obj, 4, 0)
 *   case 6: obj->unk18 = (f32)a2  (reinterpret-cast via stack)
 *   case 7: obj->unk1C = 1
 *   case 8: obj->unk30 = 1;
 *           if (obj->unk00) obj->unk00->vtbl[2](obj, 9, 0)
 *   default: if (obj->unk00) obj->unk00->vtbl[2](obj, 0, 0)
 *
 * Function size: 0xE8 bytes.
 */
s32 func_8008506C(Unk *arg0, s32 arg1, s32 arg2, s32 arg3) {
    /* nonmatching: command code in $t6 (non-standard) — see asm stub */
    (void)arg1; (void)arg2; (void)arg3;
    return 0;
}
