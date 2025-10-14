#pragma once

#include <time.h>
#include <stdio.h>

#include "vec2.h"

double benchmark_render(
    void (*render_func)(
        const Vec2 *const player_pos,
        const Vec2 *const player_dir,
        const Vec2 *const camera_plane
    ),
    const Vec2 *const player_pos,
    const Vec2 *const player_dir,
    const Vec2 *const camera_plane
);
