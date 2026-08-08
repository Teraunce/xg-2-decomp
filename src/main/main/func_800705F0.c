#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of handlerGetResult (initial). */

void sfxHeapInsert(void *, s32, s32);                         /* extern */
void sfxMarkEntityActive(void*);                               /* extern */
void sfxFindEntity(void *);                               /* extern */
s32 sfxHasEntity(void *);                             /* extern */
s32 sfxGetTopEntity();                                /* extern */
s32 sfxGetAllocEntity();                                /* extern */
s32 osSendMesg(Unk*, s32, s32);                       /* extern */
extern s32 gHandlerMainFlag;
extern s32 gHandlerAuxFlag;
extern s32 gHandlerTable;
extern s32 gHandlerResult;
extern s32 gSfxEffectTableA;
extern s32 gSfxEffectTableB;
extern s32 gEntityHandlerMsg;
extern s32 gEntityMesgQueue;
extern Unk gHandlerCtx;

void sfxEntityHandler(s32 arg0) {
    char *var_a0;
    char *var_s0;
    s32 temp_v0;
    s32 temp_v1;

    if ((gHandlerCtx.unk160 < 0) || (gHandlerCtx.unk16C != 0)) {
        sfxMarkEntityActive(sfxGetTopEntity());
        if (gHandlerCtx.unk178 != 0) {
            sfxFindEntity((void*)(s32)gHandlerCtx.unk178);
        }
        if (gHandlerCtx.unk174 != 0) {
            ((void(*)(s32, s32))(s32)gHandlerCtx.unk174)(arg0, gHandlerCtx.unk168);
        }
        gHandlerCtx.unk16C = 1;
        return;
    }
    if ((u32) (*(s32*)((char*)&gHandlerCtx + (gHandlerCtx.unk160 * 0x2C)) - 1) < 7U) {
        if ((gHandlerMainFlag != 0) && (gHandlerAuxFlag != 0)) {
            osSendMesg(&gEntityMesgQueue, &gEntityHandlerMsg, 0);
        }
    } else {
        temp_v0 = sfxGetAllocEntity();
        if ((temp_v0 == (s32)&gHandlerTable) || (temp_v0 == (s32)&gSfxEffectTableA) || (temp_v0 == (s32)&gSfxEffectTableB)) {
            temp_v1 = *(s32*)((char*)&gHandlerCtx + (gHandlerCtx.unk160 * 0x2C));
            switch (temp_v1) {                      /* irregular */
            case 10:
                var_s0 = &gSfxEffectTableA;
                var_a0 = &gSfxEffectTableA;
                if (sfxHasEntity(&gSfxEffectTableA) != 0) {
block_21:
                    sfxFindEntity(var_s0);
                } else {
block_20:
                    sfxHeapInsert(var_a0, -3, 1);
                    return;
                }
                break;
            case 11:
                var_s0 = &gSfxEffectTableB;
                var_a0 = &gSfxEffectTableB;
                if (sfxHasEntity(&gSfxEffectTableB) == 0) {
                    goto block_20;
                }
                goto block_21;
            }
        }
    }
}

void func_800707A0(void) {

}

s32 handlerGetResult(void) {
    return gHandlerResult;
}
