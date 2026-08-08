#include "ultra64.h"
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u32 unk10;
    /* 0x14 */ u32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
} UnkStruct_sp24;

s32 __osGetCount();                                /* extern */
s32 osSendMesg(Unk*, s32, s32);                       /* extern */
void __osTimerSetCompare(s32, u32);                          /* extern */
u32 __osTimerEnqueue(void*);                            /* extern */
void setCOP0Compare();                              /* extern */
extern void **gOSMsgQueuePtr;
extern s32 D_80189A98;

void __osTimerHandler(void) {
    UnkStruct_sp24 *sp24;
    s32 sp20;
    u32 sp1C;
    char *sp18;
    s32 temp_t6_2;
    u32 temp_t3;
    u32 temp_t6;
    u32 temp_t8;
    u32 temp_t9_2;
    char *temp_t9;

    /* implicit $t6: linked-list head ptr from caller; beq *$t6,$t6 = list-empty sentinel */
    if ((s32)0 /* *implicit_t6 */ != (s32)0 /* implicit_t6 */) {
loop_1:
        temp_t9 = *gOSMsgQueuePtr;
        sp24 = temp_t9;
        if ((void*)temp_t9 == (void*)gOSMsgQueuePtr) {
            setCOP0Compare();
            D_80189A98 = 0;
            return;
        }
        sp20 = __osGetCount();
        sp1C = sp20 - D_80189A98;
        D_80189A98 = sp20;
        temp_t6 = sp24->unk10;
        if ((temp_t6 >= 0U) && ((temp_t6 > 0U) || (sp1C < (u32) sp24->unk14))) {
            sp18 = sp24 + 0x10;
            temp_t3 = sp24->unk14;
            sp24->unk14 = (u32) (temp_t3 - sp1C);
            sp24->unk10 = (u32) ((sp24->unk10 - 0) - (temp_t3 < sp1C));
            __osTimerSetCompare(sp24->unk10, sp24->unk14);
            return;
        }
        *(void**)(s32)sp24->unk4 = (void*)(s32)sp24->unk0;
        ((Unk *)sp24->unk0)->unk4 = (s32)sp24->unk4;
        sp24->unk0 = 0;
        sp24->unk4 = 0;
        temp_t6_2 = sp24->unk18;
        if (temp_t6_2 != 0) {
            osSendMesg(temp_t6_2, sp24->unk1C, 0);
        }
        temp_t8 = sp24->unk8;
        temp_t9_2 = sp24->unkC;
        if ((temp_t8 != 0) || (temp_t9_2 != 0)) {
            sp24->unk10 = temp_t8;
            sp24->unk14 = temp_t9_2;
            __osTimerEnqueue(sp24);
        }
        goto loop_1;
    }
}
