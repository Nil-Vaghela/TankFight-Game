#ifndef BN_SPRITE_ITEMS_TANK_PLAYER_FINAL_H
#define BN_SPRITE_ITEMS_TANK_PLAYER_FINAL_H

#include "bn_sprite_item.h"

//{{BLOCK(tank_player_final_bn_gfx)

//======================================================================
//
//	tank_player_final_bn_gfx, 32x32@8, 
//	+ palette 176 entries, not compressed
//	+ 16 tiles not compressed
//	Total size: 352 + 1024 = 1376
//
//	Time-stamp: 2024-12-01, 02:07:14
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TANK_PLAYER_FINAL_BN_GFX_H
#define GRIT_TANK_PLAYER_FINAL_BN_GFX_H

#define tank_player_final_bn_gfxTilesLen 1024
extern const bn::tile tank_player_final_bn_gfxTiles[32];

#define tank_player_final_bn_gfxPalLen 352
extern const bn::color tank_player_final_bn_gfxPal[176];

#endif // GRIT_TANK_PLAYER_FINAL_BN_GFX_H

//}}BLOCK(tank_player_final_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item tank_player_final(sprite_shape_size(sprite_shape::SQUARE, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(tank_player_final_bn_gfxTiles, 32), bpp_mode::BPP_8, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(tank_player_final_bn_gfxPal, 176), bpp_mode::BPP_8, compression_type::NONE));
}

#endif

