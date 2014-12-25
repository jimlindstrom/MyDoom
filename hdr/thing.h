#ifndef __THING_H
#define __THING_H

#include <stdint.h>

#include "vertex.h"
#include "thing_definitions.h"
#include "projector.h"
#include "sector.h"
#include "camera.h"
#include "clipped_segment_projections.h"
#include "sprites.h"
#include "thing_projection.h"
#include "thing_instance.h"

class subsector; // forward declaration

class thing
{
public:
  thing() { }
  thing(thing_instance const *instance);
  ~thing();

  vertex const *get_map_position(void) const { return &map_position; }
  float get_facing_angle(void) const { return facing_angle; }
  uint16_t get_thing_type(void) const { return thing_type; }

  bool is_deaf(void) const { return _is_deaf; }

  void set_subsector(subsector const *ss) { _subsector = ss; }
  subsector const *get_subsector(void) const { return _subsector; }
  sector const *get_sector(void) const;
  thing_definition const *get_definition(void) const { return defn; }
  uint8_t get_frame_idx(void) const;

  void render_player_view(camera const *_camera, clipped_segment_projections *clipped_seg_projs) const;

  virtual void tick(void);

protected:
  vertex map_position;
  float facing_angle;
  uint16_t thing_type;
  bool _is_deaf;

  thing_definition const *defn;

  sprite_animation *animation;
  uint16_t frame_ctr;

  subsector const *_subsector;

  thing_projection *project(camera const *_camera) const;
  sprite const *get_cur_sprite(thing_projection const *proj) const;
};

#endif
