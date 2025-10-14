#pragma once

#include <string.h>

#include "graphics_lib.h"
#include "calc.h"
#include "dda.h"
#include "vec2.h"

#if defined USE_NCURSES
    void drawer_set_color_pairs(void);
#endif

void drawer_render_frame(
    const Vec2 *const player_pos,
    const Vec2 *const player_dir,
    const Vec2 *const camera_plane
);
