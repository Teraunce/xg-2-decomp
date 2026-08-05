#include "ultra64.h"
void __osTimerUnlink(Unk*);                               /* extern */
void __osTimerInsert(Unk*, void**);                       /* extern */
extern Unk *gPendingFlushFlag;

void sfxFlushTimers(Unk *arg0) {
    s32 var_s0;

    var_s0 = arg0->unk14;
    if (var_s0 != 0) {
        do {
            __osTimerUnlink(var_s0);
            __osTimerInsert(var_s0, arg0 + 4);
            var_s0 = arg0->unk14;
        } while (var_s0 != 0);
    }
}

void sfxEventEnqueue(Unk *arg0) {
    arg0->unk0 = gPendingFlushFlag->unk2C;
    gPendingFlushFlag->unk2C = arg0;
}

char *sfxEventDequeue(void) {
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
