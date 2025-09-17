#pragma once

#include <stdbool.h>

#include "vec2.h"
#include "draw.h"

typedef enum {
    VERTICAL,
    HORIZONTAL
} HitSide;

double dda_side_dist_component(
    const double ray_dir_coord,
    const double player_pos_coord,
    const int ray_map_box_coord,
    const double delta_dist_coord
);

HitSide dda_hit_wall_side(
    Vec2 *const p_side_dist,
    Vec2 *const p_delta_dist,
    DVec2 *const p_ray_map_box,
    DVec2 *const p_step_dir
);