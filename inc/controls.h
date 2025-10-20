#pragma once

#include <math.h>
#include <stdio.h>

#include "graphics_lib.h"
#include "vec2.h"
#include "mat22.h"
#include "calc.h"
#include "drawer.h"
#include "dda.h"

extern bool program_is_running;

#ifdef USE_SDL3
    // extern bool *key_states;

    void sdl_check_events(void);
#endif

void controls_all(
    const double frame_time,
    Vec2 *const p_pos,
    Vec2 *const p_dir,
    Vec2 *const p_camera_plane
);
