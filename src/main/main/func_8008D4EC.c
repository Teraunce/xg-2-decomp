#include "ultra64.h"
s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
void bzero(s32, s32);                           /* extern */
extern char *D_8009649C;
extern char *D_8018C288;
extern u8 D_8018C28E;
extern u8 D_8018C28F;
extern u8 D_8018C290;
extern s8 D_8018C291;
extern char *D_8018C2FC;
extern s32 D_A4600024;
extern s32 D_A4600028;
extern s32 D_A460002C;
extern s32 D_A4600030;

void **func_8008D4EC(void) {
    s32 sp1C;
    s32 temp_v0;

    D_8018C291 = 1;
    D_A4600024 = 3;
    D_A4600028 = (s32) D_8018C290;
    D_A460002C = (s32) D_8018C28E;
    D_A4600030 = (s32) D_8018C28F;
    bzero(&D_8018C288 + 0x14, 0x60);
    temp_v0 = osDisableInt();
    D_8018C288 = D_8009649C;
    D_8009649C = &D_8018C288;
    sp1C = temp_v0;
    D_8018C2FC = &D_8018C288;
    osRestoreInt(sp1C);
    return &D_8018C288;
}

void func_8008D5A8(void) {

}
