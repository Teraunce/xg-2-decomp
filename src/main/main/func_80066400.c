#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of sceneDispatch (initial). */

s32 fontGetCharWidth(u16, s32 *, s32 *);               /* extern */
void rdpTextLayout(s32, u8**, s32);                     /* extern */
s32 sfxGetVolLevel(s32, s32);                          /* extern */
extern u16 D_80182E68;
extern u16 D_80182E74;
extern s16 D_80182E76;
extern s32 D_80182E84;
extern Unk D_80182E8C;
extern u16 D_80182E94;

void func_80066400(s32 arg0, s32 arg1, u16 *arg2) {
    s32 sp14;
    s32 sp10;
    s32 temp_v0_3;
    s32 var_v1;
    u16 *var_s1;
    u16 temp_v0;
    u16 temp_v0_2;
    Unk *temp_v0_4;

    var_s1 = arg2;
    temp_v0 = *var_s1;
    if (temp_v0 != 0) {
        var_v1 = temp_v0 & 0xFFFF;
        do {
            if ((var_v1 == 0xA) || (var_v1 == 0xD)) {
                sfxGetVolLevel(arg0, arg1);
                rdpTextLayout(arg0, arg1, *var_s1 != 0xA);
                D_80182E74 = D_80182E94;
                if ((D_80182E76 + D_80182E8C.unk0) >= 0x100) {
                    D_80182E76 = 0xFF;
                } else {
                    D_80182E76 = (u16) D_80182E76 + D_80182E8C.unk2;
                }
            } else {
                temp_v0_3 = fontGetCharWidth(*var_s1, &sp10, &sp14);
                if (temp_v0_3 == 0) {
                    sfxGetVolLevel(arg0, arg1);
                }
                temp_v0_4 = (D_80182E68 * 0x10) + arg1;
                temp_v0_4->unk0 = temp_v0_3;
                temp_v0_4->unk4 = sp14;
                temp_v0_4->unk8 = sp10;
                temp_v0_4->unkC = (s32) D_80182E84;
                D_80182E68 += 1;
            }
            var_s1 += 2;
            temp_v0_2 = *var_s1;
            var_v1 = temp_v0_2 & 0xFFFF;
        } while (temp_v0_2 != 0);
    }
    sfxGetVolLevel(arg0, arg1);
}

void sceneObjectDispatch(void);  /* forward: GETTER_NOJR fallthrough */
void sceneDispatch(s32 arg1, s32 arg2, s32 arg3) {
    sceneObjectDispatch();
}
