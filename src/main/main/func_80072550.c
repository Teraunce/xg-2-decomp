#include "ultra64.h"
s32 handlerPostCmd(s32, s32, s32, s32, s32, s32, s32);     /* extern */
s32 handlerPostSfxCmd(s32, s32);                          /* extern */
void entityClearSlots(s32, s32);                       /* extern */
s32 entityStepState(s32, s32, s32);                     /* extern */
s32 contPakFetchNote(void *, s32, void *);              /* extern */
s32 contPakReadNote(void *, u16, s32, s32, s32, s32*); /* extern */
s32 contPakCountNotes(void *, s32*);                   /* extern */
s32 contPakReadDir(void *, s32*, s32*);              /* extern */
extern u16 gContPakNoteCode;
extern s32 gGameID;
extern s32 gContPakNoteAttr;
extern s32 gContPakSaveData;
extern Unk gHandlerCtx;
extern s32 gContPakResult;

void contPakLoadNote(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    s32 sp40;
    s32 sp20;
    Unk *var_v0;
    Unk *var_v1;
    s32 var_a0;
    s32 temp_v0;
    s32 var_s1;
    Unk *temp_s0;
    char *temp_s0_2;
    char *temp_s0_3;

    gContPakResult = 0;
loop_1:
    var_v0 = &gHandlerCtx;
loop_2:
    var_v0->unk168 = 1;
    temp_s0 = (arg1 * 4) + var_v0;
    if ((temp_s0->unk31C != 2) || (temp_s0->unk34C != 0)) {
        entityClearSlots(arg1, 2);
        if (temp_s0->unk31C != 2) {
            var_v0->unk168 = 0;
        }
    }
    sp40 = 0;
    if ((gHandlerCtx.unk168 != 0) && ((temp_s0_2 = (arg1 * 0x68) + (&gHandlerCtx + 0x17C), var_v0 = &gHandlerCtx, (entityStepState(contPakCountNotes(temp_s0_2, &sp40), arg1, -1) != 0)) || ((gHandlerCtx.unk168 != 0) && (var_v0 = &gHandlerCtx, (entityStepState(contPakReadDir(temp_s0_2, &sp44, &sp48), arg1, -1) != 0))))) {
        goto loop_2;
    }
    var_s1 = 0;
    if (gHandlerCtx.unk168 != 0) {
        temp_s0_3 = (arg1 * 0x68) + (&gHandlerCtx + 0x17C);
        if ((contPakReadNote(temp_s0_3, gContPakNoteCode, gGameID, &gContPakSaveData, &gContPakNoteAttr, &sp4C) == 0) && (contPakFetchNote(temp_s0_3, sp4C, &sp20) == 0)) {
            var_s1 = sp20;
            sp48 -= 1;
        }
        if (gHandlerCtx.unk168 != 0) {
            if (((sp40 + var_s1) < arg2) || (var_v1 = &gHandlerCtx, ((sp48 < 0x10) == 0))) {
                var_a0 = 0x4E;
                if (sp48 >= 0x10) {
                    var_a0 = 0x4C;
                }
                temp_v0 = handlerPostCmd(var_a0, arg1, 0x37, 0x49, 0x36, 0, 0);
                if (temp_v0 != 1) {
                    if (temp_v0 < 2) {
                        if (temp_v0 != 0) {
                            var_v1 = &gHandlerCtx;
                        } else {
                            goto loop_1;
                        }
                    } else if (temp_v0 != 2) {
                        var_v1 = &gHandlerCtx;
                    } else {
                        ((arg1 * 4) + &gHandlerCtx)->unk31C = 4;
                        gHandlerCtx.unk168 = 0;
                        goto block_28;
                    }
                } else {
                    handlerPostSfxCmd(arg1, arg2);
                    var_v0 = (void *)0x80190000;
                    goto loop_2;
                }
            }
        } else {
            goto block_29;
        }
    } else {
block_28:
block_29:
        var_v1 = &gHandlerCtx;
    }
    var_v1->unk160 = (s32) (var_v1->unk160 - 1);
}
