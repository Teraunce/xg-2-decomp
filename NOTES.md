# Extreme-G XG2 Decompilation Notes

ROM SHA1: ed0a50086ef9a89f5b445c20ab6f365165959630
ROM size: 12 MB (0xC00000 bytes)

---

## Build System Status

### Toolchain (all confirmed working)

| Tool | Version | Path |
|------|---------|------|
| IDO C compiler | 7.1 (Decompals v1.2, 2024-11-12) | `tools/ido/cc` |
| GNU as (MIPS big-endian) | 2.38 (Ubuntu cross) | `tools/mips-binutils/bin/mips-linux-gnu-as` |
| GNU ld | 2.38 | `tools/mips-binutils/bin/mips-linux-gnu-ld` |
| GNU objcopy | 2.38 | `tools/mips-binutils/bin/mips-linux-gnu-objcopy` |

Binutils shared libs at `tools/mips-binutils/lib/`. Set `LD_LIBRARY_PATH` to that path
when invoking any mips-binutils binary.

### Byte-Match Verification Results

`tools/verify_boot.py` — Python script that applies MIPS ELF relocations manually
and compares built bytes against ROM. Run as:

```bash
python3 tools/verify_boot.py
```

| Section | Status | Notes |
|---------|--------|-------|
| `asm/boot/boot.s` → ROM:0x1000 (0x98 bytes) | **✓ BYTE-EXACT** | 9 relocations resolved |
| `asm/boot/init.s` → ROM:0x1098 (0x588 bytes) | **✓ BYTE-EXACT** | 18 relocations resolved |
| Main decompressed code (450 funcs, 0x4AB20 bytes) | pending | Assembly files present; needs linker script |

### Key Assembler Flags

```
mips-linux-gnu-as -march=vr4300 -mabi=32 -G0 -EB -I include
```

### Key Compiler Flags (IDO 7.1)

```
cc -O2 -mips2 -G0 -Wab,-r4300_mul -non_shared -Xcpluscomm -woff 649,838,712 -signed
```

---

## Boot Sequence

IPL3 (CIC-6102) reads the **boot address** from the ROM header: `0x8004B400`.
It copies `ROM[0x1000..0x101000]` (1 MB) to `VRAM:0x8004B400` and jumps there.

> **CRITICAL**: The VRAM base is `0x8004B400`, NOT `0x80000400`.
> All VRAM addresses = `0x8004A400 + ROM_offset`.

### 1MB Initial Load Map

| ROM offset | VRAM       | Content                               |
|-----------|------------|---------------------------------------|
| 0x001000  | 0x8004B400 | Boot stub (func_8004B400, 35 instrs)  |
| 0x001094  | 0x8004B494 | 4-byte pad (0x74680200, invalid op)   |
| 0x001098  | 0x8004B498 | LZSS decompressor (func_8004B498)     |
| 0x001620  | 0x8004BA20 | LZSS block header (24 bytes)          |
| 0x001638  | 0x8004BA38 | LZSS compressed data (177,519 bytes)  |
| 0x04C000  | 0x80096400 | Overlay destination area (overwritten)|
| 0x101000  | 0x8014B400 | End of 1MB load                       |

### Execution Flow

1. **func_8004B400** (boot stub):
   - Clears two BSS ranges (both zero-length in shipped ROM)
   - Calls **func_8004B498** (never returns)

2. **func_8004B498** (LZSS decompressor):
   - Polls SI status (0xA4800018) until ready, reads PIF RAM (0xBFC007FC)
   - Copies 0x2B588 bytes from VRAM:0x8004BA20 to VRAM:0x8024BA20 (staging)
   - Zeros 4078 bytes of ring buffer on stack (sp+0x10..sp+0x100D)
   - LZSS-decompresses staging -> VRAM:0x8004BA20 (overwrites the source)
   - Calls **func_8004B464** (icache flush)
   - jalr -> VRAM:0x8004BA20 (decompressed code entry, never returns)

3. **func_8004B464** (icache flush):
   - Cache-Index-Invalidates [0x80000000, 0x80002000) in 0x10-byte steps

---

## LZSS Decompressor Parameters

Format: Okumura LZSS with custom 24-byte header.

| Parameter        | Value                               |
|-----------------|-------------------------------------|
| Ring size        | 4096 bytes                          |
| Fill value       | 0x00 (RDRAM-initialized)            |
| Initial write pos| 0xFEE (4078)                        |
| Bit convention   | 1=literal, 0=back-ref               |
| Flag byte order  | LSB first                           |
| Sentinel         | flag_byte OR 0xFF00; bit8=0 triggers new fetch |
| Min match length | 3  ((k & 0x0F) + 3)                |
| Max match length | 18                                  |
| Offset encoding  | j OR ((k & 0xF0) << 4)  (12-bit)   |
| Termination      | output byte counter from header[+0x10] |

### LZSS Block Header (ROM:0x1620 / VRAM:0x8004BA20)

```
+0x00  u32  version  = 0x00000001
+0x04  u32  pad      = 0x00000000
+0x08  u32  hdr_size = 0x00000018  <- used to locate compressed data start
+0x0C  u32  magic    = 0x4C5A5353  ('LZSS')
+0x10  u32  out_size = 0x0004AB20  (305,952 bytes) <- output byte counter ($t3)
+0x14  u32  in_size  = 0x0002B56F  (177,519 bytes)
+0x18  u8[] compressed data...
```

Compressed data: ROM:0x1638 -> ROM:0x41BA7 (177,519 bytes).
Output: VRAM:0x8004BA20 -> VRAM:0x80096540 (305,952 bytes).

### Output Region Notes

- First 283,352 bytes: MIPS code (450 functions identified via RDRAM scan).
- Bytes 283,352+: zero-initialized data tables (function pointer arrays, vtables).
  The BizHawk main-menu dump has non-zero values there because the game's
  runtime init fills them in AFTER decompression. The LZSS output is
  CORRECTLY all zeros there.

---

## Overlay System

### '2fak' File Table (ROM:0x124C / VRAM:0x8004B64C)

Magic: `0x3266616B` ('2fak'), followed by 122 entries of `(u32 rom_offset, u32 size)`.
Each entry describes one asset/overlay block in the ROM.

#### Top-Level Entries (0–7): Major ROM Sections

| Idx | ROM offset | Size      | Description                              |
|-----|-----------|-----------|------------------------------------------|
| 0   | 0xB23580  | 0x59E0    | Unknown block (magic 0x00020801)         |
| 1   | 0xA4DF10  | 0xD5670   | Asset directory (0xD2 entries × 0x10 B)  |
| 2   | 0x7DD9E0  | 0x77B0    | 'B1' format block (textures/models?)     |
| 3   | 0x7E5190  | 0x17DBC0  | Large data block                         |
| 4   | 0x962D50  | 0x4020    | 'B1' format block                        |
| 5   | 0x966D70  | 0xC46C0   | Mixed-format block                       |
| 6   | 0xA2B430  | 0x22AE0   | Data block                               |
| 7   | 0x1107E0  | 0         | Null/terminator (size=0)                 |

Entries 2–6 form a sequential chain ending at entry 1's start (0xA4DF10).
Entry 1 ends at entry 0's start (0xB23580).
Entry 0 ends at entry 8's start (0xB28F60).

#### Entries 8–34: LZSS-Compressed Code Overlays

All confirmed as LZSS blocks (magic 0x00000001/0x4C5A5353). Loaded at runtime
into VRAM:0x8010EB00–0x8014B400 area. Each decompresses to 28–92 KB of code.

| Idx | ROM offset | Comp size | Decomp size | Notes            |
|-----|-----------|-----------|-------------|------------------|
| 8   | 0xB28F60  | 0x2E20    | 0x77B0      | Track 1?         |
| 9   | 0xB2BD80  | 0x4650    | 0x846C      |                  |
| 10  | 0xB303D0  | 0x28D0    | 0x74D8      |                  |
| 11  | 0xB32CA0  | 0x3900    | 0x6E90      |                  |
| 12  | 0xB365A0  | 0x3D70    | 0x790C      |                  |
| 13  | 0xB3A310  | 0x2D00    | 0x7428      |                  |
| 14  | 0xB3D010  | 0x23B0    | 0x7538      |                  |
| 15  | 0xB3F3C0  | 0x41A0    | 0x8DD8      |                  |
| 16  | 0xB43560  | 0x3BD0    | 0x74DC      |                  |
| 17  | 0xB47130  | 0x3D90    | 0x9248      |                  |
| 18  | 0xB4AEC0  | 0x3160    | 0x7590      |                  |
| 19  | 0xB4E020  | 0x31B0    | 0x72F0      |                  |
| 20  | 0xB511D0  | 0x3DFE0   | 0x6C118     | HUGE — audio/FMV?|
| 21  | 0xB8F1B0  | 0x3AD0    | 0x42D0      |                  |
| 22  | 0xBA0570  | 0x51C0    | 0x8758      |                  |
| 23  | 0xBA5730  | 0x6570    | 0xA0C0      |                  |
| 24  | 0xBABCA0  | 0x5AA0    | 0x8C24      |                  |
| 25  | 0xBB1740  | 0x5B30    | 0x97C4      |                  |
| 26  | 0xBB7270  | 0x4CC0    | 0x8B1C      |                  |
| 27  | 0xBBBF30  | 0x75D0    | 0xB270      |                  |
| 28  | 0xBC3500  | 0x53E0    | 0x8BD4      |                  |
| 29  | 0xBC88E0  | 0x5120    | 0x9EE8      |                  |
| 30  | 0xBCDA00  | 0x4CA0    | 0x7764      |                  |
| 31  | 0xBD26A0  | 0x6380    | 0x9F9C      |                  |
| 32  | 0xBD8A20  | 0x6370    | 0xB090      |                  |
| 33  | 0xBDED90  | 0x5D90    | 0x95D8      |                  |
| 34  | 0xBE4B20  | 0x8160    | 0xB1C0      |                  |

Entries 36–41 (ROM:0xB92C80–0xBA0570) are a second sequential LZSS block
(decompressing to 0x26A0–0x2540 bytes each); interleaved with entries 22+.

#### Entries 42+: Audio/Level Data Files

Alternating pattern of `(rom_offset, size)` / `(0, 5)` null separators.
Files in range 0x92000–0x10C9D0, sizes ~0x5800 each. Likely audio samples or
track-specific level geometry.

### DMA Loader Functions

| VRAM       | Name              | Description                                   |
|-----------|-------------------|-----------------------------------------------|
| 0x80074F08 | func_80074F08    | PI raw write: wait for PI_STATUS, sw arg1→arg0 |
| 0x80074F40 | func_80074F40    | PI raw read: wait for PI_STATUS, lw from arg0  |
| 0x8008CEC0 | func_8008CEC0    | osEPiRawReadIo equivalent                     |
| 0x8008D0A8 | func_8008D0A8    | PI DMA start (sets DRAM_ADDR, CART_ADDR, LEN) |
| 0x8008D188 | func_8008D188    | PI DMA start with domain config update        |
| 0x8008CF18 | func_8008CF18    | Overlay loader (schedules async DMA+decomp)   |
| 0x8008D3C0 | func_8008D3C0    | PI domain init (reads from 0xB0000000)        |

PI registers used: 0xA4600000 (DRAM_ADDR), 0xA4600004 (CART_ADDR),
0xA4600008 (RD_LEN), 0xA460000C (WR_LEN), 0xA4600010 (STATUS).

### Decompressed Code Memory Layout

| VRAM range              | Size   | Content                                  |
|------------------------|--------|------------------------------------------|
| 0x8004BA20–0x8004D138  | 5.5KB  | Entry stub (BSS clear + call game init)  |
| 0x8004D138–0x80090CF8  | 270KB  | 450 game functions (code)                |
| 0x80090CF8–0x80096540  | 22KB   | BSS/data region (zero-initialized)       |

Entry stub BSS clear ranges (from disassembly):
- [0x8016D1D0, 0x8018D328)  — 114 KB
- [0x8016D1D0, 0x8016D1D0)  — 0 B (empty, always skipped)
- [0x8018D328, 0x8018F718)  — 8 KB
- [0x80190000, 0x801A3000)  — 76 KB (approx)

Then calls func_8004E094 (game init), then BREAK.

740 total function prologues found in the RDRAM dump at main menu.
450 are in the decompressed region (0x8004BA20–0x80096540).
~290 are in overlay space (0x8010EB00+).

---

## Compiler

Expected: **IDO 7.1** (Silicon Graphics). Standard N64 compiler.
Flags: `-O2 -mips2` (typical for this era).

---

## Build System

- Splitter: splat 0.41.1 / spimdisasm 1.42.2
- Assembler: mips-linux-gnu-as  (-march=vr4300 -mabi=32 -G0 -EB)
- Decompiler: m2c v0.1.0 (matt-kempster/mips_to_c)
- Config: xg2.yaml / xg2.ld

Key splat config:
```yaml
- name: boot
  type: code
  start: 0x1000
  vram: 0x8004B400   # IPL3 boot address from ROM header
  subsegments:
    - [0x1000, asm, boot/boot]
    - [0x1094, bin, boot/boot_pad]
    - [0x1098, asm, boot/init]
    - [0x1620, bin, boot/compressed_main]
    - [0x4C000, bin, boot/overlay_dest]
    - [0x101000]
```

---

## Symbol Addresses

All VRAM = 0x8004A400 + ROM_offset.

| Symbol         | VRAM       | ROM       | Description                |
|---------------|------------|-----------|----------------------------|
| func_8004B400 | 0x8004B400 | 0x001000  | Boot stub entry            |
| func_8004B464 | 0x8004B464 | 0x001064  | Icache flush               |
| func_8004B498 | 0x8004B498 | 0x001098  | LZSS decompressor          |
| func_8004B5B8 | 0x8004B5B8 | 0x0011B8  | Back-ref copy inner loop   |
| D_8004BA20    | 0x8004BA20 | 0x001620  | LZSS block header          |
| D_80096400    | 0x80096400 | 0x04C000  | Overlay destination area   |

---

## Named Functions (symbol_addrs_named.txt)

47 functions identified and named. Key matches:

### N64 OS / libultra equivalents

| VRAM       | Name                    | Evidence                                           |
|-----------|-------------------------|----------------------------------------------------|
| 0x8007C9E8 | osInitialize           | installs exception vectors at 0x80000080/100/180   |
| 0x8007BA98 | osWritebackInvalDCache  | cache 0x15/0x11, 0x10-byte lines, thresh 0x2000   |
| 0x8007BB48 | osInvalICache           | cache 0x10/0x0, 0x20-byte lines, thresh 0x4000    |
| 0x8007BC28 | osWritebackDCache       | cache 0x19/0x1, 0x10-byte lines, thresh 0x2000    |
| 0x8007BCD8 | osCreateMesgQueue       | init: head=tail=&D_800952A0, cnt=0, size/buf args  |
| 0x8007BD08 | osCreateThread          | fills OSThread struct, links into D_800952AC list  |
| 0x8007C768 | osDisableInt            | returns prev SR, disables interrupts               |
| 0x8007C788 | osRestoreInt            | restores SR from osDisableInt result               |
| 0x8007CC78 | __osGetSR               | mfc0 $v0, $12                                      |
| 0x8007CC88 | __osGetFpcsr            | cfc1 $v0 (FPU CSR)                                 |
| 0x8007CC98 | __osSetSR               | mtc0 $a0, $12                                      |
| 0x8007CCA8 | __osInitTLB             | mtc0 + tlbwi to zero TLB                           |
| 0x8007D688 | osVirtualToPhysical     | strips KSEG0/1 prefix; TLB walk fallback           |
| 0x80086848 | osAiRawStartDma         | sets AI_DRAM_ADDR (0xA4500000) + AI_LEN            |
| 0x800866F4 | osAiSetFrequency        | computes AI_DACRATE / AI_BITRATE from freq arg     |
| 0x80086BD4 | osSpTaskStart           | polls SP idle, writes 0x125 to SP_STATUS           |
| 0x80086C48 | osSpSetStatus           | sw arg → SP_STATUS (0xA4040010)                    |
| 0x80086C60 | osSpSetPc               | sw arg → SP_PC (0xA4080000)                        |
| 0x80086C98 | osSpRawStartDma         | sets SP_MEM_ADDR/DRAM_ADDR/LEN regs               |
| 0x80086DC8 | osSpGetStatus           | lw from SP_STATUS                                  |
| 0x80087158 | osViInit                | init VI mode, VI_CONTROL=0, call osViSwapBuffer    |
| 0x80087298 | osViGetCurrentFramebuffer | returns D_80095640                              |
| 0x80087728 | osViSwapBuffer          | writes all VI regs from mode table, swaps buffers  |
| 0x80087AF8 | osEPiRawReadIo          | read from 0xA0000000|arg0; checks SI busy first    |
| 0x80087B78 | osEPiRawWriteIo         | write arg1 to 0xA0000000|arg0; checks SI busy      |
| 0x80087C78 | osSiRawStartDma         | SI_DRAM_ADDR + PIF_ADDR_RD/WR64B (0x1FC007C0)    |
| 0x80074F08 | __osPiRawWriteIo        | waits PI_STATUS & 3 == 0, sw arg1 → arg0           |
| 0x80074F40 | __osPiRawReadIo         | waits PI_STATUS & 3 == 0, lw from arg0             |
| 0x8008CEC0 | osEPiRawReadIo_cart     | reads from (D_80000308 | arg0 | 0xA0000000)       |
| 0x8008D0A8 | osEPiStartDma_simple    | sets PI DRAM_ADDR/CART_ADDR/LEN; no domain config  |
| 0x8008D188 | osEPiStartDma           | full osEPiStartDma with domain register update     |
| 0x8008CF18 | osEPiLoad               | async overlay loader via thread queue              |
| 0x8008D3C0 | osEPiGetDomainInfo      | reads from 0xB0000000, inits PI domain table       |

### Game-Specific Functions

| VRAM       | Name              | Description                                              |
|-----------|-------------------|----------------------------------------------------------|
| 0x8004BA20 | decompressed_entry| set sp=0x803FFFF0, clear 4 BSS ranges, call gameInit    |
| 0x8004D4A8 | heap_alloc_default| loads D_80090D00 (heap_end), falls into heap_alloc       |
| 0x8004D4B0 | heap_alloc        | bump allocator: D_80090D04=remaining, 16-byte aligned   |
| 0x8004E094 | gameInit          | first game fn: osInitialize, create main thread          |
| 0x8004E0F8 | gameMainThread    | init VI, load menu overlay, create next thread           |
| 0x8004E21C | gameMainLoop_setup| init queues, VI retrace, controller, main game loop      |

## Decompiled C Files

All 450 main-code functions have been m2c-decompiled:
- ASM: `asm/main/main/*.s` (451 files, splat-generated via `xg2_main.yaml`)
- C:   `src/main/main/*.c` (451 files, m2c output, not yet byte-matched)
- Data:`asm/main/data/main/data.data.s` (22 KB data section)

Symbol list: `symbol_addrs_main.txt` (450 typed function symbols)

## Open Questions

1. IDO 7.1 byte-match verification pending — needs install + Makefile integration.
2. Overlay VRAM load addresses: BizHawk-derived values (0x8010EB00 etc.) need
   re-verification against the actual DMA dispatcher (func_8008CF18) logic.
3. Entry 20 in the '2fak' table (decompresses to 442 KB) — needs identification.
4. Entries 42+ audio file format — determine sample rate/codec.
