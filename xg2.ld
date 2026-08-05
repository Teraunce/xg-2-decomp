/* Absolute symbol definitions for boot-block hardware/memory constants.
 * These are addresses hardcoded in the LZSS decompressor (init_merged.s)
 * and the RDRAM initializer (boot.s).  The symbol name encodes the value.
 * Verified against raw instruction encodings (lui/addiu %hi/%lo). */
D_80000400 = 0x80000400;   /* RDRAM base (cleared by boot.s) */
D_80001000 = 0x80001000;   /* RDRAM end boundary */
D_2B588    = 0x0002B588;   /* ROM offset of LZSS-compressed main block */
D_8004BA20 = 0x8004BA20;   /* Destination buffer / end of boot in RAM */
D_8024BA20 = 0x8024BA20;   /* Decompressed main block load address in RAM */
D_8024BA28 = 0x8024BA28;   /* LZSS header field (compressed size / dest ptr) */

SECTIONS
{
    HIDDEN(__romPos = 0);
    _gp = 0x0;
    header_ROM_START = __romPos;
    header_VRAM = ADDR(.header);
    .header 0x80000000 : AT(header_ROM_START) SUBALIGN(16)
    {
        FILL(0x00000000);
        header_DATA_START = .;
        build/asm/header.o(.data);
        header_DATA_END = .;
        header_DATA_SIZE = ABSOLUTE(header_DATA_END - header_DATA_START);
    }
    __romPos += SIZEOF(.header);
    header_ROM_END = __romPos;
    header_VRAM_END = .;

    ipl3_ROM_START = __romPos;
    ipl3_VRAM = ADDR(.ipl3);
    .ipl3 0xA4000040 : AT(ipl3_ROM_START) SUBALIGN(16)
    {
        FILL(0x00000000);
        ipl3_DATA_START = .;
        build/assets/ipl3.o(.data);
        ipl3_DATA_END = .;
        ipl3_DATA_SIZE = ABSOLUTE(ipl3_DATA_END - ipl3_DATA_START);
    }
    __romPos += SIZEOF(.ipl3);
    ipl3_ROM_END = __romPos;
    ipl3_VRAM_END = .;

    boot_ROM_START = __romPos;
    boot_VRAM = ADDR(.boot);
    /* SUBALIGN(4): override input-section alignment so boot.o and init_merged.o
     * concatenate without padding gaps.  boot.o text ends at 0x8004B498
     * (4-byte aligned), so init_merged.o text starts exactly there. */
    .boot 0x8004B400 : AT(boot_ROM_START) SUBALIGN(4)
    {
        FILL(0x00000000);
        boot_TEXT_START = .;
        build/asm/boot/boot.o(.text);
        build/asm/boot/init.o(.text);
        . = ALIGN(., 16);
        boot_TEXT_END = .;
        boot_TEXT_SIZE = ABSOLUTE(boot_TEXT_END - boot_TEXT_START);
        boot_DATA_START = .;
        /* boot_pad.o omitted: its content (0x74680200) is already the last
         * word of boot.o .text; inserting it again here would shift the
         * compressed_main blob by 4 bytes relative to the base ROM. */
        build/asm/boot/boot.o(.data);
        build/asm/boot/init.o(.data);
        build/assets/boot/compressed_main.o(.data);
        build/assets/boot/overlay_dest.o(.data);
        . = ALIGN(., 16);
        boot_DATA_END = .;
        boot_DATA_SIZE = ABSOLUTE(boot_DATA_END - boot_DATA_START);
        boot_RODATA_START = .;
        build/asm/boot/boot.o(.rodata);
        build/asm/boot/init.o(.rodata);
        . = ALIGN(., 16);
        boot_RODATA_END = .;
        boot_RODATA_SIZE = ABSOLUTE(boot_RODATA_END - boot_RODATA_START);
    }
    boot_bss_VRAM = ADDR(.boot_bss);
    .boot_bss (NOLOAD) : SUBALIGN(16)
    {
        FILL(0x00000000);
        boot_BSS_START = .;
        build/asm/boot/boot.o(.bss);
        build/asm/boot/init.o(.bss);
        . = ALIGN(., 16);
        boot_BSS_END = .;
        boot_BSS_SIZE = ABSOLUTE(boot_BSS_END - boot_BSS_START);
    }
    __romPos += SIZEOF(.boot);
    __romPos = ALIGN(__romPos, 16);
    . = ALIGN(., 16);
    boot_ROM_END = __romPos;
    boot_VRAM_END = .;

    assets_ROM_START = __romPos;
    assets_VRAM = ADDR(.assets);
    .assets 0x101000 : AT(assets_ROM_START) SUBALIGN(16)
    {
        FILL(0x00000000);
        assets_DATA_START = .;
        build/assets/assets.o(.data);
        assets_DATA_END = .;
        assets_DATA_SIZE = ABSOLUTE(assets_DATA_END - assets_DATA_START);
    }
    __romPos += SIZEOF(.assets);
    assets_ROM_END = __romPos;
    assets_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
