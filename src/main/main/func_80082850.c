#include "ultra64.h"
void func_8007DA18(Unk*);                               /* extern */
void func_8007DA48(Unk*, void**);                       /* extern */
extern Unk *gPendingFlushFlag;

void func_80082850(Unk *arg0) {
    s32 var_s0;

    var_s0 = arg0->unk14;
    if (var_s0 != 0) {
        do {
            func_8007DA18(var_s0);
            func_8007DA48(var_s0, arg0 + 4);
            var_s0 = arg0->unk14;
        } while (var_s0 != 0);
    }
}

void func_800828B0(Unk *arg0) {
    arg0->unk0 = gPendingFlushFlag->unk2C;
    gPendingFlushFlag->unk2C = arg0;
}

char *func_800828C8(void) {
    char *temp_a0;
    char *var_v1;

    var_v1 = NULL;
    temp_a0 = gPendingFlushFlag->unk2C;
    if (temp_a0 != NULL) {
        var_v1 = temp_a0;
        gPendingFlushFlag->unk2C = (void *) *temp_a0;
        *temp_a0 = 0;
    }
    return var_v1;
}

void func_800828F8(void) {

}
