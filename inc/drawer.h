#pragma once

// #include <ncurses.h>
#include <string.h>

#include "graphic_lib.h"
#include "calc.h"
#include "dda.h"
#include "linear_algebra.h"

#ifdef USE_SDL3
    #include <stdio.h>

    void drawer_get_color_rgba(
        int color[4],
        const DVec2 map_box,
        const double dist,
        const HitSide hit_side
    );
    void drawer_draw_centered_line(const int height_sb, const int window_x, const int color_rgba[4]);
#elif defined USE_NCURSES
    // #define FONT_W 8//11
    // #define FONT_H 15//27

    void drawer_set_color_pairs(void);
    char drawer_get_wall_shape(const double dist, const HitSide hit_side);
    int drawer_get_wall_color_pair(const DVec2 map_box);
    void drawer_draw_centered_line(
        const int height_sb,
        const int cli_x,
        const char shape,
        const int color_pair
    );
#endif
int drawer_get_line_height(const double wall_dist);