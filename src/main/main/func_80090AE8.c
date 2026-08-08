#include "ultra64.h"
char *sfxEventDequeue(void *);                        /* extern */
s32 audioTimerAcquire(Unk*, void**, s16);            /* extern */

s32 sfxNoteAssign(Unk *arg0, Unk *arg1, Unk *arg2) {
    Unk *sp10;
    s32 *temp_v0;
    s32 temp_v0_2;
    Unk *temp_s1;
    Unk *temp_v0_3;
    Unk *temp_v0_4;

    temp_v0 = arg0->unk2C;
    sp10 = NULL;
    if ((temp_v0 == NULL) || (*temp_v0 == 0)) {
        return 0;
    }
    temp_v0_2 = audioTimerAcquire(arg0, &sp10, arg2->unk0);
    if (sp10 != NULL) {
        temp_s1 = sp10->unkC;
        if (temp_v0_2 != 0) {
            sp10->unkD8 = 0x200;
            ((Unk *)sp10->unk8)->unk8 = 0;
            temp_v0_3 = sfxEventDequeue(sp10);
            temp_v0_3->unk8 = 0xB;
            temp_v0_3->unkC = 0;
            temp_v0_3->unk4 = (s32) arg0->unk1C;
            temp_v0_3->unk10 = (s32) (sp10->unkD8 - 0x40);
            ((s32(*)())(s32)temp_s1->unk8)(temp_s1, 3, temp_v0_3);
            temp_v0_4 = sfxEventDequeue(NULL);
            if (temp_v0_4 != NULL) {
                temp_v0_4->unk8 = 0xF;
                temp_v0_4->unk0 = 0;
                temp_v0_4->unk4 = (s32) (arg0->unk1C + sp10->unkD8);
                ((s32(*)())(s32)temp_s1->unk8)(temp_s1, 3, temp_v0_4);
            }
        } else {
            sp10->unkD8 = 0;
        }
        arg1->unk16 = (u16) arg2->unk0;
        arg1->unkC = 0;
        arg1->unk1A = (s16) arg2->unk4;
        arg1->unk14 = 0;
        arg1->unk18 = (u16) arg2->unk2;
        sp10->unk8 = arg1;
        arg1->unk8 = sp10;
    }
    return sp10 != NULL;
}
