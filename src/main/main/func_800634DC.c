#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of sfxTableInitGetter (initial). */

s32 sfxMapId(s32);                               /* extern */
void rdpRunSetupDL(void**);                               /* extern */
void gfxAddSyncCmd(void**);                               /* extern */
void sfxRenderBegin(void**, s32);                            /* extern */
void sceneDispatch(s32, s32, s32);                    /* extern */
extern s32 D_8004C050;
extern s32 D_8004C058;
extern s32 D_80173CC0;
extern s32 D_801823C4;
extern s32 D_801823C8;

void gameMenuRender(void) {
    char *var_a1;
    s32 var_a3;
    s32 temp_t2;

    rdpRunSetupDL(&D_80173CC0);
    if (D_801823C4 != 0) {
        sfxRenderBegin(&D_80173CC0, 0);
        sfxMapId(0x48);
        var_a1 = &D_8004C050;
        var_a3 = 0x10;
    } else {
        temp_t2 = sfxMapId(0x69);
        var_a1 = &D_8004C058;
        if ((D_801823C8 * 3) < 0) {

        }
        var_a3 = 5;
    }
    sceneDispatch(var_a1, 0, var_a3);
    gfxAddSyncCmd(&D_80173CC0);
}

void sfxTableInit(void);  /* forward: GETTER_NOJR fallthrough */
void sfxTableInitGetter(Unk *arg0) {
    (void) arg0->unkC00;  /* GETTER_NOJR: lb $zero,0xC00($a0) prefetch, falls into sfxTableInit */
    sfxTableInit();
}
