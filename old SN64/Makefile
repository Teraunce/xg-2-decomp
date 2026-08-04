### xg2 Decomp Makefile ###

# Use bash so verify/match_check rules can use process substitution <(...)
SHELL := /bin/bash

# --- Toolchain paths (absolute, sandbox-stable) ---
TOOLS_DIR   := $(shell cd .. && pwd)/tools
IDO_DIR     := $(TOOLS_DIR)/ido
MIPS_DIR    := $(TOOLS_DIR)/mips-binutils

AS          := $(MIPS_DIR)/bin/mips-linux-gnu-as
LD          := $(MIPS_DIR)/bin/mips-linux-gnu-ld
OBJCOPY     := $(MIPS_DIR)/bin/mips-linux-gnu-objcopy
OBJDUMP     := $(MIPS_DIR)/bin/mips-linux-gnu-objdump
PYTHON      := python3
TRIM_TOOL   := $(TOOLS_DIR)/trim_ido.py

# IDO shared-lib wrapper so tools load without LD_LIBRARY_PATH in env
export LD_LIBRARY_PATH := $(MIPS_DIR)/lib:$(LD_LIBRARY_PATH)

# --- Compiler selection ---
# XG2 was compiled with SN Systems SN64 (GCC 2.7.2 Cygnus SN64.X).
# Evidence: jr ra with addiu sp in delay slot (not IDO 7.1 style),
#           ra saved at frame-8 for single-ra functions (tight packing),
#           andi directly into result register (not via temp reg like decompals IDO 5.3).
#
# tools/sn64/gcc is the SN64 binary (32-bit x86), requires
# IA32 emulation support to run. On a host with 32-bit support:
#   make CC_VER=sn64 match_check FUNC=func_XXXXXXXX
#
# Fallback IDO 7.1 (tools/ido/) and IDO 5.3 (tools/ido53/) are available
# for compilation testing but neither produces byte-matching output.
CC_VER      ?= ido71
ifeq ($(CC_VER),sn64)
  CC        := $(TOOLS_DIR)/sn64/gcc
  CFLAGS    := -O2 -mips2 -G0 -I include
  TRIM_TOOL := $(TOOLS_DIR)/trim_ido.py
else ifeq ($(CC_VER),ido53)
  CC        := $(TOOLS_DIR)/ido53/cc
  CFLAGS    := -O2 -mips2 -G0 -Wab,-r4300_mul -non_shared -Xcpluscomm \
               -woff 649,838,712 -signed -I include
  TRIM_TOOL := $(TOOLS_DIR)/trim_ido.py
else
  CC        := $(TOOLS_DIR)/ido/cc
  CFLAGS    := -O2 -mips2 -G0 -Wab,-r4300_mul -non_shared -Xcpluscomm \
               -woff 649,838,712 -signed -I include
  TRIM_TOOL := $(TOOLS_DIR)/trim_ido.py
endif
# GNU as: big-endian MIPS I/II (vr4300), o32 ABI, no GP-relative, no section padding
ASFLAGS     := -march=vr4300 -mabi=32 -G0 -EB -no-pad-sections
# Main-block linker flags (separate from the full ROM link)
MAIN_LDFLAGS := -T xg2_main.ld --no-check-sections
LDFLAGS     := -T xg2.ld -Map build/xg2.map --no-check-sections
OBJCOPYFLAGS:= -O binary

# --- Paths ---
BUILD_DIR   := build
ASM_DIR     := asm
SRC_DIR     := src
ASSET_DIR   := assets

BASEROM     := baserom.z64
TARGET      := $(BUILD_DIR)/xg2.z64
ELF         := $(BUILD_DIR)/xg2.elf

# --- ASM exclusion lists ---
# entry.s spans the full boot+init block; boot.s + init.s cover the same range
# individually.  init_merged.s was a workaround stub — it lacks the embedded
# D_8004B64C data table that init.s carries in its .text section, causing ROM
# content divergence.  Use init.s (macro.inc-based, complete) instead.
ASM_BOOT_EXCLUDE := \
    $(ASM_DIR)/boot/entry.s \
    $(ASM_DIR)/boot/init_merged.s

# func_8007BD08_merged.s grouped 3 functions but func_8007BD08 and func_8007C0F4
# have been decompiled to C; func_8007BE58 now has its own stub. Drop the merged file.
# func_80087D28.s contains func_80087D78 inline; func_8008E458.s contains func_8008E4A8.
# Exclude the individual stubs that would duplicate symbols from those container files.
ASM_MERGED_EXCLUDE := \
    $(ASM_DIR)/main/main/func_8007BD08_merged.s \
    $(ASM_DIR)/main/main/func_80087D78.s \
    $(ASM_DIR)/main/main/func_8008E4A8.s

# Collect all source files, removing excluded stubs
ASM_SOURCES  := $(filter-out $(ASM_BOOT_EXCLUDE) $(ASM_MERGED_EXCLUDE), \
                $(shell find $(ASM_DIR) -name '*.s' | sort))

# Exclude src/boot/ — those C files are reference/documentation only;
# the linker uses build/asm/boot/*.o from the assembled asm stubs instead.
C_SOURCES    := $(shell find $(SRC_DIR) -name '*.c' -not -path '$(SRC_DIR)/boot/*' | sort)
ASSET_BINS   := $(shell find $(ASSET_DIR) -name '*.bin' | sort)

ASM_OBJECTS  := $(patsubst $(ASM_DIR)/%.s,   $(BUILD_DIR)/asm/%.o,    $(ASM_SOURCES))
C_OBJECTS    := $(patsubst $(SRC_DIR)/%.c,   $(BUILD_DIR)/src/%.o,    $(C_SOURCES))

# Exclude ASM stubs for functions that have been matched to C.
# Each matched .c produces a .o in build/src/; the corresponding
# asm/main/main/*.o would be a duplicate — drop it from ASM_OBJECTS.
C_FUNC_BASES    := $(basename $(notdir $(C_SOURCES)))
MATCHED_ASM_OBJ := $(foreach f,$(C_FUNC_BASES),$(BUILD_DIR)/asm/main/main/$(f).o)
ASM_OBJECTS     := $(filter-out $(MATCHED_ASM_OBJ),$(ASM_OBJECTS))

ASSET_OBJECTS:= $(patsubst $(ASSET_DIR)/%.bin, $(BUILD_DIR)/assets/%.o, $(ASSET_BINS))

ALL_OBJECTS  := $(ASM_OBJECTS) $(C_OBJECTS) $(ASSET_OBJECTS)

# Main-block objects (assembled into build/main/asm/…, linked via xg2_main.ld)
MAIN_ASM_SOURCES := $(shell find $(ASM_DIR)/main/main -name '*.s' | sort)
MAIN_ASM_OBJECTS := $(patsubst $(ASM_DIR)/main/main/%.s, \
                     $(BUILD_DIR)/main/asm/main/main/%.s.o, \
                     $(MAIN_ASM_SOURCES))

MAIN_ELF := $(BUILD_DIR)/main/xg2_main.elf
MAIN_BIN := $(BUILD_DIR)/main/xg2_main.bin
MAIN_REF := $(ASSET_DIR)/boot/decompressed_main.bin

.PHONY: all clean verify setup main_elf verify_main

all: $(TARGET)

# Link
$(ELF): $(ALL_OBJECTS) xg2.ld
	$(LD) $(LDFLAGS) -o $@ $(ALL_OBJECTS)

# Convert ELF -> raw binary ROM
$(TARGET): $(ELF)
	$(OBJCOPY) $(OBJCOPYFLAGS) $< $@
	@echo "Built $(TARGET)"

# Compile C (SN64/IDO), trim trailing .text padding the compiler adds.
# Expected .text size comes from the matching .s stub in asm/main/main/.
# Intermediate padded object goes to .c.padded.o; trimmed final is .c.o
$(BUILD_DIR)/main/src/main/main/%.c.o: $(SRC_DIR)/main/main/%.c \
                                        $(ASM_DIR)/main/main/%.s
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@.padded $<
	$(PYTHON) $(TRIM_TOOL) $@.padded $@ $(ASM_DIR)/main/main/$*.s
	@rm -f $@.padded 2>/dev/null || true

# Compile C (generic, for non-main-block files)
$(BUILD_DIR)/src/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# Assemble .s files (main block — with -no-pad-sections)
$(BUILD_DIR)/main/asm/main/main/%.s.o: $(ASM_DIR)/main/main/%.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -I include -o $@ $<

# Assemble .s files (generic)
$(BUILD_DIR)/asm/%.o: $(ASM_DIR)/%.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -I include -o $@ $<

# Binary assets -> .o (wrapped in a .data section)
$(BUILD_DIR)/assets/%.o: $(ASSET_DIR)/%.bin
	@mkdir -p $(dir $@)
	$(OBJCOPY) -I binary -O elf32-tradbigmips -B mips \
		--rename-section .data=.data $< $@

# Byte-match verification: compare only the relevant ROM slice, not full ROM
# (since we're building the decompressed main block, not the full z64 yet)
verify: $(TARGET)
	@echo "Comparing $(TARGET) with $(BASEROM)..."
	@sha1sum $(BASEROM) $(TARGET)
	@cmp $(BASEROM) $(TARGET) && echo "✓ BYTE-EXACT MATCH" || \
		(echo "✗ MISMATCH"; diff <(xxd $(BASEROM)) <(xxd $(TARGET)) | head -40; exit 1)

# ---- Main-block link & verify ----

# Link all main-block asm stubs (and any already-matched C objects listed in xg2_main.ld)
# Objects are referenced by path inside the linker script; we just need them built first.
$(MAIN_ELF): $(MAIN_ASM_OBJECTS) xg2_main.ld xg2_main.syms.ld
	@mkdir -p $(dir $@)
	$(LD) $(MAIN_LDFLAGS) -o $@

# Strip to raw binary (only .main section)
$(MAIN_BIN): $(MAIN_ELF)
	$(OBJCOPY) -O binary --only-section=.main $< $@

main_elf: $(MAIN_BIN)
	@echo "Main block: $(MAIN_BIN)"

# Byte-compare linked main block against decompressed ROM reference
verify_main: $(MAIN_BIN)
	@echo "Comparing $(MAIN_BIN) vs $(MAIN_REF) ..."
	@cmp $(MAIN_BIN) $(MAIN_REF) && echo "✓ MAIN BLOCK BYTE-EXACT MATCH" || \
		(echo "✗ MISMATCH (first diff):"; \
		 cmp -l $(MAIN_BIN) $(MAIN_REF) | \
		   awk '{printf "  offset 0x%x: got %03o  want %03o\n", $$1-1, $$2, $$3}' | head -20; \
		 exit 1)

# ---- Single-function match check ----
# Usage: make match_check FUNC=func_8004D138
# Compiles src/main/main/$(FUNC).c via trim_ido, then byte-compares .text
# against the assembled asm stub.
match_check:
	@test -n "$(FUNC)" || (echo "Usage: make match_check FUNC=func_XXXXXXXX"; exit 1)
	@echo "=== $(FUNC) ==="
	@$(MAKE) -s $(BUILD_DIR)/main/src/main/main/$(FUNC).c.o 2>&1 | grep -v "^make" || true
	@$(MAKE) -s $(BUILD_DIR)/main/asm/main/main/$(FUNC).s.o 2>&1 | grep -v "^make" || true
	@$(OBJCOPY) -O binary -j .text $(BUILD_DIR)/main/src/main/main/$(FUNC).c.o /tmp/$(FUNC).c.text
	@$(OBJCOPY) -O binary -j .text $(BUILD_DIR)/main/asm/main/main/$(FUNC).s.o /tmp/$(FUNC).s.text
	@cmp /tmp/$(FUNC).c.text /tmp/$(FUNC).s.text && \
		echo "✓ MATCH" || \
		(echo "✗ MISMATCH"; \
		 diff <(xxd /tmp/$(FUNC).c.text) <(xxd /tmp/$(FUNC).s.text) | head -30)

# Compile just one C file for quick IDO smoke test
# Usage: make test_ido SRC=src/boot/boot.c
test_ido:
	$(CC) $(CFLAGS) -c -o /tmp/test_ido.o $(SRC)
	$(OBJDUMP) -d /tmp/test_ido.o | head -60

clean:
	rm -rf $(BUILD_DIR)

setup:
	@echo "Checking toolchain..."
	@test -x $(AS)      || (echo "ERROR: $(AS) not found";      exit 1)
	@test -x $(LD)      || (echo "ERROR: $(LD) not found";      exit 1)
	@test -x $(OBJCOPY) || (echo "ERROR: $(OBJCOPY) not found"; exit 1)
	@test -x $(CC)      || (echo "ERROR: $(CC) not found";      exit 1)
	@echo "Toolchain OK"
	@mkdir -p $(BUILD_DIR)/asm/boot $(BUILD_DIR)/src/boot $(BUILD_DIR)/assets/boot

# Re-split ROM with splat
split:
	splat split xg2.yaml
