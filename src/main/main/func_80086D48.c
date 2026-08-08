#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x4];
    /* 0x04 */ s32 unk4;
} UnkStruct_arg0;

s32 osSpGetStatus();                                /* static */
extern s32 gViCfgPtr;
extern s32 SP_STATUS_REG;

s32 osSpTaskYield(UnkStruct_arg0 *arg0) {
    s32 sp1C;
    s32 sp18;

    sp1C = osSpGetStatus();
    if (sp1C & 0x100) {
        sp18 = 1;
    } else {
        sp18 = 0;
    }
    if (sp1C & 0x80) {
        arg0->unk4 = (s32) (arg0->unk4 | sp18);
        arg0->unk4 = (s32) (arg0->unk4 & ~2);
    }
    return sp18;
}

s32 osSpGetStatus(void) {
    return SP_STATUS_REG;
}

void viMgrInit(void);  /* forward: GETTER_NOJR fallthrough */
void viMgrInitGetter(void) {
    viMgrInit();  /* GETTER_NOJR: loads gViCfgPtr into $t6, falls into viMgrInit */
}
