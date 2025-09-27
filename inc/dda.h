#pragma once

#include <stdbool.h>

#include "linear_algebra.h"
// #include "calc.h"
#include "map.h"

extern bool use_euclidian_dist;

typedef enum {
    VERTICAL,
    HORIZONTAL,
    NONE
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

double dda_measure_wall_dist(
    const HitSide hit_wall_side,
    const Vec2 side_dist,
    const Vec2 delta_dist,
    const Vec2 player_dir,
    const Vec2 ray_dir
);