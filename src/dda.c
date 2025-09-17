#include "dda.h"

// get intersection *distance* based on current player coordinate
double dda_side_dist_component(
    const double ray_dir_coord,
    const double player_pos_coord,
    const int ray_map_box_coord,
    const double delta_dist_coord
) {
    if (ray_dir_coord < 0)
        return (player_pos_coord - ray_map_box_coord) * delta_dist_coord;
    else
        return (ray_map_box_coord + 1.0 - player_pos_coord) * delta_dist_coord;
}

HitSide dda_hit_wall_side(
    Vec2 *const p_side_dist,
    Vec2 *const p_delta_dist,
    DVec2 *const p_ray_map_box,
    DVec2 *const p_step_dir
) {
    HitSide side_type = NONE;
    while (
        p_ray_map_box->x + p_step_dir->x >= 0 &&
        p_ray_map_box->x + p_step_dir->x <= MAP_W &&
        p_ray_map_box->y + p_step_dir->y >= 0 &&
        p_ray_map_box->y + p_step_dir->y <= MAP_H
    ) {
        // jump to the nearest map square side
        if (p_side_dist->x < p_side_dist->y) {
            p_side_dist->x += p_delta_dist->x;
            p_ray_map_box->x += p_step_dir->x;
            side_type = VERTICAL;
        }
        else {
            p_side_dist->y += p_delta_dist->y;
            p_ray_map_box->y += p_step_dir->y;
            side_type = HORIZONTAL;
        }
        // check if ray has hit a wall
        if (world_map[p_ray_map_box->x][p_ray_map_box->y] > 0)
            return side_type;
    }
    return side_type;
}