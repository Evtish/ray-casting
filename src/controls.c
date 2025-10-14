#include "controls.h"

#ifndef M_PI
    #define M_PI  3.14159265358979323846 /* pi */
#endif

#ifndef M_PI_2
    #define M_PI_2 1.57079632679489661923 /* pi/2 */
#endif

#define FAST_MODE_RATIO 2
#define UNIT_WALK_STEP 0.0001 // in map boxes
#define UNIT_TURN_STEP M_PI / 300 // in radians
// #define WALK_OFFSET 0.01 // in map boxes, a small step back when the player bump into a wall

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
    cos(a),     sin(a), \
    -sin(a),    cos(a) \
}

bool program_is_running = true;

#ifdef USE_SDL3
    static SDL_Event sdl_event;
    static bool key_states[SDL_SCANCODE_COUNT];

    // void key_states_clear(void) {
    //     memset(key_states, false, SDL_SCANCODE_COUNT * sizeof(bool));
    // }

    void sdl_check_events(void) {
        // key_states_clear();
        while (SDL_PollEvent(&sdl_event)) {
            switch (sdl_event.type) {
                case SDL_EVENT_QUIT: program_is_running = false; break;
                case SDL_EVENT_KEY_DOWN: key_states[sdl_event.key.scancode] = true; break;
                case SDL_EVENT_KEY_UP: key_states[sdl_event.key.scancode] = false; break;
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
//         //     p_new_pos->y = map_box.y - WALK_OFFSET;
//         // else if (new_pos.y == -1)
//         //     p_new_pos->y = map_box.y + 1 + WALK_OFFSET;
//         // else if (new_pos.x == 1)
//         //     p_new_pos->x = map_box.x - WALK_OFFSET;
//         // else if (new_pos.x == -1)
//         //     p_new_pos->x = map_box.x + 1 + WALK_OFFSET;
//     }
// }

void controls_all(
    const double frame_time,
    Vec2 *const p_pos,
    Vec2 *const p_dir,
    Vec2 *const p_camera_plane
) {
    // const Vec2 forward_dir = *p_dir,
    //     backward_dir = vec2_mult_n(forward_dir, -1),
    //     right_dir = vec2_mult_matrix(forward_dir, ROTATION_MATRIX(M_PI_2)),
    //     left_dir = vec2_mult_n(right_dir, -1);
    const Vec2 perp_dir = vec2_mult_matrix(*p_dir, ROTATION_MATRIX(-M_PI_2));
    double walk_step = frame_time * UNIT_WALK_STEP, turn_step = frame_time * UNIT_TURN_STEP;
    Vec2 pos_offset = {0, 0}, new_pos,
        new_dir = *p_dir,
        new_camera_plane = *p_camera_plane;

    #ifdef USE_SDL3
        // quit
        if (key_states[SDL_SCANCODE_Q])
            program_is_running = false;
        
        // toggle fisheye mode
        if (key_states[SDL_SCANCODE_F])
            use_euclidian_dist = !use_euclidian_dist;

        // enable fast mode
        if (key_states[SDL_SCANCODE_LSHIFT] || key_states[SDL_SCANCODE_RSHIFT])
            walk_step *= FAST_MODE_RATIO, turn_step *= FAST_MODE_RATIO;
        else
            walk_step = frame_time * UNIT_WALK_STEP, turn_step = frame_time * UNIT_TURN_STEP;
        
        // walk
        if (key_states[SDL_SCANCODE_UP])
            pos_offset = vec2_add(pos_offset, vec2_mult_n(*p_dir, walk_step));
        if (key_states[SDL_SCANCODE_DOWN])
            pos_offset = vec2_add(pos_offset, vec2_mult_n(*p_dir, -walk_step));
        
        if (key_states[SDL_SCANCODE_RIGHT]) {
            // strafe
            if (key_states[SDL_SCANCODE_LALT] || key_states[SDL_SCANCODE_RALT])
                pos_offset = vec2_add(pos_offset, vec2_mult_n(perp_dir, walk_step));
            // turn
            else {
                new_dir = vec2_mult_matrix(*p_dir, ROTATION_MATRIX(turn_step));
                new_camera_plane = vec2_mult_matrix(*p_camera_plane, ROTATION_MATRIX(turn_step));
            }
        }
        if (key_states[SDL_SCANCODE_LEFT]) {
            // strafe
            if (key_states[SDL_SCANCODE_LALT] || key_states[SDL_SCANCODE_RALT])
                pos_offset = vec2_add(pos_offset, vec2_mult_n(perp_dir, -walk_step));
            // turn
            else {
                new_dir = vec2_mult_matrix(*p_dir, ROTATION_MATRIX(-turn_step));
                new_camera_plane = vec2_mult_matrix(*p_camera_plane, ROTATION_MATRIX(-turn_step));
            }
        }

    #elif defined USE_NCURSES
        switch (getch()) {
            // quit
            case KEY_LOWERCASE_Q:
            case KEY_UPPERCASE_Q:
                program_is_running = false;
                break;

            // fisheye
            case KEY_LOWERCASE_F:
            case KEY_UPPERCASE_F:
                use_euclidian_dist = !use_euclidian_dist;
                break;

            // walk
            case KEY_UP:
                new_pos = vec2_add(*p_pos, vec2_mult_n(forward_dir, UNIT_WALK_STEP));
                // *p_pos = vec2_add(*p_pos, delta_pos);
                break;
            case KEY_DOWN:
                new_pos = vec2_add(*p_pos, vec2_mult_n(forward_dir, -UNIT_WALK_STEP));
                // *p_pos = vec2_add(*p_pos, delta_pos);
                break;
            case KEY_SUP:
                new_pos = vec2_add(*p_pos, vec2_mult_n(forward_dir, FAST_MODE_RATIO * UNIT_WALK_STEP));
                // *p_pos = vec2_add(*p_pos, delta_pos);
                break;
            case KEY_SDOWN:
                new_pos = vec2_add(*p_pos, vec2_mult_n(forward_dir, -FAST_MODE_RATIO * UNIT_WALK_STEP));
                // *p_pos = vec2_add(*p_pos, delta_pos);
                break;
            
            // strafe
            case KEY_ALT_RIGHT:
                new_pos = vec2_add(*p_pos, vec2_mult_n(right_dir, UNIT_WALK_STEP));
                // *p_pos = vec2_add(*p_pos, delta_pos);
                break;
            case KEY_ALT_LEFT:
                new_pos = vec2_add(*p_pos, vec2_mult_n(left_dir, UNIT_WALK_STEP));
                // *p_pos = vec2_add(*p_pos, delta_pos);
                break;

            // turn
            case KEY_RIGHT:
                *p_dir = vec2_mult_matrix(*p_dir, ROTATION_MATRIX(UNIT_TURN_STEP));
                *p_camera_plane = vec2_mult_matrix(*p_camera_plane, ROTATION_MATRIX(UNIT_TURN_STEP));
                break;
            case KEY_LEFT:
                *p_dir = vec2_mult_matrix(*p_dir, ROTATION_MATRIX(-UNIT_TURN_STEP));
                *p_camera_plane = vec2_mult_matrix(*p_camera_plane, ROTATION_MATRIX(-UNIT_TURN_STEP));
                break;
            case KEY_SRIGHT:
                *p_dir = vec2_mult_matrix(*p_dir, ROTATION_MATRIX(2 * UNIT_TURN_STEP));
                *p_camera_plane = vec2_mult_matrix(*p_camera_plane, ROTATION_MATRIX(FAST_MODE_RATIO * UNIT_TURN_STEP));
                break;
            case KEY_SLEFT:
                *p_dir = vec2_mult_matrix(*p_dir, ROTATION_MATRIX(-2 * UNIT_TURN_STEP));
                *p_camera_plane = vec2_mult_matrix(*p_camera_plane, ROTATION_MATRIX(-FAST_MODE_RATIO * UNIT_TURN_STEP));
                break;
        }
    #endif
    
    new_pos = vec2_add(*p_pos, vec2_normalize(pos_offset));
    *p_pos = vec2_limit(new_pos, (Vec2) {0, 0}, (Vec2) {MAP_W, MAP_H});
    *p_dir = new_dir, *p_camera_plane = new_camera_plane;
    // CREATE A COLLISION CHECK!!!
}
