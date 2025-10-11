#pragma once

#include <math.h>

#include "graphic_lib.h"
#include "linear_algebra.h"
#include "calc.h"
#include "drawer.h"
#include "dda.h"

extern bool program_is_running;

#ifdef USE_SDL3
    extern bool key_states[SDL_SCANCODE_COUNT];

    void sdl_check_events(void);
#endif

void controls_all(Vec2 *const p_pos, Vec2 *const p_dir, Vec2 *const p_camera_plane);
