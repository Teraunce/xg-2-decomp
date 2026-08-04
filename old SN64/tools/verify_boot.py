"""
Verify boot.s + init.s byte-match against the ROM by manually applying
MIPS ELF relocations to the assembled .text sections.
"""
import struct

def parse_elf(obj_path):
    with open(obj_path, 'rb') as f:
        data = f.read()
    e_shoff      = struct.unpack_from('>I', data, 0x20)[0]
    e_shentsize  = struct.unpack_from('>H', data, 0x2e)[0]
    e_shnum      = struct.unpack_from('>H', data, 0x30)[0]
    e_shstrndx   = struct.unpack_from('>H', data, 0x32)[0]
    sections = []
    for i in range(e_shnum):
        off = e_shoff + i * e_shentsize
        # sh_name(0) sh_type(1) sh_flags(2) sh_addr(3) sh_offset(4) sh_size(5)
        # sh_link(6) sh_info(7) sh_addralign(8) sh_entsize(9)
        sh = struct.unpack_from('>IIIIIIIIII', data, off)
        sections.append(sh)
    shstr_off = sections[e_shstrndx][4]
    def sname(sh):
        noff = shstr_off + sh[0]
        return data[noff:data.index(b'\x00', noff)].decode()
    return data, sections, sname

def get_text_bytes(obj_path):
    data, sections, sname = parse_elf(obj_path)
    for sh in sections:
        if sname(sh) == '.text':
            return bytearray(data[sh[4]:sh[4]+sh[5]])
    raise KeyError('.text not found')

def get_symbols(obj_path):
    data, sections, sname = parse_elf(obj_path)
    sym_sh = strtab_sh = None
    for sh in sections:
        n = sname(sh)
        if n == '.symtab': sym_sh = sh
        if n == '.strtab': strtab_sh = sh
    if not sym_sh:
        return {}
    strtab_off = strtab_sh[4]
    sym_size   = sym_sh[9]  # sh_entsize
    syms = {}
    for i in range(sym_sh[5] // sym_size):
        off = sym_sh[4] + i * sym_size
        st_name, st_value = struct.unpack_from('>II', data, off)
        noff = strtab_off + st_name
        name = data[noff:data.index(b'\x00', noff)].decode()
        if name:
            syms[name] = st_value
    return syms

def apply_mips_relocs(obj_path, section_name, vma_base, ext_syms):
    data, sections, sname = parse_elf(obj_path)

    # Find target section
    text_sh = None
    for sh in sections:
        if sname(sh) == section_name:
            text_sh = sh
            break
    text = bytearray(data[text_sh[4]:text_sh[4]+text_sh[5]])

    # Find .rel.text (sh_type == 9 = SHT_REL)
    rel_sh = None
    for sh in sections:
        n = sname(sh)
        if n in (f'.rel{section_name}', f'.rela{section_name}',
                 '.rel.text', '.rela.text'):
            if sh[1] in (9, 4):  # sh_type: 9=REL, 4=RELA
                rel_sh = sh
                break

    if not rel_sh:
        print("  WARNING: no relocation section found")
        return bytes(text)

    # Find .symtab and .strtab
    sym_sh = strtab_sh = None
    for sh in sections:
        n = sname(sh)
        if n == '.symtab': sym_sh = sh
        if n == '.strtab': strtab_sh = sh

    strtab_off = strtab_sh[4]
    sym_size   = sym_sh[9]

    # Build local symbol table
    local_syms = {}
    n_syms = sym_sh[5] // sym_size
    for i in range(n_syms):
        off = sym_sh[4] + i * sym_size
        st_name, st_value = struct.unpack_from('>II', data, off)
        noff = strtab_off + st_name
        name = data[noff:data.index(b'\x00', noff)].decode()
        local_syms[i] = (name, st_value)

    all_syms = {name: val for name, val in local_syms.values() if name}
    all_syms.update(ext_syms)

    # Apply relocations
    is_rela = rel_sh[1] == 4
    ent_size = rel_sh[9]  # sh_entsize
    n_rels = rel_sh[5] // ent_size
    applied = 0
    skipped = []

    for i in range(n_rels):
        off = rel_sh[4] + i * ent_size
        r_off, r_info = struct.unpack_from('>II', data, off)
        r_addend = struct.unpack_from('>i', data, off+8)[0] if is_rela else 0
        r_sym_idx = r_info >> 8
        r_type    = r_info & 0xFF

        sym_name, sym_val = local_syms.get(r_sym_idx, ('?', 0))
        # Resolve
        S = all_syms.get(sym_name, 0) if sym_name in all_syms else sym_val
        if S == 0:
            skipped.append((r_off, r_type, sym_name))
            continue

        if r_off >= len(text):  # PDR reloc or out-of-range
            continue

        word = struct.unpack_from('>I', text, r_off)[0]

        if   r_type == 4:   # R_MIPS_26 (jal)
            word = (word & 0xFC000000) | ((S >> 2) & 0x03FFFFFF)
        elif r_type == 5:   # R_MIPS_HI16 (MIPS spike: add 0x8000 for sign-ext compensation)
            hi_adj = (S + 0x8000) >> 16
            word = (word & 0xFFFF0000) | (hi_adj & 0xFFFF)
        elif r_type == 6:   # R_MIPS_LO16
            word = (word & 0xFFFF0000) | (S & 0xFFFF)
        elif r_type == 10:  # R_MIPS_PC16 (branch)
            pc = vma_base + r_off + 4
            word = (word & 0xFFFF0000) | (((S - pc) >> 2) & 0xFFFF)
        elif r_type == 2:   # R_MIPS_32
            word = S
        else:
            skipped.append((r_off, r_type, sym_name))
            continue

        struct.pack_into('>I', text, r_off, word)
        applied += 1

    print(f"  Applied {applied} relocations" + (f", skipped {len(skipped)}: {skipped[:3]}" if skipped else ""))
    return bytes(text)

# ---- Main ----
with open('/tmp/boot_rom.bin', 'rb') as f:
    rom = f.read()

ext = {
    'D_80000400':   0x80000400,
    'D_80001000':   0x80001000,
    'D_8004BA20':   0x8004BA20,
    'D_8024BA20':   0x8024BA20,
    'D_8024BA28':   0x8024BA28,
    'D_2B588':      0x0002B588,
    'func_8004B498': 0x8004B498,
    'func_8004B464': 0x8004B464,
    'func_8004B4F4': 0x8004B4F4,
    'func_8004B5B8': 0x8004B5B8,
    'func_8004B620': 0x8004B620,
}

print("=== boot.s (0x8004B400, 0x98 bytes) ===")
boot = apply_mips_relocs('/tmp/boot.o', '.text', 0x8004B400, ext)[:0x98]
rom_boot = rom[:0x98]
diffs = [(i, rom_boot[i], boot[i]) for i in range(0x98) if boot[i] != rom_boot[i]]
if diffs:
    print(f"  ✗ {len(diffs)} differences:")
    for off, r, b in diffs[:10]: print(f"    0x{off:04x}: ROM=0x{r:02x} BUILT=0x{b:02x}")
else:
    print("  ✓ BYTE-EXACT MATCH")

print()
print("=== init.s (0x8004B498, 0x588 bytes) ===")
init = apply_mips_relocs('/tmp/init.o', '.text', 0x8004B498, ext)[:0x588]
rom_init = rom[0x98:0x98+0x588]
diffs = [(i, rom_init[i], init[i]) for i in range(0x588) if init[i] != rom_init[i]]
if diffs:
    print(f"  ✗ {len(diffs)} differences:")
    for off, r, b in diffs[:10]: print(f"    0x{off:04x}: ROM=0x{r:02x} BUILT=0x{b:02x}")
else:
    print("  ✓ BYTE-EXACT MATCH")
