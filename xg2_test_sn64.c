typedef int s32; typedef unsigned int u32;
typedef struct { s32 unk0; int pad[1]; s32 unk8; int pad2[1]; s32 unk10; } S;
s32 func_80081730(S*);
s32 func_80081B58(S *a0, s32 *a1) {
    s32 v = a0->unk8;
    if ((u32)v >= (u32)(a0->unk0 + a0->unk10)) return 0;
    *a1 = func_80081730(a0);
    a0->unk8 = v;
    return 1;
}
