#pragma once

#include <ncurses.h>

#include "calc.h"
#include "dda.h"
#include "linear_algebra.h"

#define CLI_W getmaxx(stdscr) //173//236
#define CLI_H getmaxy(stdscr) //41//64
// #define FONT_W 8//11
// #define FONT_H 15//27

void set_color_pairs(void);
int drawer_get_line_height(const double wall_dist);
char drawer_get_wall_shape(const double dist, const HitSide hit_side);
int drawer_get_wall_color_pair(const DVec2 map_box);
void drawer_draw_centered_line(
    const int height_sb,
    const int cli_x,
    const char shape,
    const int color_pair
);