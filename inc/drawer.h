#pragma once

#include <ncurses.h>

#include "calc.h"
#include "vec2.h"

#define MAP_W 24
#define MAP_H 24
#define CLI_W 236
#define CLI_H 64
// #define FONT_W 8//11
// #define FONT_H 15//27

extern int world_map[MAP_H][MAP_W];

char drawer_get_color(const DVec2 map_box);
int drawer_get_line_height(const double wall_dist);
void drawer_centered_line(const int height_sb, const int cli_x, char color);