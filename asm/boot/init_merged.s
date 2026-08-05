.include "asm_macros.inc"

.set noat
.set noreorder
.set gp=64

nonmatching func_8004B498, 0x120

glabel func_8004B498
    /* 1098 8004B498 27BDEFD0 */  addiu      $sp, $sp, -0x1030
    /* 109C 8004B49C 3C03A480 */  lui        $v1, (0xA4800018 >> 16)
    /* 10A0 8004B4A0 34630018 */  ori        $v1, $v1, (0xA4800018 & 0xFFFF)
    /* 10A4 8004B4A4 3C05BFC0 */  lui        $a1, (0xBFC007FC >> 16)
    /* 10A8 8004B4A8 34A507FC */  ori        $a1, $a1, (0xBFC007FC & 0xFFFF)
    /* 10AC 8004B4AC AFBF102C */  sw         $ra, 0x102C($sp)
    /* 10B0 8004B4B0 AFB01028 */  sw         $s0, 0x1028($sp)
  .L8004B4B4:
    /* 10B4 8004B4B4 8C620000 */  lw         $v0, 0x0($v1)
    /* 10B8 8004B4B8 30420003 */  andi       $v0, $v0, 0x3
    /* 10BC 8004B4BC 1440FFFD */  bnez       $v0, .L8004B4B4
    /* 10C0 8004B4C0 00000000 */   nop
    /* 10C4 8004B4C4 8CA40000 */  lw         $a0, 0x0($a1)
  .L8004B4C8:
    /* 10C8 8004B4C8 8C620000 */  lw         $v0, 0x0($v1)
    /* 10CC 8004B4CC 30420003 */  andi       $v0, $v0, 0x3
    /* 10D0 8004B4D0 1440FFFD */  bnez       $v0, .L8004B4C8
    /* 10D4 8004B4D4 34820008 */   ori       $v0, $a0, 0x8
    /* 10D8 8004B4D8 ACA20000 */  sw         $v0, 0x0($a1)
    /* 10DC 8004B4DC 00002821 */  addu       $a1, $zero, $zero
    /* 10E0 8004B4E0 3C060003 */  lui        $a2, %hi(D_2B588)
    /* 10E4 8004B4E4 3C028025 */  lui        $v0, %hi(D_8024BA20)
    /* 10E8 8004B4E8 2444BA20 */  addiu      $a0, $v0, %lo(D_8024BA20)
    /* 10EC 8004B4EC 3C028005 */  lui        $v0, %hi(D_8004BA20)
    /* 10F0 8004B4F0 2443BA20 */  addiu      $v1, $v0, %lo(D_8004BA20)
  alabel func_8004B4F4
    /* 10F4 8004B4F4 24C2B588 */  addiu      $v0, $a2, %lo(D_2B588)
    /* 10F8 8004B4F8 04420001 */  bltzl      $v0, .L8004B500
    /* 10FC 8004B4FC 24420003 */   addiu     $v0, $v0, 0x3
  .L8004B500:
    /* 1100 8004B500 00021083 */  sra        $v0, $v0, 2
    /* 1104 8004B504 00A2102A */  slt        $v0, $a1, $v0
    /* 1108 8004B508 10400007 */  beqz       $v0, .L8004B528
    /* 110C 8004B50C 3C028005 */   lui       $v0, %hi(D_8004BA20)
    /* 1110 8004B510 8C620000 */  lw         $v0, 0x0($v1)
    /* 1114 8004B514 24630004 */  addiu      $v1, $v1, 0x4
    /* 1118 8004B518 24A50001 */  addiu      $a1, $a1, 0x1
    /* 111C 8004B51C AC820000 */  sw         $v0, 0x0($a0)
    /* 1120 8004B520 08012D3D */  j          func_8004B4F4
    /* 1124 8004B524 24840004 */   addiu     $a0, $a0, 0x4
  .L8004B528:
    /* 1128 8004B528 244ABA20 */  addiu      $t2, $v0, %lo(D_8004BA20)
    /* 112C 8004B52C 24040FED */  addiu      $a0, $zero, 0xFED
    /* 1130 8004B530 27A50FFD */  addiu      $a1, $sp, 0xFFD
    /* 1134 8004B534 3C038025 */  lui        $v1, %hi(D_8024BA28)
    /* 1138 8004B538 8C62BA28 */  lw         $v0, %lo(D_8024BA28)($v1)
    /* 113C 8004B53C 2463BA28 */  addiu      $v1, $v1, %lo(D_8024BA28)
    /* 1140 8004B540 2442FFF8 */  addiu      $v0, $v0, -0x8
    /* 1144 8004B544 00433821 */  addu       $a3, $v0, $v1
  .L8004B548:
    /* 1148 8004B548 A0A00000 */  sb         $zero, 0x0($a1)
    /* 114C 8004B54C 2484FFFF */  addiu      $a0, $a0, -0x1
    /* 1150 8004B550 0481FFFD */  bgez       $a0, .L8004B548
    /* 1154 8004B554 24A5FFFF */   addiu     $a1, $a1, -0x1
    /* 1158 8004B558 8C6B0008 */  lw         $t3, 0x8($v1)
    /* 115C 8004B55C 00006021 */  addu       $t4, $zero, $zero
    /* 1160 8004B560 19600031 */  blez       $t3, .L8004B628
    /* 1164 8004B564 24050FEE */   addiu     $a1, $zero, 0xFEE
    /* 1168 8004B568 27AD0010 */  addiu      $t5, $sp, 0x10
    /* 116C 8004B56C 000C6043 */  sra        $t4, $t4, 1
  .L8004B570:
    /* 1170 8004B570 31820100 */  andi       $v0, $t4, 0x100
    /* 1174 8004B574 14400005 */  bnez       $v0, .L8004B58C
    /* 1178 8004B578 31820001 */   andi      $v0, $t4, 0x1
    /* 117C 8004B57C 90E40000 */  lbu        $a0, 0x0($a3)
    /* 1180 8004B580 24E70001 */  addiu      $a3, $a3, 0x1
    /* 1184 8004B584 348CFF00 */  ori        $t4, $a0, 0xFF00
    /* 1188 8004B588 31820001 */  andi       $v0, $t4, 0x1
  .L8004B58C:
    /* 118C 8004B58C 1040000A */  beqz       $v0, func_8004B5B8
    /* 1190 8004B590 01A51021 */   addu      $v0, $t5, $a1
    /* 1194 8004B594 90E40000 */  lbu        $a0, 0x0($a3)
    /* 1198 8004B598 24E70001 */  addiu      $a3, $a3, 0x1
    /* 119C 8004B59C 24A50001 */  addiu      $a1, $a1, 0x1
    /* 11A0 8004B5A0 30A50FFF */  andi       $a1, $a1, 0xFFF
    /* 11A4 8004B5A4 256BFFFF */  addiu      $t3, $t3, -0x1
    /* 11A8 8004B5A8 A0440000 */  sb         $a0, 0x0($v0)
    /* 11AC 8004B5AC A1440000 */  sb         $a0, 0x0($t2)
    /* 11B0 8004B5B0 08012D88 */  j          func_8004B620
    /* 11B4 8004B5B4 254A0001 */   addiu     $t2, $t2, 0x1


  alabel func_8004B5B8
    /* 11B8 8004B5B8 90E90000 */  lbu        $t1, 0x0($a3)
    /* 11BC 8004B5BC 24E70001 */  addiu      $a3, $a3, 0x1
    /* 11C0 8004B5C0 90E80000 */  lbu        $t0, 0x0($a3)
    /* 11C4 8004B5C4 00003021 */  addu       $a2, $zero, $zero
    /* 11C8 8004B5C8 310200F0 */  andi       $v0, $t0, 0xF0
    /* 11CC 8004B5CC 00021100 */  sll        $v0, $v0, 4
    /* 11D0 8004B5D0 01224825 */  or         $t1, $t1, $v0
    /* 11D4 8004B5D4 3102000F */  andi       $v0, $t0, 0xF
    /* 11D8 8004B5D8 24480002 */  addiu      $t0, $v0, 0x2
    /* 11DC 8004B5DC 0106102A */  slt        $v0, $t0, $a2
    /* 11E0 8004B5E0 1440000F */  bnez       $v0, func_8004B620
    /* 11E4 8004B5E4 24E70001 */   addiu     $a3, $a3, 0x1
  .L8004B5E8:
    /* 11E8 8004B5E8 01A51021 */  addu       $v0, $t5, $a1
    /* 11EC 8004B5EC 24A50001 */  addiu      $a1, $a1, 0x1
    /* 11F0 8004B5F0 30A50FFF */  andi       $a1, $a1, 0xFFF
    /* 11F4 8004B5F4 256BFFFF */  addiu      $t3, $t3, -0x1
    /* 11F8 8004B5F8 01261821 */  addu       $v1, $t1, $a2
    /* 11FC 8004B5FC 30630FFF */  andi       $v1, $v1, 0xFFF
    /* 1200 8004B600 01A31821 */  addu       $v1, $t5, $v1
    /* 1204 8004B604 90640000 */  lbu        $a0, 0x0($v1)
    /* 1208 8004B608 24C60001 */  addiu      $a2, $a2, 0x1
    /* 120C 8004B60C A0440000 */  sb         $a0, 0x0($v0)
    /* 1210 8004B610 A1440000 */  sb         $a0, 0x0($t2)
    /* 1214 8004B614 0106102A */  slt        $v0, $t0, $a2
    /* 1218 8004B618 1040FFF3 */  beqz       $v0, .L8004B5E8
    /* 121C 8004B61C 254A0001 */   addiu     $t2, $t2, 0x1
  alabel func_8004B620
    /* 1220 8004B620 1D60FFD3 */  bgtz       $t3, .L8004B570
    /* 1224 8004B624 000C6043 */   sra       $t4, $t4, 1
  .L8004B628:
    /* 1228 8004B628 3C108005 */  lui        $s0, %hi(D_8004BA20)
    /* 122C 8004B62C 0C012D19 */  jal        func_8004B464
    /* 1230 8004B630 2610BA20 */   addiu     $s0, $s0, %lo(D_8004BA20)
    /* 1234 8004B634 0200F809 */  jalr       $s0
    /* 1238 8004B638 00000000 */   nop
    /* 123C 8004B63C 8FBF102C */  lw         $ra, 0x102C($sp)
    /* 1240 8004B640 8FB01028 */  lw         $s0, 0x1028($sp)
    /* 1244 8004B644 03E00008 */  jr         $ra
    /* 1248 8004B648 27BD1030 */   addiu     $sp, $sp, 0x1030
endlabel func_8004B5B8
