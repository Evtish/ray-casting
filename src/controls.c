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

#define KEY_ALT_RIGHT 567
#define KEY_ALT_LEFT 552
#define KEY_SUP 337
#define KEY_SDOWN 336
#define KEY_LOWERCASE_F 102
#define KEY_UPPERCASE_F 70

// [cos    sin]
// [-sin   cos]
#define ROTATION_MATRIX(a) (Mat22) { \
    (Vec2) {cos(a), -sin(a)}, \
    (Vec2) {sin(a), cos(a)} \
}

void controls_all(Vec2 *const p_pos, Vec2 *const p_dir, Vec2 *const p_camera_plane) {
    Vec2 delta_pos;
    // DVec2 new_map_box;

    switch (getch()) {
        //fisheye
        case KEY_LOWERCASE_F:
        case KEY_UPPERCASE_F:
            use_euclidian_dist = !use_euclidian_dist;
            break;

        // walk
        case KEY_UP:
            delta_pos = vec2_mult_n(*p_dir, WALK_STEP);
            *p_pos = vec2_add(*p_pos, delta_pos);
            break;
        case KEY_DOWN:
            delta_pos = vec2_mult_n(*p_dir, -WALK_STEP);
            *p_pos = vec2_add(*p_pos, delta_pos);
            break;
        case KEY_SUP:
            delta_pos = vec2_mult_n(*p_dir, 2 * WALK_STEP);
            *p_pos = vec2_add(*p_pos, delta_pos);
            break;
        case KEY_SDOWN:
            delta_pos = vec2_mult_n(*p_dir, -2 * WALK_STEP);
            *p_pos = vec2_add(*p_pos, delta_pos);
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

        //strafe
        case KEY_ALT_RIGHT:
            delta_pos = vec2_mult_n(vec2_mult_matrix(*p_dir, ROTATION_MATRIX(M_PI_2)), WALK_STEP);
            *p_pos = vec2_add(*p_pos, delta_pos);
            break;
        case KEY_ALT_LEFT:
            delta_pos = vec2_mult_n(vec2_mult_matrix(*p_dir, ROTATION_MATRIX(3 * M_PI_2)), WALK_STEP);
            *p_pos = vec2_add(*p_pos, delta_pos);
            break;
    }

    *p_pos = vec2_limit(*p_pos, (Vec2) {0, 0}, (Vec2) {MAP_W, MAP_H});
    // CREATE A COLLISION CHECK!!!
}
