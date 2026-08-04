build/xg2.elf: \
    build/asm/header.o \
    build/assets/ipl3.o \
    build/asm/boot/boot.o \
    build/assets/boot/boot_pad.o \
    build/asm/boot/init.o \
    build/assets/boot/compressed_main.o \
    build/assets/boot/overlay_dest.o \
    build/assets/assets.o
build/asm/header.o:
build/assets/ipl3.o:
build/asm/boot/boot.o:
build/assets/boot/boot_pad.o:
build/asm/boot/init.o:
build/assets/boot/compressed_main.o:
build/assets/boot/overlay_dest.o:
build/assets/assets.o:
-include build/asm/header.d build/assets/ipl3.d build/asm/boot/boot.d build/assets/boot/boot_pad.d build/asm/boot/init.d build/assets/boot/compressed_main.d build/assets/boot/overlay_dest.d build/assets/assets.d
