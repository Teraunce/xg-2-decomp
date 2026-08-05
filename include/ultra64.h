/**
 * ultra64.h — minimal N64 SDK type/macro stubs for xg2-decomp
 *
 * Covers only what boot.c / init.c / decompiled main functions use.
 * Expand as needed when decompiling further files.
 */

#ifndef _ULTRA64_H_
#define _ULTRA64_H_

/* ---- Basic integer types (SGI/N64 convention) ---- */
typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;
typedef unsigned long long  u64;
typedef signed char         s8;
typedef signed short        s16;
typedef signed int          s32;
typedef signed long long    s64;
typedef float               f32;
typedef double              f64;

/* ---- Pointer-sized integer types (N64 = 32-bit pointers) ---- */
typedef s32  intptr_t;
typedef u32  uintptr_t;

/* Volatile hardware-register variants */
typedef volatile u8         vu8;
typedef volatile u16        vu16;
typedef volatile u32        vu32;
typedef volatile u64        vu64;
typedef volatile s8         vs8;
typedef volatile s16        vs16;
typedef volatile s32        vs32;
typedef volatile s64        vs64;

/* ---- NULL / bool ---- */
#ifndef NULL
#define NULL ((void *)0)
#endif

/* ---- N64 hardware register base addresses ---- */
/* PI (Peripheral Interface) */
#define PI_BASE_REG         0xA4600000
#define PI_DRAM_ADDR_REG    (*(vu32 *)0xA4600000)
#define PI_CART_ADDR_REG    (*(vu32 *)0xA4600004)
#define PI_RD_LEN_REG       (*(vu32 *)0xA4600008)
#define PI_WR_LEN_REG       (*(vu32 *)0xA460000C)
#define PI_STATUS_REG       (*(vu32 *)0xA4600010)
#define PI_STATUS_DMA_BUSY  (1 << 0)
#define PI_STATUS_IO_BUSY   (1 << 1)
#define PI_STATUS_ERROR     (1 << 2)

/* SI (Serial Interface) */
#define SI_DRAM_ADDR_REG    (*(vu32 *)0xA4800000)
#define SI_PIF_ADDR_RD64B   (*(vu32 *)0xA4800004)
#define SI_PIF_ADDR_WR64B   (*(vu32 *)0xA4800010)
#define SI_STATUS_REG       (*(vu32 *)0xA4800018)
#define SI_STATUS_DMA_BUSY  (1 << 0)
#define SI_STATUS_RD_BUSY   (1 << 1)
#define SI_STATUS_DMA_ERROR (1 << 3)
#define SI_STATUS_INTERRUPT (1 << 12)

/* ---- MIPS cache operations (IDO inline asm — IDO uses asm(), not __asm__) ---- */
#define CACHE_OP(op, addr) \
    asm("cache " #op ", 0(" #addr ")")

#define ICACHE_INDEX_STORE_TAG  0x08
#define ICACHE_HIT_INVALIDATE   0x10
#define DCACHE_HIT_WRITEBACK_INVAL 0x15

/* ---- BREAK instruction ---- */
/* IDO 7.1 uses asm() — GCC __asm__ syntax is not supported */
#define BREAK(code) asm("break " #code)

/* ---- m2c decompiler helper macros ---- */
/* M2C_BREAK(n): emits a MIPS BREAK n instruction (trap / assertion) */
#define M2C_BREAK(n) BREAK(n)
/* M2C_MEMCPY_ALIGNED(dst,src,n): word-aligned block copy m2c can't express
 * as a struct assignment.  memcpy() with aligned args compiles identically. */
extern void *memcpy(void *, const void *, unsigned long);
#define M2C_MEMCPY_ALIGNED(dst, src, n) memcpy((void *)(dst), (const void *)(src), (n))

/* ---- OS thread / message types ---- */
typedef s32 OSPri;
typedef s32 OSId;
typedef void *OSMesg;


/* Pull in OS thread/queue types so OSThread and OSMesgQueue are known
 * before the libultra function stubs that reference them. */
#include "os.h"

/* ---- libultra function stubs (declared, not defined here) ---- */
extern void osInitialize(void);
extern void osCreateMesgQueue(OSMesgQueue *mq, OSMesg *msg, s32 count);
extern s32  osSendMesg(OSMesgQueue *mq, OSMesg msg, s32 flag);
extern s32  osRecvMesg(OSMesgQueue *mq, OSMesg *msg, s32 flag);

#define OS_MESG_NOBLOCK  0
#define OS_MESG_BLOCK    1

/* Catch-all opaque struct for unknown pointer types from decompiler output */
#include "unk.h"

#endif /* _ULTRA64_H_ */
