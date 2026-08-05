#include "ultra64.h"
void osCreateMesgQueue(Unk*, s32, s32);                       /* extern */
void osCreateThread(OSThread*, OSId, u32, s32, u32, OSPri);    /* extern */
s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
void osSetEventMesg(s32, s32, s32);                     /* extern */
void func_8007D008(Unk*, s32);                            /* extern */
void osStartThread(Unk*);                               /* extern */
void func_8007D278();                                  /* extern */
s32 func_80087138(char*);                               /* extern */
void osViInit();                                  /* extern */
extern char *D_800955C0;
extern s32 D_800955D0;
extern s32 D_80189AE8;
extern s32 D_80189C98;
extern s32 D_8018AC98;
extern s32 D_8018ACB0;
extern s16 D_8018ACC8;
extern s16 D_8018ACE0;
extern s32 func_80086F60;

void func_80086DE0(s32 arg0) {
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 temp_v0;

    if ((s32)0 /* implicit $t6 from caller */ == 0) {
        func_8007D278();
        osCreateMesgQueue(&D_8018AC98, &D_8018ACB0, 5);
        D_8018ACC8 = 0xD;
        D_8018ACC8 = 0;
        D_8018ACC8 = 0;
        D_8018ACE0 = 0xE;
        D_8018ACE0 = 0;
        D_8018ACE0 = 0;
        osSetEventMesg(7, &D_8018AC98, &D_8018ACC8);
        osSetEventMesg(3, &D_8018AC98, &D_8018ACE0);
        sp28 = -1;
        sp24 = func_80087138(0);
        if (sp24 < arg0) {
            sp28 = sp24;
            func_8007D008(0, arg0);
        }
        temp_v0 = osDisableInt();
        D_800955C0 = (void *)1;
        D_800955C0 = &D_80189AE8;
        D_800955C0 = &D_8018AC98;
        D_800955C0 = &D_8018AC98;
        sp2C = temp_v0;
        D_800955D0 = 0;
        D_800955D0 = 0;
        D_800955D0 = 0;
        osCreateThread(&D_80189AE8, 0, &func_80086F60, &D_800955C0, &D_80189C98 + 0x1000, arg0);
        osViInit();
        osStartThread(&D_80189AE8);
        osRestoreInt(sp2C);
        if (sp28 != -1) {
            func_8007D008(0, sp28);
        }
    }
}
