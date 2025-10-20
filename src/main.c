#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include "calc.h"
#include "vec2.h"
#include "dda.h"
#include "drawer.h"
#include "controls.h"
#include "benchmark.h"

#define BENCHMARK false // true - print time spent rendering one frame (SDL3 only)

int main(void) {
    Vec2 player_pos = {11.0, 11.0};
    Vec2 player_dir = {0.0, 1.0}; // must be normalized
    Vec2 camera_plane = {0.67, 0.0};

    time_t prev_time_clocks = 0;
    double frame_time_s = 0;

    graphics_init();
    while (program_is_running) {
        frame_time_s = (clock() - prev_time_clocks) / (double) CLOCKS_PER_SEC;
        prev_time_clocks = clock();

        drawer_render_frame(&player_pos, &player_dir, &camera_plane);
        #if BENCHMARK && defined USE_SDL3
            printf("Time spent: %.3lf s\n", frame_time_s);
        #endif

        #ifdef USE_SDL3
            sdl_check_events();
        #endif
        controls_all(frame_time_s, &player_pos, &player_dir, &camera_plane);

        graphics_refresh();
    }
    graphics_quit();

    return 0;
}
