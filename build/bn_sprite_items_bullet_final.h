#ifndef BN_SPRITE_ITEMS_BULLET_FINAL_H
#define BN_SPRITE_ITEMS_BULLET_FINAL_H

#include "bn_sprite_item.h"

//{{BLOCK(bullet_final_bn_gfx)

//======================================================================
//
//	bullet_final_bn_gfx, 8x8@8, 
//	+ palette 32 entries, not compressed
//	+ 1 tiles not compressed
//	Total size: 64 + 64 = 128
//
//	Time-stamp: 2024-12-01, 02:07:14
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BULLET_FINAL_BN_GFX_H
#define GRIT_BULLET_FINAL_BN_GFX_H

#define bullet_final_bn_gfxTilesLen 64
extern const bn::tile bullet_final_bn_gfxTiles[2];

#define bullet_final_bn_gfxPalLen 64
extern const bn::color bullet_final_bn_gfxPal[32];

#endif // GRIT_BULLET_FINAL_BN_GFX_H

//}}BLOCK(bullet_final_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item bullet_final(sprite_shape_size(sprite_shape::SQUARE, sprite_size::SMALL), 
            sprite_tiles_item(span<const tile>(bullet_final_bn_gfxTiles, 2), bpp_mode::BPP_8, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(bullet_final_bn_gfxPal, 32), bpp_mode::BPP_8, compression_type::NONE));
}

#endif

