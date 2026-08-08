#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of handlerGetResult (initial). */

void sfxHeapInsert(void *, s32, s32);                         /* extern */
void sfxMarkEntityActive(void*);                               /* extern */
void sfxFindEntity(void *);                               /* extern */
s32 sfxHasEntity(void *);                             /* extern */
s32 sfxGetTopEntity();                                /* extern */
s32 sfxGetAllocEntity();                                /* extern */
s32 osSendMesg(Unk*, s32, s32);                       /* extern */
extern s32 D_80093EDC;
extern s32 D_80093EE0;
extern s32 gHandlerTable;
extern s32 D_80093EF8;
extern s32 D_800E412C;
extern s32 D_800E4220;
extern s32 D_8017C948;
extern s32 D_801887B8;
extern Unk D_801887D0;

void sfxEntityHandler(s32 arg0) {
    char *var_a0;
    char *var_s0;
    s32 temp_v0;
    s32 temp_v1;

    if ((D_801887D0.unk160 < 0) || (D_801887D0.unk16C != 0)) {
        sfxMarkEntityActive(sfxGetTopEntity());
        if (D_801887D0.unk178 != 0) {
            sfxFindEntity((void*)(s32)D_801887D0.unk178);
        }
        if (D_801887D0.unk174 != 0) {
            ((void(*)(s32, s32))(s32)D_801887D0.unk174)(arg0, D_801887D0.unk168);
        }
        D_801887D0.unk16C = 1;
        return;
    }
    if ((u32) (*(s32*)((char*)&D_801887D0 + (D_801887D0.unk160 * 0x2C)) - 1) < 7U) {
        if ((D_80093EDC != 0) && (D_80093EE0 != 0)) {
            osSendMesg(&D_801887B8, &D_8017C948, 0);
        }
    } else {
        temp_v0 = sfxGetAllocEntity();
        if ((temp_v0 == (s32)&gHandlerTable) || (temp_v0 == (s32)&D_800E412C) || (temp_v0 == (s32)&D_800E4220)) {
            temp_v1 = *(s32*)((char*)&D_801887D0 + (D_801887D0.unk160 * 0x2C));
            switch (temp_v1) {                      /* irregular */
            case 10:
                var_s0 = &D_800E412C;
                var_a0 = &D_800E412C;
                if (sfxHasEntity(&D_800E412C) != 0) {
block_21:
                    sfxFindEntity(var_s0);
                } else {
block_20:
                    sfxHeapInsert(var_a0, -3, 1);
                    return;
                }
                break;
            case 11:
                var_s0 = &D_800E4220;
                var_a0 = &D_800E4220;
                if (sfxHasEntity(&D_800E4220) == 0) {
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
    return D_80093EF8;
}
