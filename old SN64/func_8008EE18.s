	.verstamp	7 10
	.option	pic0
	.text	
	.align	2
	.file	2 "/tmp/func_8008EE18.c"
	.globl	func_8008EE18
	.loc	2 3
 #   1	typedef signed int s32;
 #   2	s32 func_8008EE98(s32, s32, s32);
 #   3	s32 func_8008EE18(s32 arg0, s32 arg1, s32 arg2) {
	.ent	func_8008EE18 2
func_8008EE18:
	.option	O2
	subu	$sp, 24
	sw	$31, 20($sp)
	.mask	0x80000000, -4
	.frame	$sp, 24, $31
	sw	$6, 32($sp)
	.loc	2 3
	.loc	2 4
 #   4	    return func_8008EE98(arg0, arg1, arg2) + arg2;
	lw	$6, 32($sp)
	.livereg	0x0E00000E,0x00000000
	jal	func_8008EE98
	lw	$14, 32($sp)
	addu	$2, $2, $14
	.livereg	0x2000FF0E,0x00000FFF
	lw	$31, 20($sp)
	addu	$sp, 24
	j	$31
	.end	func_8008EE18
