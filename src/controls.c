#include "controls.h"

#ifndef M_PI
    #define M_PI  3.14159265358979323846 /* pi */
#endif

#ifndef M_PI_2
    #define M_PI_2 1.57079632679489661923 /* pi/2 */
#endif

#define WALK_STEP 0.1 // in map boxes
#define WALK_DELTA 0.01 // in map boxes
#define TURN_STEP M_PI / 60 // in radians

#ifdef USE_NCURSES
    #define KEY_ALT_RIGHT 567
    #define KEY_ALT_LEFT 552
    #define KEY_SUP 337
    #define KEY_SDOWN 336
    #define KEY_LOWERCASE_F 102
    #define KEY_UPPERCASE_F 70
    #define KEY_LOWERCASE_Q 113
    #define KEY_UPPERCASE_Q 81
#endif

// [cos    sin]
// [-sin   cos]
#define ROTATION_MATRIX(a) (Mat22) { \
    (Vec2) {cos(a), -sin(a)}, \
    (Vec2) {sin(a), cos(a)} \
}

bool program_is_running = true;

#ifdef USE_SDL3
    bool key_states[SDL_SCANCODE_COUNT];

    void key_states_clear(void) {
        memset(key_states, false, SDL_SCANCODE_COUNT * sizeof(bool));
    }

    void sdl_check_events(void) {
        key_states_clear();
        while (SDL_PollEvent(&sdl_event)) {
            switch (sdl_event.type) {
                case SDL_EVENT_QUIT: program_is_running = false; break;
                case SDL_EVENT_KEY_DOWN: key_states[sdl_event.key.scancode] = true; break;
            }
        }
    }
#endif

// USE DDA!!!
// void keep_in_bounds(Vec2 *const p_pos, Vec2 *const p_new_pos) {
//     DVec2 new_map_box = (DVec2) {p_new_pos->x, p_new_pos->y};
//     float delta_y;

//     if (new_map_box.x > MAP_W || new_map_box.y > MAP_H) {
//         *p_new_pos = vec2_limit(*p_new_pos, (Vec2) {0, 0}, (Vec2) {MAP_W, MAP_H});
//         new_map_box = (DVec2) {p_new_pos->x, p_new_pos->y};
//     }

//     if (world_map[new_map_box.x][new_map_box.y] != 0) {
//         delta_y = p_new_pos->y - new_map_box.y;
//         // if (new_pos.y == 1)
//         //     p_new_pos->y = map_box.y - WALK_DELTA;
//         // else if (new_pos.y == -1)
//         //     p_new_pos->y = map_box.y + 1 + WALK_DELTA;
//         // else if (new_pos.x == 1)
//         //     p_new_pos->x = map_box.x - WALK_DELTA;
//         // else if (new_pos.x == -1)
//         //     p_new_pos->x = map_box.x + 1 + WALK_DELTA;
//     }
// }

void controls_all(Vec2 *const p_pos, Vec2 *const p_dir, Vec2 *const p_camera_plane) {
    Vec2 new_pos = *p_pos;
    // DVec2 new_map_box,
    DVec2 normalized_dir = vec2_normalize(*p_dir),
    normalized_right_dir = vec2_normalize(vec2_mult_matrix(*p_dir, ROTATION_MATRIX(M_PI_2))),
    normalized_left_dir = vec2_normalize(vec2_mult_matrix(*p_dir, ROTATION_MATRIX(3 * M_PI_2)));

    #ifdef USE_SDL3
        if (key_states[SDL_SCANCODE_ESCAPE])
            program_is_running = false;
        if (key_states[SDL_SCANCODE_F])
            use_euclidian_dist = !use_euclidian_dist;
        if (key_states[SDL_SCANCODE_UP])
            new_pos = vec2_add(*p_pos, dvec2_mult_n(normalized_dir, WALK_STEP));
        if (key_states[SDL_SCANCODE_DOWN])
            new_pos = vec2_add(*p_pos, dvec2_mult_n(normalized_dir, -WALK_STEP));
        if (key_states[SDL_SCANCODE_RIGHT]) {
            *p_dir = vec2_mult_matrix(*p_dir, ROTATION_MATRIX(TURN_STEP));
            *p_camera_plane = vec2_mult_matrix(*p_camera_plane, ROTATION_MATRIX(TURN_STEP));
        }
        if (key_states[SDL_SCANCODE_LEFT]) {
            *p_dir = vec2_mult_matrix(*p_dir, ROTATION_MATRIX(-TURN_STEP));
            *p_camera_plane = vec2_mult_matrix(*p_camera_plane, ROTATION_MATRIX(-TURN_STEP));
        }

    #elif defined USE_NCURSES
        switch (getch()) {
            //quit
            case KEY_LOWERCASE_Q:
            case KEY_UPPERCASE_Q:
                program_is_running = false;
                break;

            //fisheye
            case KEY_LOWERCASE_F:
            case KEY_UPPERCASE_F:
                use_euclidian_dist = !use_euclidian_dist;
                break;

            // walk
            case KEY_UP:
                new_pos = vec2_add(*p_pos, dvec2_mult_n(normalized_dir, WALK_STEP));
                // *p_pos = vec2_add(*p_pos, delta_pos);
                break;
            case KEY_DOWN:
                new_pos = vec2_add(*p_pos, dvec2_mult_n(normalized_dir, -WALK_STEP));
                // *p_pos = vec2_add(*p_pos, delta_pos);
                break;
            case KEY_SUP:
                new_pos = vec2_add(*p_pos, dvec2_mult_n(normalized_dir, 2 * WALK_STEP));
                // *p_pos = vec2_add(*p_pos, delta_pos);
                break;
            case KEY_SDOWN:
                new_pos = vec2_add(*p_pos, dvec2_mult_n(normalized_dir, -2 * WALK_STEP));
                // *p_pos = vec2_add(*p_pos, delta_pos);
                break;
            
            //strafe
            case KEY_ALT_RIGHT:
                new_pos = vec2_add(*p_pos, dvec2_mult_n(normalized_right_dir, WALK_STEP));
                // *p_pos = vec2_add(*p_pos, delta_pos);
                break;
            case KEY_ALT_LEFT:
                new_pos = vec2_add(*p_pos, dvec2_mult_n(normalized_left_dir, WALK_STEP));
                // *p_pos = vec2_add(*p_pos, delta_pos);
                break;

            //turn
            case KEY_RIGHT:
                *p_dir = vec2_mult_matrix(*p_dir, ROTATION_MATRIX(TURN_STEP));
                *p_camera_plane = vec2_mult_matrix(*p_camera_plane, ROTATION_MATRIX(TURN_STEP));
                break;
            case KEY_LEFT:
                *p_dir = vec2_mult_matrix(*p_dir, ROTATION_MATRIX(-TURN_STEP));
                *p_camera_plane = vec2_mult_matrix(*p_camera_plane, ROTATION_MATRIX(-TURN_STEP));
                break;
            case KEY_SRIGHT:
                *p_dir = vec2_mult_matrix(*p_dir, ROTATION_MATRIX(2 * TURN_STEP));
                *p_camera_plane = vec2_mult_matrix(*p_camera_plane, ROTATION_MATRIX(2 * TURN_STEP));
                break;
            case KEY_SLEFT:
                *p_dir = vec2_mult_matrix(*p_dir, ROTATION_MATRIX(-2 * TURN_STEP));
                *p_camera_plane = vec2_mult_matrix(*p_camera_plane, ROTATION_MATRIX(-2 * TURN_STEP));
                break;
        }
    #endif

    *p_pos = vec2_limit(new_pos, (Vec2) {0, 0}, (Vec2) {MAP_W, MAP_H}); // FIX!!!
    // CREATE A COLLISION CHECK!!!
}
