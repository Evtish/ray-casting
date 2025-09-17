#include <locale.h>
#include <stdbool.h>
#include <stdio.h>

#include "calc.h"
#include "vec2.h"
#include "dda.h"
#include "drawing.h"

int main(void) {
    setlocale(LC_ALL, "");

    initscr();

    Vec2 player_pos = {11.0, 11.0};
    Vec2 player_dir = {0.0, -1.0};
    Vec2 camera_plane = {1.0, -1.0};
    Vec2 ray_dir, delta_dist, side_dist;
    DVec2 ray_map_box, step_dir;
    double screen_pos_x, perp_wall_dist;
    HitSide hit_wall_side_type;
    int line_height; // in symbols of CLI

    while (true) {
        for (int i = 0; i <= CLI_W; i++) {
            screen_pos_x = fmap(i, 0, CLI_W, -1.0, 1.0);
            ray_dir = vec2_add(player_dir, vec2_scalar_mult_n(camera_plane, screen_pos_x));

            // MAYBE ADD step_dir ONE TIME RIGHT NOW
            ray_map_box = (DVec2) {player_pos.x, player_pos.y};
            step_dir = vec2_normalize(ray_dir);

            delta_dist = (Vec2) {
                fabs(prevent_zero_div(1, ray_dir.x, ALMOST_INF)),
                fabs(prevent_zero_div(1, ray_dir.y, ALMOST_INF))
            };
            // the first x- and y-intersection *distances*
            side_dist = (Vec2) {
                dda_side_dist_component(ray_dir.x, player_pos.x, ray_map_box.x, delta_dist.x),
                dda_side_dist_component(ray_dir.y, player_pos.y, ray_map_box.y, delta_dist.y)
            };

            // if (ray_dir.x < 0) side_dist.x = (player_pos.x - ray_map_box.x) * delta_dist.x;
            // else side_dist.x = (ray_map_box.x + 1.0 - player_pos.x) * delta_dist.x;
            // if (ray_dir.y < 0) side_dist.y = (player_pos.y - ray_map_box.y) * delta_dist.y;
            // else side_dist.y = (ray_map_box.y + 1.0 - player_pos.y) * delta_dist.y;

            // printf("side_dist.x = %lf, side_dist.y = %lf\n", side_dist.x, side_dist.y);
            // printf("step_dir.x = %d, step_dir.y = %d\n", step_dir.x, step_dir.y);
            
            // DDA algorythm
            hit_wall_side_type = dda_hit_wall_side(&side_dist, &delta_dist, &ray_map_box, &step_dir);
            // printf("hit_wall_side_type = %d (0 - VERTICAL, 1 - HORIZONTAL)\n", hit_wall_side_type);

            if (hit_wall_side_type == VERTICAL)
                perp_wall_dist = side_dist.x - delta_dist.x;
            else if (hit_wall_side_type == HORIZONTAL)
                perp_wall_dist = side_dist.y - delta_dist.y;
            else
                continue;
            
            line_height = 5 * CLI_H / perp_wall_dist;
            char color = draw_get_color(ray_map_box);
            draw_centered_line(line_height, i, color);

        }
        refresh();
    }
    
    endwin();

    return 0;
}
