#include "ultra64.h"
void audioQueueStop(s32);                               /* extern */
extern s32 D_80181588;

void func_8005F530(void) {
    Unk *var_s0;
    s32 temp_a0;
    s32 var_s1;

    var_s1 = 0;
    if ((s32)0 /* implicit $v0 from caller */ > 0) {
        var_s0 = &D_80181588;
        do {
            var_s1 += 1;
            audioQueueStop(var_s0->unk10);
            audioQueueStop(var_s0->unk14);
            audioQueueStop(var_s0->unk18);
            temp_a0 = var_s0->unk1C;
            var_s0 += 0x30;
            audioQueueStop(temp_a0);
        } while (var_s1 < ((Unk*)0 /* implicit $v1 */)->unk1648);
    }
}
