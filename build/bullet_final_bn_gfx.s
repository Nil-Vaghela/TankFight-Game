
@{{BLOCK(bullet_final_bn_gfx)

@=======================================================================
@
@	bullet_final_bn_gfx, 8x8@8, 
@	+ palette 32 entries, not compressed
@	+ 1 tiles not compressed
@	Total size: 64 + 64 = 128
@
@	Time-stamp: 2024-12-01, 02:07:14
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global bullet_final_bn_gfxTiles		@ 64 unsigned chars
	.hidden bullet_final_bn_gfxTiles
bullet_final_bn_gfxTiles:
	.word 0x000D100F,0x00000019,0x1B1A100F,0x00171700,0x1C000000,0x1100000E,0x12050019,0x00111412
	.word 0x0B080600,0x09161815,0x0A070400,0x080C1411,0x06040200,0x06070707,0x02020100,0x01040403

	.section .rodata
	.align	2
	.global bullet_final_bn_gfxPal		@ 64 unsigned chars
	.hidden bullet_final_bn_gfxPal
bullet_final_bn_gfxPal:
	.hword 0x0000,0x0000,0x1084,0x14A5,0x18C6,0x24E6,0x2108,0x294A
	.hword 0x318C,0x35AD,0x35CE,0x3DCE,0x3DEF,0x2815,0x3339,0x377F
	.hword 0x3B7F,0x4210,0x4231,0x4631,0x4631,0x4A52,0x4E73,0x56B5
	.hword 0x5AD6,0x56BF,0x431B,0x433A,0x4B5D,0x0000,0x0000,0x0000

@}}BLOCK(bullet_final_bn_gfx)
