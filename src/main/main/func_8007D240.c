#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of func_8007D304 (initial). */

extern Unk *gOSMsgQueuePtr;
extern s32 D_80189A8C;
extern s32 D_80189A90;
extern s32 D_80189A94;

void func_8007D240(void **arg1, char *arg2, char *arg3) {
    char *var_a2;
    char *var_a3;

    var_a2 = arg2;
    var_a3 = arg3;
    if (var_a3 != NULL) {
loop_1:
        if ((void*)var_a3 == (void*)arg1) {
            *var_a2 = *arg1;
            return;
        }
        var_a2 = var_a3;
        var_a3 = *var_a2;
        if (var_a3 == NULL) {

        } else {
            goto loop_1;
        }
    }
}

void func_8007D278(void) {
    D_80189A8C = 0;
    D_80189A8C = 0;
    D_80189A90 = 0;
    D_80189A94 = 0;
    gOSMsgQueuePtr->unk4 = (void *) gOSMsgQueuePtr;
    gOSMsgQueuePtr->unk0 = (void *) gOSMsgQueuePtr->unk4;
    gOSMsgQueuePtr->unk10 = 0;
    gOSMsgQueuePtr->unk14 = 0;
    gOSMsgQueuePtr->unk8 = (s32) gOSMsgQueuePtr->unk10;
    gOSMsgQueuePtr->unkC = (s32) gOSMsgQueuePtr->unk14;
    gOSMsgQueuePtr->unk18 = 0;
    gOSMsgQueuePtr->unk1C = 0;
}

void func_8007D30C(void);  /* forward: GETTER_NOJR fallthrough */
void func_8007D304(void) {
    func_8007D30C();
}
