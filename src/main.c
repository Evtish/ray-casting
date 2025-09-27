#include <locale.h>
#include <stdbool.h>
#include <stdio.h>

#include "calc.h"
#include "linear_algebra.h"
#include "dda.h"
#include "drawer.h"
#include "controls.h"

int main(void) {
    setlocale(LC_ALL, "");

    initscr();
    cbreak();
    noecho();
    intrflush(stdscr, false);
    keypad(stdscr, true);

    if (has_colors()) {
        start_color();
        set_color_pairs();
    }

    Vec2 player_pos = {11.0, 11.0};
    Vec2 player_dir = {0.0, 1.0};
    Vec2 camera_plane = {0.67, 0.0};
    Vec2 ray_dir, delta_dist, side_dist;
    DVec2 ray_map_box, step_dir;
    double screen_pos_x, wall_dist;
    HitSide hit_wall_side;
    int line_height, wall_color_pair;
    char wall_shape;

    while (true) {
        for (int i = 0; i <= CLI_W; i++) {
            screen_pos_x = fmap(i, 0, CLI_W, -1, 1);
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
            hit_wall_side = dda_hit_wall_side(&side_dist, &delta_dist, &ray_map_box, &step_dir);
            if (hit_wall_side != NONE)
                wall_dist = dda_measure_wall_dist(hit_wall_side, side_dist, delta_dist, player_dir, ray_dir);
            else
                continue;
            
            line_height = drawer_get_line_height(wall_dist);
            wall_shape = drawer_get_wall_shape(wall_dist, hit_wall_side);
            wall_color_pair = drawer_get_wall_color_pair(ray_map_box);
            drawer_draw_centered_line(line_height, i, wall_shape, wall_color_pair);
        }
        controls_all(&player_pos, &player_dir, &camera_plane);

        // int ch = getch();
        // switch (getch()) {
        //     case KEY_UP:
        //         printw("getmaxx: %d, getmaxy: %d\n", getmaxx(stdscr), getmaxy(stdscr));
        //     break;
        // }

        clear(); // FIX THIS!!!
        refresh();
    }
    
    endwin();

    return 0;
}
