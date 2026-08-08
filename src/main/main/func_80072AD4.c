#include "ultra64.h"
void sfxEntryWrite(s32, s32, u32);                       /* extern */
u16 sfxAllocBlock(s32);                             /* extern */
void sfxPlay(u16);                               /* extern */
s32 sfxGetEntry(s32);                             /* extern */
s32 calcHash(u8*, s32);                        /* extern */
s32 alignUp256(s32);                               /* extern */
s32 handlerPostCmd(s32, s32, s32, s32, s32, s32, s32);       /* extern */
void entityClearSlots(s32, s32);                       /* extern */
s32 entityStepState(s32, s32, s32);                   /* extern */
s32 contPakAllocNote(Unk*, u16, s32, u8*, u8*, s32, s32*); /* extern */
s32 contPakLoadSave(Unk*, u16, s32, s32, s32);      /* extern */
s32 contPakWriteNote(Unk*, s32, u8, s32, s32, char*);     /* extern */
s32 contPakFetchNote(void *, s32, void *);              /* extern */
s32 contPakReadNote(void *, u16, s32, s32, s32, s32*); /* extern */
extern u16 gContPakNoteCode;
extern s32 gGameID;
extern s32 gContPakNoteAttr;
extern s32 gContPakSaveData;
extern Unk gHandlerCtx;
extern s32 gContPakHandlerPhase;
extern s32 gContPakResult;

void contPakCreateNote(s32 arg0, s32 arg1, s32 arg2, s32 (*arg3)(s32)) {
    u16 sp44;
    s32 sp40;
    s32 sp20;
    s32 temp_s0_2;
    s32 temp_v0_3;
    u16 temp_s0;
    u16 temp_v0_2;
    u32 temp_v0;
    Unk *temp_s0_3;
    char *temp_s0_4;
    Unk *temp_s1;

    temp_v0 = alignUp256(arg2);
    temp_v0_2 = sfxAllocBlock(temp_v0);
    sp44 = temp_v0_2;
    temp_s0 = temp_v0_2 & 0xFFFF;
    sfxEntryWrite(sfxGetEntry(temp_s0), 0xDEADBEEF, temp_v0 >> 2);
    temp_s0_2 = sfxGetEntry(temp_s0);
    temp_s1 = sfxGetEntry(temp_s0) + temp_v0;
    arg3(temp_s0_2);
    *(s32*)((char*)temp_s1 - 4)= calcHash(temp_s0_2, temp_v0 - 4);
    gContPakResult = 0;
loop_1:
    gHandlerCtx.unk168 = 1;
    temp_s0_3 = (arg1 * 4) + &gHandlerCtx;
    if ((temp_s0_3->unk31C != 2) || (temp_s0_3->unk34C != 0)) {
        entityClearSlots(arg1, 2);
        if (temp_s0_3->unk31C != 2) {
            gHandlerCtx.unk168 = 0;
        }
    }
    if (gHandlerCtx.unk168 != 0) {
        temp_s0_4 = (arg1 * 0x68) + (&gHandlerCtx + 0x17C);
        temp_v0_3 = contPakReadNote(temp_s0_4, gContPakNoteCode, gGameID, &gContPakSaveData, &gContPakNoteAttr, &sp40);
        switch (temp_v0_3) {                        /* irregular */
        case 0:
            if (entityStepState(contPakFetchNote(temp_s0_4, sp40, &sp20), arg1, temp_v0) == 0) {
                if (gHandlerCtx.unk168 != 0) {
                    if (sp20 != temp_v0) {
                        if (entityStepState(contPakLoadSave(temp_s0_4, gContPakNoteCode, gGameID, &gContPakSaveData, &gContPakNoteAttr), arg1, temp_v0) == 0) {
                            if (gHandlerCtx.unk168 != 0) {
                            case 5:
                                if (entityStepState(contPakAllocNote(temp_s0_4, gContPakNoteCode, gGameID, &gContPakSaveData, &gContPakNoteAttr, temp_v0, &sp40), arg1, temp_v0) == 0) {
                                    goto block_20;
                                }
                                goto loop_1;
                            }
                            goto block_24;
                        }
                        goto loop_1;
                    }
block_19:
block_20:
                    if (gHandlerCtx.unk168 != 0) {
                        if (entityStepState(contPakWriteNote((arg1 * 0x68) + (&gHandlerCtx + 0x17C), sp40, 1, 0, temp_v0, sfxGetEntry(sp44)), arg1, temp_v0) == 0) {
                            if (gHandlerCtx.unk168 == 0) {
                                goto block_23;
                            }
                        } else {
                            goto loop_1;
                        }
                    } else {
                        goto block_24;
                    }
                } else {
                    goto block_24;
                }
            } else {
                goto loop_1;
            }
            break;
        default:
            if (entityStepState(temp_v0_3, arg1, temp_v0) == 0) {
                gContPakHandlerPhase = 0;
                goto block_19;
            }
            goto loop_1;
        }
    } else {
block_23:
block_24:
        handlerPostCmd(0x56, arg1, 0, 0, 0, 0, 0);
    }
    sfxPlay(sp44);
    gHandlerCtx.unk160 = (s32) (gHandlerCtx.unk160 - 1);
}
