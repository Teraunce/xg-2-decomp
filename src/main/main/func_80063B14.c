#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of func_80063B94 (initial). */

u16 sfxAllocBlock(s32);                             /* extern */
void sfxPlay(u16);                               /* extern */
s32 sfxGetEntry(s32);                             /* extern */
s32 sfxDispatchSample(s32, s32);                        /* extern */
extern s32 gSfxDefTable;
extern s32 D_801823E0;

s32 func_80063B14(u32 arg0) {
    s32 temp_s0;
    s32 var_v0;

    if (arg0 < (u32)(s32)0 /* implicit $v0 from caller */) {
        temp_s0 = sfxAllocBlock(((Unk*)(s32)((arg0 * 0x10) + gSfxDefTable))->unk8) & 0xFFFF;
        var_v0 = 0;
        if (temp_s0 != 0) {
            var_v0 = temp_s0;
            if (sfxDispatchSample(arg0, sfxGetEntry(temp_s0)) == 0) {
                sfxPlay(temp_s0);
                goto block_4;
            }
        }
    } else {
block_4:
        var_v0 = 0;
    }
    return var_v0;
}

s32 func_80063B94(void) {
    return D_801823E0;
}
