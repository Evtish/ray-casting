#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include "calc.h"
#include "vec2.h"
#include "dda.h"
#include "drawer.h"
#include "controls.h"
#include "benchmark.h"

#define BENCHMARK true // true - print time spent rendering one frame (SDL3 only)

int main(void) {
    Vec2 player_pos = {11.0, 11.0};
    Vec2 player_dir = {0.0, 1.0}; // must be normalized
    Vec2 camera_plane = {0.67, 0.0};

    double frame_time_sec = 0;

    graphics_init();
    while (program_is_running) {
        #ifdef USE_SDL3
            sdl_check_events();
        #endif
        controls_all(frame_time_sec * 1000, &player_pos, &player_dir, &camera_plane);

        #if BENCHMARK && defined USE_SDL3 
            frame_time_sec = benchmark_render(drawer_render_frame, &player_pos, &player_dir, &camera_plane);
            printf("Time spent: %.3lf ms\n", frame_time_sec * 1000);
        #else
            drawer_render_frame(&player_pos, &player_dir, &camera_plane);
        #endif

        graphics_refresh();
    }
    graphics_quit();

    return 0;
}
