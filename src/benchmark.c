#include "benchmark.h"

// returns time, seconds
double benchmark_render(
    void (*render_func)(
        const Vec2 *const player_pos,
        const Vec2 *const player_dir,
        const Vec2 *const camera_plane
    ),
    const Vec2 *const player_pos,
    const Vec2 *const player_dir,
    const Vec2 *const camera_plane
) {
    clock_t start = clock();
    render_func(player_pos, player_dir, camera_plane);
    return (clock() - start) / (double) CLOCKS_PER_SEC;
}
