### Extreme-G 2 Decomp Makefile — IDO build ###

SHELL := /bin/bash

# ---------------------------------------------------------------------------
# Toolchain
# ---------------------------------------------------------------------------
# Relative paths avoid shell-tokenisation issues with spaces in the project path.
# LD_LIBRARY_PATH is set by make directly (not shell-tokenised), so CURDIR is safe there.
TOOLS_DIR := tools
MIPS_DIR  := $(TOOLS_DIR)/mips-binutils

AS      := $(MIPS_DIR)/bin/mips-linux-gnu-as
LD      := $(MIPS_DIR)/bin/mips-linux-gnu-ld
OBJCOPY := $(MIPS_DIR)/bin/mips-linux-gnu-objcopy
OBJDUMP := $(MIPS_DIR)/bin/mips-linux-gnu-objdump
PYTHON  := python3

# IDO 7.1 — only supported compiler for this project
CC      := $(TOOLS_DIR)/ido/cc
CFLAGS  := -O2 -mips2 -G0 -Wab,-r4300_mul -non_shared -Xcpluscomm \
            -woff 649,838,712 -signed -I include

# Absolute path for LD_LIBRARY_PATH (make sets env vars directly — spaces OK here)
export LD_LIBRARY_PATH := $(CURDIR)/$(MIPS_DIR)/lib:$(LD_LIBRARY_PATH)

# GNU as: big-endian VR4300, o32 ABI, no GP-relative, no padding between sections
ASFLAGS := -march=vr4300 -mabi=32 -G0 -EB -no-pad-sections

LDFLAGS      := -T xg2.ld      -Map build/xg2.map --no-check-sections
MAIN_LDFLAGS := -T xg2_main.ld --no-check-sections
OBJCOPYFLAGS := -O binary

# ---------------------------------------------------------------------------
# Paths
# ---------------------------------------------------------------------------
BUILD_DIR := build
ASM_DIR   := asm
SRC_DIR   := src
ASSET_DIR := assets
BASEROM   := baserom.z64
TARGET    := $(BUILD_DIR)/xg2.z64
ELF       := $(BUILD_DIR)/xg2.elf

# ---------------------------------------------------------------------------
# ROM build source lists
# The full ROM (xg2.ld) uses: header + boot asm + compressed_main blob + assets.
# Main block C/asm stubs are NOT linked into the ROM — the main block is the
# original compressed binary (assets/boot/compressed_main.bin), so the ROM
# always matches the reference regardless of decompilation status.
# ---------------------------------------------------------------------------
ASM_BOOT_EXCLUDE := \
    $(ASM_DIR)/boot/entry.s \
    $(ASM_DIR)/boot/init_merged.s

ROM_ASM_SOURCES := $(filter-out $(ASM_BOOT_EXCLUDE), \
                   $(ASM_DIR)/header.s \
                   $(shell find $(ASM_DIR)/boot -name '*.s' | sort))

ROM_ASM_OBJECTS := $(patsubst $(ASM_DIR)/%.s, $(BUILD_DIR)/asm/%.o, $(ROM_ASM_SOURCES))

ASSET_BINS    := $(shell find $(ASSET_DIR) -name '*.bin' | sort)
ASSET_OBJECTS := $(patsubst $(ASSET_DIR)/%.bin, $(BUILD_DIR)/assets/%.o, $(ASSET_BINS))

ROM_OBJECTS := $(ROM_ASM_OBJECTS) $(ASSET_OBJECTS)

# ---------------------------------------------------------------------------
# Main-block asm objects (for verify_main link only)
# ---------------------------------------------------------------------------
ASM_MERGED_EXCLUDE := \
    $(ASM_DIR)/main/main/func_8007BD08_merged.s \
    $(ASM_DIR)/main/main/func_80087D78.s \
    $(ASM_DIR)/main/main/func_8008E4A8.s

MAIN_ASM_SOURCES := $(filter-out $(ASM_MERGED_EXCLUDE), \
                    $(shell find $(ASM_DIR)/main/main -name '*.s' | sort))
MAIN_ASM_OBJECTS := $(patsubst $(ASM_DIR)/main/main/%.s, \
                    $(BUILD_DIR)/main/asm/main/main/%.s.o, \
                    $(MAIN_ASM_SOURCES))

MAIN_ELF := $(BUILD_DIR)/main/xg2_main.elf
MAIN_BIN := $(BUILD_DIR)/main/xg2_main.bin
MAIN_REF := $(ASSET_DIR)/boot/decompressed_main.bin

# ---------------------------------------------------------------------------
# C sources (compile for validation — not linked into ROM)
# ---------------------------------------------------------------------------
C_SOURCES := $(shell find $(SRC_DIR)/main/main -name '*.c' | sort)
C_OBJECTS := $(patsubst $(SRC_DIR)/main/main/%.c, \
             $(BUILD_DIR)/src/main/main/%.o, $(C_SOURCES))

.PHONY: all clean verify verify_main compile_check match_check setup

# ---------------------------------------------------------------------------
# Default: build the ROM (always byte-exact — uses compressed_main.bin)
# ---------------------------------------------------------------------------
all: $(TARGET)

$(ELF): $(ROM_OBJECTS) xg2.ld
	$(LD) $(LDFLAGS) -o $@ $(ROM_OBJECTS)

$(TARGET): $(ELF)
	$(OBJCOPY) $(OBJCOPYFLAGS) $< $@
	@echo "Built $(TARGET)"

verify: $(TARGET)
	@sha1sum $(BASEROM) $(TARGET)
	@cmp $(BASEROM) $(TARGET) && echo "✓ BYTE-EXACT MATCH" || echo "✗ MISMATCH"

# ---------------------------------------------------------------------------
# Compile all C with IDO — error-check only, output not linked into ROM
# Usage: make compile_check   (or: make compile_check -j8 for parallel)
# ---------------------------------------------------------------------------
compile_check: $(C_OBJECTS)
	@echo "All $(words $(C_OBJECTS)) C files compiled successfully."

$(BUILD_DIR)/src/main/main/%.o: $(SRC_DIR)/main/main/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $< 2>&1 | grep -v "^cfe: Warning" || true

# ---------------------------------------------------------------------------
# Assemble rules
# ---------------------------------------------------------------------------
$(BUILD_DIR)/asm/%.o: $(ASM_DIR)/%.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -I include -o $@ $<

$(BUILD_DIR)/main/asm/main/main/%.s.o: $(ASM_DIR)/main/main/%.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -I include -o $@ $<

$(BUILD_DIR)/assets/%.o: $(ASSET_DIR)/%.bin
	@mkdir -p $(dir $@)
	$(OBJCOPY) -I binary -O elf32-tradbigmips -B mips \
		--rename-section .data=.data $< $@

# ---------------------------------------------------------------------------
# Main-block asm-only link + byte-compare (reference verification)
# ---------------------------------------------------------------------------
$(MAIN_ELF): $(MAIN_ASM_OBJECTS) xg2_main.ld xg2_main.syms.ld
	@mkdir -p $(dir $@)
	$(LD) $(MAIN_LDFLAGS) -o $@

$(MAIN_BIN): $(MAIN_ELF)
	$(OBJCOPY) -O binary --only-section=.main $< $@

verify_main: $(MAIN_BIN)
	@echo "Comparing $(MAIN_BIN) vs $(MAIN_REF) ..."
	@cmp $(MAIN_BIN) $(MAIN_REF) && echo "✓ MAIN BLOCK BYTE-EXACT MATCH" || \
		(echo "✗ MISMATCH"; \
		 cmp -l $(MAIN_BIN) $(MAIN_REF) | \
		   awk '{printf "  offset 0x%x: got %03o want %03o\n", $$1-1, $$2, $$3}' | head -20)

# ---------------------------------------------------------------------------
# IDO match check for a single function
# Compares IDO-compiled .text against the assembled asm stub .text
# Usage: make match_check FUNC=func_8007A8E0
# ---------------------------------------------------------------------------
match_check:
	@test -n "$(FUNC)" || (echo "Usage: make match_check FUNC=func_XXXXXXXX"; exit 1)
	@echo "=== $(FUNC) ==="
	@$(CC) $(CFLAGS) -c -o /tmp/$(FUNC).c.o $(SRC_DIR)/main/main/$(FUNC).c 2>&1 \
		| grep -v "^cfe: Warning" || true
	@$(AS) $(ASFLAGS) -I include -o /tmp/$(FUNC).s.o $(ASM_DIR)/main/main/$(FUNC).s 2>/dev/null
	@$(OBJCOPY) -O binary -j .text /tmp/$(FUNC).c.o /tmp/$(FUNC).c.text
	@$(OBJCOPY) -O binary -j .text /tmp/$(FUNC).s.o /tmp/$(FUNC).s.text
	@cmp /tmp/$(FUNC).c.text /tmp/$(FUNC).s.text && echo "✓ MATCH" || \
		(echo "✗ MISMATCH (c=$$(wc -c < /tmp/$(FUNC).c.text) bytes  s=$$(wc -c < /tmp/$(FUNC).s.text) bytes)"; \
		 diff <($(OBJDUMP) -D -b binary -m mips:4300 --endian=big /tmp/$(FUNC).c.text) \
		      <($(OBJDUMP) -D -b binary -m mips:4300 --endian=big /tmp/$(FUNC).s.text) | head -40)

# ---------------------------------------------------------------------------
clean:
	rm -rf $(BUILD_DIR)

setup:
	@echo "Checking toolchain..."
	@test -x $(AS)      || (echo "ERROR: $(AS) not found";      exit 1)
	@test -x $(LD)      || (echo "ERROR: $(LD) not found";      exit 1)
	@test -x $(OBJCOPY) || (echo "ERROR: $(OBJCOPY) not found"; exit 1)
	@test -x $(CC)      || (echo "ERROR: $(CC) not found";      exit 1)
	@echo "Toolchain OK"
	@mkdir -p $(BUILD_DIR)
