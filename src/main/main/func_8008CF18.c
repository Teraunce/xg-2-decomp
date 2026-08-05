#include "ultra64.h"
void osCreateMesgQueue(Unk*, s32, s32);                     /* extern */
void osCreateThread(OSThread*, OSId, u32, s32, u32, OSPri);    /* extern */
s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
void osSetEventMesg(s32, s32, s32);                         /* extern */
void osSetThreadPri(Unk*, s32);                            /* extern */
void osStartThread(Unk*);                               /* extern */
s32 func_80087138(char*);                               /* extern */
void func_8008E458();                                  /* extern */
extern char *D_80096480;
extern char *D_80096490;
extern s32 D_800964B0;
extern s32 D_8018B038;
extern s32 D_8018B1E8;
extern s32 D_8018C1E8;
extern s32 D_8018C200;
extern s32 D_8018D310;
extern s32 osEPiStartDma_simple;
extern s32 osEPiStartDma;
extern s32 gfxDmaEventLoop;

void osEPiLoad(s32 arg0, char *arg1, char *arg2, s32 arg3) {
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 temp_v0;

    if (D_80096480 == NULL) {
        osCreateMesgQueue(arg1, arg2, arg3);
        osCreateMesgQueue(&D_8018C1E8, &D_8018C200, 1);
        if (D_800964B0 == 0) {
            func_8008E458();
        }
        osSetEventMesg(8, &D_8018C1E8, 0x22222222);
        sp28 = -1;
        sp24 = func_80087138(0);
        if (sp24 < arg0) {
            sp28 = sp24;
            osSetThreadPri(0, arg0);
        }
        temp_v0 = osDisableInt();
        D_80096480 = (void *)1;
        D_80096480 = &D_8018B038;
        D_80096480 = &D_8018C1E8;
        D_80096480 = arg1;
        sp2C = temp_v0;
        D_80096490 = &D_8018D310;
        D_80096490 = &osEPiStartDma_simple;
        D_80096490 = &osEPiStartDma;
        osCreateThread(&D_8018B038, 0, &gfxDmaEventLoop, &D_80096480, &D_8018B1E8 + 0x1000, arg0);
        osStartThread(&D_8018B038);
        osRestoreInt(sp2C);
        if (sp28 != -1) {
            osSetThreadPri(0, sp28);
        }
    }
}
