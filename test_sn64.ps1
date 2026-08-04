# test_sn64.ps1
# Run: powershell -ExecutionPolicy Bypass -File test_sn64.ps1
#
# Tests SN64 GCC (gcc-2.7.2-970404) against func_80081B58.
# Files are written to WSL's /tmp/ to avoid NTFS EOVERFLOW in old cpp.

$sn64Dir = "C:\Users\Teraunce\AppData\Roaming\Claude\local-agent-mode-sessions\06f53cfa-011f-4ff0-8fd6-80a52e23784f\ac2bd788-cf8b-4f87-8759-d312ecb49aac\local_59aa4e2b-bcaa-4387-bfd3-68bc7bb752e6\outputs\tools\sn64"
$gccWin  = $sn64Dir + "\gcc"

if (-not (Test-Path $gccWin)) {
    Write-Host "ERROR: SN64 GCC not found at $gccWin" -ForegroundColor Red
    exit 1
}

function wslpath($p) {
    $drive = $p.Substring(0,1).ToLower()
    $rest  = $p.Substring(2).Replace('\','/')
    return "/mnt/$drive$rest"
}

$gccWsl     = wslpath $gccWin
$sn64DirWsl = wslpath $sn64Dir

# Source lives entirely on WSL Linux fs (/tmp/) to avoid 32-bit stat EOVERFLOW on NTFS
$srcLinux = "/tmp/xg2sn64.c"
$outLinux = "/tmp/xg2sn64.s"

# Test C source — 1-arg prototype (func_80081730 confirmed 1-arg leaf)
$c = @'
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
'@

# Write source to WSL /tmp/ by piping via stdin
$c | wsl bash -c "cat > $srcLinux"

Write-Host "Testing SN64 GCC (gcc-2.7.2-970404)..." -ForegroundColor Cyan

$variants = @(
    @{ label = "-O2";                   opt = "-O2" },
    @{ label = "-O1";                   opt = "-O1" },
    @{ label = "-O2 -fno-caller-saves"; opt = "-O2 -fno-caller-saves" },
    @{ label = "-O2 -mips1";            opt = "-O2 -mips1" }
)

foreach ($v in $variants) {
    Write-Host ""
    Write-Host ("--- " + $v.label + " ---") -ForegroundColor Yellow

    $cmd = "chmod +x '$gccWsl' 2>/dev/null; '$gccWsl' -B'$sn64DirWsl/' " + $v.opt + " -mips2 -G0 -fno-pic -mno-abicalls -S $srcLinux -o $outLinux 2>&1"
    $err = wsl bash -c $cmd
    if ($err) { Write-Host $err -ForegroundColor DarkYellow }

    $asmLines = wsl bash -c "cat $outLinux 2>/dev/null"
    if ($asmLines) {
        Write-Host "-- full asm --"
        $asmLines | Where-Object { $_ -notmatch "^\s*#" -and $_.Trim() -ne "" }
    } else {
        Write-Host "  (no output)" -ForegroundColor Red
    }
}

Write-Host ""
Write-Host "=== Reference (func_80081B58) ===" -ForegroundColor Cyan
Write-Host "  subu  sp, sp, 24      (frame=0x18)"
Write-Host "  sw    ra, 20(sp)      (ra at frame-4)"
Write-Host "  NO sw s0/s1 saves"
Write-Host "  or    t0, a1, zero    (hold arg1 in t0 across jal)"
Write-Host "  jal   func_80081730"
Write-Host "  sw    v0, 0(t0)       (use t0 as saved a1 after jal)"
