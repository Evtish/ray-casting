#include "drawer.h"

#define H_SCALING_RATIO 1.0
#define MAX_DIST_THRESHOLD 15

char shapes[] = {'@', '%', '#', 'O', '&', 'a', 'o', ':', ',', '.'};
// char shapes[] = {'@', 'O'};

void set_color_pairs(void) {
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(5, COLOR_RED, COLOR_BLACK);
}

int drawer_get_line_height(const double wall_dist) {
    return H_SCALING_RATIO * CLI_H / wall_dist;
}

char drawer_get_wall_shape(const double dist, const HitSide hit_side) {
    int shape_index = fmap(dist, 0, MAX_DIST_THRESHOLD, 0, arr_len(shapes) / 2 - 1);
    if (hit_side == HORIZONTAL)
        shape_index += arr_len(shapes) / 2;

    // int shape_index = 0;
    // if (hit_side == VERTICAL)
    //     shape_index = 1;

    return shapes[shape_index];
}

int drawer_get_wall_color_pair(const DVec2 map_box) {
    return COLOR_PAIR(world_map[map_box.x][map_box.y]);
}

void drawer_draw_centered_line(
    const int height_sb,
    const int cli_x,
    const char shape,
    const int color_pair
) {
    int offset = (CLI_H - height_sb) / 2;
    int start = limit(offset, 0, CLI_H), end = limit(CLI_H - offset, 0, CLI_H);
    
    for (int i = start; i < end; i++) {
        if (has_colors()) attron(color_pair);
        mvaddch(i, cli_x, shape);
        if (has_colors()) attroff(color_pair);
    }
}