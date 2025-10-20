#include "drawer.h"

#define H_SCALING_RATIO 0.8
#define MAX_DIST_THRESHOLD (int) (hypotenuse(MAP_H, MAP_W) * 0.5)

#ifdef USE_SDL3
    #define MIN_COLOR_VAL 0
    #define MAX_COLOR_VAL 255

    typedef enum {
        SKY_R = 85, SKY_G = 170, SKY_B = 255,
        GROUND_R = 35, GROUND_G = 0, GROUND_B = 0
    } SkyGroundColor;

    void drawer_get_color_rgba(
        unsigned char color[4],
        const DVec2 map_box,
        const double dist,
        const HitSide hit_side
    ) {
        unsigned char colors_rgba[][4] = {
            {255, 255, 255, SDL_ALPHA_OPAQUE}, // white
            {0, 170, 0, SDL_ALPHA_OPAQUE}, // green
            {0, 85, 255, SDL_ALPHA_OPAQUE}, // blue
            {170, 0, 255, SDL_ALPHA_OPAQUE}, // purple
            {170, 0, 0, SDL_ALPHA_OPAQUE} // red
        };
        int idx = world_map[map_box.x][map_box.y] - 1,
        alpha = SDL_ALPHA_OPAQUE - fmap(dist, 0, MAX_DIST_THRESHOLD, 0, SDL_ALPHA_OPAQUE * 0.8); // the farther the darker

        if (hit_side == HORIZONTAL)
            alpha /= 1.2;

        memcpy(color, colors_rgba[idx], sizeof colors_rgba[idx][0] * 3);
        color[3] = alpha;
    }

    void drawer_draw_centered_line(const int height, const int window_x, const unsigned char color[4]) {
        int offset = (WINDOW_H - height) / 2;
        int start = limit(offset, 0, WINDOW_H), end = limit(WINDOW_H - offset, 0, WINDOW_H);
        
        SDL_SetRenderDrawBlendMode(sdl_renderer, SDL_BLENDMODE_BLEND);
        // sky
        SDL_SetRenderDrawColor(sdl_renderer, SKY_R, SKY_G, SKY_B, SDL_ALPHA_OPAQUE);
        SDL_RenderLine(sdl_renderer, window_x, 0, window_x, start - 1);
        // wall
        SDL_SetRenderDrawColor(sdl_renderer, color[0], color[1], color[2], color[3]);
        SDL_RenderLine(sdl_renderer, window_x, start, window_x, end);
        // ground
        SDL_SetRenderDrawColor(sdl_renderer, GROUND_R, GROUND_G, GROUND_B, SDL_ALPHA_OPAQUE);
        SDL_RenderLine(sdl_renderer, window_x, end + 1, window_x, WINDOW_H);
    }

    void drawer_correct_gamma(unsigned char color[4]) {
        double r = fmap(color[0], MIN_COLOR_VAL, MAX_COLOR_VAL, 0, 1);
        double g = fmap(color[1], MIN_COLOR_VAL, MAX_COLOR_VAL, 0, 1);
        double b = fmap(color[2], MIN_COLOR_VAL, MAX_COLOR_VAL, 0, 1);

        double corr_r = correct_gamma(r);
        double corr_g = correct_gamma(g);
        double corr_b = correct_gamma(b);

        color[0] = fmap(corr_r, 0, 1, MIN_COLOR_VAL, MAX_COLOR_VAL);
        color[1] = fmap(corr_g, 0, 1, MIN_COLOR_VAL, MAX_COLOR_VAL);
        color[2] = fmap(corr_b, 0, 1, MIN_COLOR_VAL, MAX_COLOR_VAL);
    }
    
#elif defined USE_NCURSES
    #define DESKTOP_ENV 1 // 0 - KDE Plasma, 1 - Gnome
    #define SHAPE_SIDE_SHIFT 2

    void drawer_set_color_pairs(void) {
        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_BLUE, COLOR_BLACK);
        init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(5, COLOR_RED, COLOR_BLACK);
    }

    char drawer_get_wall_shape(const double dist, const HitSide hit_side) {
        #if DESKTOP_ENV == 0
            char shapes[] = {'#', '@', '0', '$', '&', '?', '%'};
        #elif DESKTOP_ENV == 1
            char shapes[] = {'$', '%', '#', '&', '0', '?'};
        #endif
        int amount_of_shapes = arr_len(shapes);

        int shape_index = fmap(dist, 0, MAX_DIST_THRESHOLD, 0, amount_of_shapes - SHAPE_SIDE_SHIFT - 1);
        if (hit_side == HORIZONTAL && shape_index < amount_of_shapes)
            shape_index += SHAPE_SIDE_SHIFT;

        return shapes[shape_index];
    }

    int drawer_get_wall_color_pair(const DVec2 map_box) {
        return COLOR_PAIR(world_map[map_box.x][map_box.y]);
    }

    void drawer_draw_centered_line(
        const int height,
        const int cli_x,
        const char shape,
        const int color_pair
    ) {
        int offset = (WINDOW_H - height) / 2;
        int start = limit(offset, 0, WINDOW_H), end = limit(WINDOW_H - offset, 0, WINDOW_H);

        for (int i = 0; i < WINDOW_H; i++) {
            // sky
            if (i < start) {
                mvaddch(i, cli_x, ' ');
            }
            // ground
            else if (i > end) {
                if (has_colors()) attron(0);
                mvaddch(i, cli_x, '.');
            }
            // wall
            else {
                if (has_colors()) attron(color_pair);
                mvaddch(i, cli_x, shape);
            }
            if (has_colors()) attroff(color_pair);
        }
    }
#endif

int drawer_get_line_height(const double wall_dist) {
    return H_SCALING_RATIO * WINDOW_H / wall_dist;
}

void drawer_render_frame(
    const Vec2 *const player_pos,
    const Vec2 *const player_dir,
    const Vec2 *const camera_plane
) {
    Vec2 ray_dir, delta_dist, side_dist;
    DVec2 ray_map_box, step_dir;
    double screen_pos_x, wall_dist;
    HitSide wall_side;
    int line_height;

    #ifdef USE_SDL3
        unsigned char wall_color[4];
    #elif defined USE_NCURSES
        char wall_shape;
        int wall_color;
    #endif
    
    for (int i = 0; i <= WINDOW_W; i++) {
        screen_pos_x = fmap(i, 0, WINDOW_W, -1, 1);
        ray_dir = vec2_add(*player_dir, vec2_mult_n(*camera_plane, screen_pos_x));

        // MAYBE ADD step_dir ONE TIME RIGHT NOW
        ray_map_box = (DVec2) {player_pos->x, player_pos->y};
        step_dir = vec2_quantize(ray_dir);

        delta_dist = (Vec2) {
            fabs(prevent_zero_div(1, ray_dir.x, ALMOST_INF)),
            fabs(prevent_zero_div(1, ray_dir.y, ALMOST_INF))
        };
        // the first x- and y-intersection *distances*
        side_dist = (Vec2) {
            dda_side_dist_component(ray_dir.x, player_pos->x, ray_map_box.x, delta_dist.x),
            dda_side_dist_component(ray_dir.y, player_pos->y, ray_map_box.y, delta_dist.y)
        };
        
        // DDA algorythm
        wall_side = dda_hit_wall_side(&side_dist, &delta_dist, &ray_map_box, &step_dir);
        if (wall_side != NONE)
            wall_dist = dda_measure_wall_dist(wall_side, side_dist, delta_dist, *player_dir, ray_dir);
        else
            continue;
        
        line_height = drawer_get_line_height(wall_dist);
        #ifdef USE_SDL3
            drawer_get_color_rgba(wall_color, ray_map_box, wall_dist, wall_side);
            drawer_correct_gamma(wall_color);
            drawer_draw_centered_line(line_height, i, wall_color);
        #elif defined USE_NCURSES
            wall_shape = drawer_get_wall_shape(wall_dist, wall_side);
            wall_color = drawer_get_wall_color_pair(ray_map_box);
            drawer_draw_centered_line(line_height, i, wall_shape, wall_color);
        #endif
    }
}
