#include "weapon.h"
#include "sprites.h"
#include "games.h"

weapon::weapon(char const *sprite_name_up,
               char const *sprite_name_down,
               char const *sprite_name_ready,
               char const *sprite_name_attack,
               char const *sprite_name_flash)
{
  state = WEAPON_STATE_READY;

  sprite_up     = sprites_lookup_animation(sprite_name_up);
  sprite_down   = sprites_lookup_animation(sprite_name_down);
  sprite_ready  = sprites_lookup_animation(sprite_name_ready);
  sprite_attack = sprites_lookup_animation(sprite_name_attack);
  sprite_flash  = sprites_lookup_animation(sprite_name_flash);
  if(!sprite_up    ) { printf("ERROR: couldn't find sprite \"%s\"\n", sprite_name_up); exit(0); }
  if(!sprite_down  ) { printf("ERROR: couldn't find sprite \"%s\"\n", sprite_name_down); exit(0); }
  if(!sprite_ready ) { printf("ERROR: couldn't find sprite \"%s\"\n", sprite_name_ready); exit(0); }
  if(!sprite_attack) { printf("ERROR: couldn't find sprite \"%s\"\n", sprite_name_attack); exit(0); }
  if(!sprite_flash ) { printf("ERROR: couldn't find sprite \"%s\"\n", sprite_name_flash); exit(0); }
}

sprite const *weapon::get_cur_sprite(void) const
{
  switch(state)
  {
    case WEAPON_STATE_UP:	return sprite_up    ->get_frame(0)->get_sprite(0); break;
    case WEAPON_STATE_DOWN:	return sprite_down  ->get_frame(0)->get_sprite(0); break;
    case WEAPON_STATE_READY:	return sprite_ready ->get_frame(0)->get_sprite(0); break;
    case WEAPON_STATE_ATTACK:	return sprite_attack->get_frame(0)->get_sprite(0); break;
    case WEAPON_STATE_FLASH:	return sprite_flash ->get_frame(0)->get_sprite(0); break;
  }
  return NULL;
}

void weapon::draw(void) const
{
  sprite const *spr = get_cur_sprite();

  int16_t h=games_get_screen_height();
  int16_t w=games_get_screen_width();
  float scale = w / 320.0;

  int16_t x = w/2 - (scale*spr->get_width())/2.0;
  int16_t y = (h-1) - (scale*spr->get_height());

  spr->draw(x, y, scale);
}
