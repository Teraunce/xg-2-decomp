#include "ultra64.h"
s32 __osEnqueueWait(void *);                            /* extern */
s32 __osPopQueue(void *);                          /* extern */
s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
void osStartThread(Unk*);                               /* extern */
extern Unk *__osRunningThread;

s32 osSendMesg(OSMesgQueue *mq, OSMesg msg, s32 flag) {
    Unk *arg0 = (Unk *)mq;
    s32 arg1 = (s32)(s32)msg;
    s32 arg2 = flag;
    s32 temp_s0;

    temp_s0 = osDisableInt();
    if (arg0->unk8 >= arg0->unk10) {
loop_1:
        if (arg2 == 1) {
            __osRunningThread->unk10 = 8;
            __osEnqueueWait(arg0 + 4);
            if (arg0->unk8 < arg0->unk10) {
                goto block_5;
            }
            goto loop_1;
        }
        osRestoreInt(temp_s0);
        return -1;
    }
block_5:
    *(s32*)((s32)arg0->unk14 + (((s32) (arg0->unkC + arg0->unk8) % (s32) arg0->unk10) * 4)) = arg1;
    arg0->unk8 = (s32) (arg0->unk8 + 1);
    if (((Unk*)(s32)arg0->unk0)->unk0 != 0) {
        osStartThread(__osPopQueue(arg0));
    }
    osRestoreInt(temp_s0);
    return 0;
}
