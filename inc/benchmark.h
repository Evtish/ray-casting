#pragma once

#include <time.h>
#include <stdio.h>

#include "linear_algebra.h"

double benchmark_render(
    void (*render_func)(
        const Vec2 player_pos, const Vec2 player_dir, const Vec2 camera_plane
    ), const Vec2 player_pos, const Vec2 player_dir, const Vec2 camera_plane
);
