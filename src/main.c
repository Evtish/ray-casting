#include <stdbool.h>
#include <stdio.h>

#include "calc.h"
#include "linear_algebra.h"
#include "dda.h"
#include "drawer.h"
#include "controls.h"
#include "benchmark.h"

int main(void) {
    Vec2 player_pos = {11.0, 11.0};
    Vec2 player_dir = {0.0, 1.0};
    Vec2 camera_plane = {0.67, 0.0};

    #if defined USE_SDL3 || USE_NCURSES
        graphics_init();
        while (program_is_running) {
            graphics_refresh();

            double time_passed = benchmark_render(drawer_render_frame, player_pos, player_dir, camera_plane);
            // printf("Time passed: %lf seconds\n", time_passed);

            #ifdef USE_SDL3
                sdl_check_events();
            #endif
            controls_all(&player_pos, &player_dir, &camera_plane);
        }
        graphics_quit();
    #endif

    return 0;
}
