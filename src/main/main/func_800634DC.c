#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of sfxTableInitGetter (initial). */

s32 sfxMapId(s32);                               /* extern */
void rdpRunSetupDL(void**);                               /* extern */
void gfxAddSyncCmd(void**);                               /* extern */
void sfxRenderBegin(void**, s32);                            /* extern */
void sceneDispatch(s32, s32, s32);                    /* extern */
extern s32 gTexLineParam50;
extern s32 gTexLineParam58;
extern s32 gDLPtr;
extern s32 gSfxBlockedFlag;
extern s32 gSfxTimer;

void gameMenuRender(void) {
    char *var_a1;
    s32 var_a3;
    s32 temp_t2;

    rdpRunSetupDL(&gDLPtr);
    if (gSfxBlockedFlag != 0) {
        sfxRenderBegin(&gDLPtr, 0);
        sfxMapId(0x48);
        var_a1 = &gTexLineParam50;
        var_a3 = 0x10;
    } else {
        temp_t2 = sfxMapId(0x69);
        var_a1 = &gTexLineParam58;
        if ((gSfxTimer * 3) < 0) {

        }
        var_a3 = 5;
    }
    sceneDispatch(var_a1, 0, var_a3);
    gfxAddSyncCmd(&gDLPtr);
}

void sfxTableInit(void);  /* forward: GETTER_NOJR fallthrough */
void sfxTableInitGetter(Unk *arg0) {
    (void) arg0->unkC00;  /* GETTER_NOJR: lb $zero,0xC00($a0) prefetch, falls into sfxTableInit */
    sfxTableInit();
}
