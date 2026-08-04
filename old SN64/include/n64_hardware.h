#ifndef N64_HARDWARE_H
#define N64_HARDWARE_H

/*
 * N64 hardware register definitions.
 * All addresses are uncached (0xA4xxxxxx / 0xA0xxxxxx / 0xB1xxxxxx).
 * Access via *(volatile u32*)REGNAME.
 */

/* ---- SP (Signal Processor) ---- */
#define SP_MEM_ADDR_REG     0xA4040000u
#define SP_DRAM_ADDR_REG    0xA4040004u
#define SP_RD_LEN_REG       0xA4040008u
#define SP_WR_LEN_REG       0xA404000Cu
#define SP_STATUS_REG       0xA4040010u

/* SP_STATUS_REG bits */
#define SP_STATUS_HALT          0x0001
#define SP_STATUS_BROKE         0x0002
#define SP_STATUS_DMA_BUSY      0x0004
#define SP_STATUS_DMA_FULL      0x0008
#define SP_STATUS_IO_FULL       0x0010
#define SP_STATUS_SSTEP         0x0020
#define SP_STATUS_INTR_BREAK    0x0040
#define SP_CLR_HALT             0x0001  /* write to clear HALT */
#define SP_SET_HALT             0x0002  /* write to set HALT  */

/* ---- DP Command (RDP) ---- */
#define DPC_START_REG       0xA4080000u
#define DPC_END_REG         0xA4080004u
#define DPC_CURRENT_REG     0xA4080008u
#define DPC_STATUS_REG      0xA408000Cu

/* ---- MI (MIPS Interface) ---- */
#define MI_MODE_REG         0xA4300000u
#define MI_VERSION_REG      0xA4300004u
#define MI_INTR_REG         0xA4300008u
#define MI_INTR_MASK_REG    0xA430000Cu

/* MI_INTR_REG / MI_INTR_MASK_REG bits */
#define MI_INTR_SP      0x01
#define MI_INTR_SI      0x02
#define MI_INTR_AI      0x04
#define MI_INTR_VI      0x08
#define MI_INTR_PI      0x10
#define MI_INTR_DP      0x20

/* ---- VI (Video Interface) ---- */
#define VI_STATUS_REG       0xA4400000u  /* VI_CONTROL_REG */
#define VI_ORIGIN_REG       0xA4400004u  /* framebuffer DRAM address */
#define VI_WIDTH_REG        0xA4400008u
#define VI_INTR_REG         0xA440000Cu  /* VI_V_INTR_REG */
#define VI_CURRENT_REG      0xA4400010u  /* VI_V_CURRENT_LINE_REG */
#define VI_BURST_REG        0xA4400014u  /* VI_TIMING_REG */
#define VI_V_SYNC_REG       0xA4400018u
#define VI_H_SYNC_REG       0xA440001Cu
#define VI_LEAP_REG         0xA4400020u  /* VI_H_SYNC_LEAP_REG */
#define VI_H_START_REG      0xA4400024u  /* VI_H_VIDEO_REG */
#define VI_V_START_REG      0xA4400028u  /* VI_V_VIDEO_REG */
#define VI_V_BURST_REG      0xA440002Cu
#define VI_X_SCALE_REG      0xA4400030u
#define VI_Y_SCALE_REG      0xA4400034u

/* VI_STATUS_REG pixel format bits */
#define VI_CTRL_TYPE_16     0x002   /* 16-bit color (5-5-5-1) */
#define VI_CTRL_TYPE_32     0x003   /* 32-bit color */
#define VI_CTRL_GAMMA_DITHER_EN 0x004
#define VI_CTRL_GAMMA_EN    0x008
#define VI_CTRL_DIVOT_EN    0x010
#define VI_CTRL_SERRATE     0x040   /* interlaced output */
#define VI_CTRL_ANTIALIAS_MASK  0x300

/* ---- AI (Audio Interface) ---- */
#define AI_DRAM_ADDR_REG    0xA4500000u
#define AI_LEN_REG          0xA4500004u
#define AI_CONTROL_REG      0xA4500008u
#define AI_STATUS_REG       0xA450000Cu
#define AI_DACRATE_REG      0xA4500010u
#define AI_BITRATE_REG      0xA4500014u

/* AI_STATUS_REG bits */
#define AI_STATUS_BUSY      0x40000000u
#define AI_STATUS_FULL      0x80000000u

/* ---- PI (Peripheral Interface) ---- */
#define PI_DRAM_ADDR_REG    0xA4600000u
#define PI_CART_ADDR_REG    0xA4600004u
#define PI_RD_LEN_REG       0xA4600008u
#define PI_WR_LEN_REG       0xA460000Cu
#define PI_STATUS_REG       0xA4600010u
#define PI_BSD_DOM1_LAT_REG 0xA4600014u
#define PI_BSD_DOM1_PWD_REG 0xA4600018u
#define PI_BSD_DOM1_PGS_REG 0xA460001Cu
#define PI_BSD_DOM1_RLS_REG 0xA4600020u
#define PI_BSD_DOM2_LAT_REG 0xA4600024u
#define PI_BSD_DOM2_PWD_REG 0xA4600028u
#define PI_BSD_DOM2_PGS_REG 0xA460002Cu
#define PI_BSD_DOM2_RLS_REG 0xA4600030u

/* PI_STATUS_REG bits */
#define PI_STATUS_DMA_BUSY      0x01
#define PI_STATUS_IO_BUSY       0x02
#define PI_STATUS_ERROR         0x04
#define PI_STATUS_RESET         0x01  /* write to reset */
#define PI_STATUS_CLR_INTR      0x02  /* write to clear interrupt */

/* ---- SI (Serial Interface — controllers/PIF) ---- */
#define SI_DRAM_ADDR_REG        0xA4800000u
#define SI_PIF_ADDR_RD64B_REG   0xA4800004u
#define SI_PIF_ADDR_WR64B_REG   0xA4800010u
#define SI_STATUS_REG           0xA4800018u

/* SI_STATUS_REG bits */
#define SI_STATUS_DMA_BUSY      0x01
#define SI_STATUS_RD_BUSY       0x02
#define SI_STATUS_DMA_ERROR     0x08
#define SI_STATUS_INTERRUPT     0x1000

/* ---- Cart SRAM save area (0xB1xxxxxx = uncached DOM2) ---- */
#define SRAM_SAVE_DATA          0xB1FFFFD8u
#define SRAM_SAVE_DATA2         0xB1FFFFF0u

/* ---- Uncached RDRAM base ---- */
#define RDRAM_BASE_UNCACHED     0xA0000000u

/* ---- N64 controller button bitmasks (osContPad.button) ---- */
#define CONT_A          0x8000
#define CONT_B          0x4000
#define CONT_G          0x2000  /* Z trigger */
#define CONT_START      0x1000
#define CONT_UP         0x0800  /* D-pad up */
#define CONT_DOWN       0x0400  /* D-pad down */
#define CONT_LEFT       0x0200  /* D-pad left */
#define CONT_RIGHT      0x0100  /* D-pad right */
#define CONT_L          0x0020  /* L trigger */
#define CONT_R          0x0010  /* R trigger */
#define CONT_C_UP       0x0008
#define CONT_C_DOWN     0x0004
#define CONT_C_LEFT     0x0002
#define CONT_C_RIGHT    0x0001

/* Convenience macro: read a 32-bit MMIO register */
#define IO_READ(reg)        (*(volatile unsigned int *)(reg))
#define IO_WRITE(reg, val)  (*(volatile unsigned int *)(reg) = (val))

#endif /* N64_HARDWARE_H */
