#include <stdbool.h>
#include <stdio.h>

#include "calc.h"
#include "linear_algebra.h"
#include "dda.h"
#include "drawer.h"
#include "controls.h"

int main(void) {
    graphics_init();

    Vec2 player_pos = {11.0, 11.0};
    Vec2 player_dir = {0.0, 1.0};
    Vec2 camera_plane = {0.67, 0.0};
    Vec2 ray_dir, delta_dist, side_dist;
    DVec2 ray_map_box, step_dir;
    double screen_pos_x, wall_dist;
    HitSide wall_side;
    int line_height;
    // int* wall_color;
    #ifdef USE_SDL3
        int wall_color[4];
    #elif defined USE_NCURSES
        char wall_shape;
        int wall_color;
    #endif

    while (program_is_running) {
        graphics_refresh();

        for (int i = 0; i <= WINDOW_W; i++) {
            screen_pos_x = fmap(i, 0, WINDOW_W, -1, 1);
            ray_dir = vec2_add(player_dir, vec2_mult_n(camera_plane, screen_pos_x));

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
            
            // DDA algorythm
            wall_side = dda_hit_wall_side(&side_dist, &delta_dist, &ray_map_box, &step_dir);
            if (wall_side != NONE)
                wall_dist = dda_measure_wall_dist(wall_side, side_dist, delta_dist, player_dir, ray_dir);
            else
                continue;
            
            line_height = drawer_get_line_height(wall_dist);
            #ifdef USE_SDL3
                drawer_get_color_rgba(wall_color, ray_map_box, wall_dist, wall_side);
                drawer_draw_centered_line(line_height, i, wall_color);
            #elif defined USE_NCURSES
                wall_shape = drawer_get_wall_shape(wall_dist, wall_side);
                wall_color = drawer_get_wall_color_pair(ray_map_box);
                drawer_draw_centered_line(line_height, i, wall_shape, wall_color);
            #endif
        }
        // int ch = getch();
        // printw("%d\n", ch);

        #ifdef USE_SDL3
            sdl_check_events();
        #endif
        controls_all(&player_pos, &player_dir, &camera_plane);
    }
    graphics_quit();

    return 0;
}
