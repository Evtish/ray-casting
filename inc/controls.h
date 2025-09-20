#pragma once

#include <math.h>
#include <ncurses.h>

#include "linear_algebra.h"
#include "calc.h"
#include "drawer.h"
#include "dda.h"

void controls_all(Vec2 *const p_pos, Vec2 *const p_dir, Vec2 *const p_camera_plane);