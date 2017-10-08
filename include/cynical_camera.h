//
// Created by Morpheus on 06-Oct-17.
//

#ifndef CYNICAL_ENGINE_CYNICAL_CAMERA_H
#define CYNICAL_ENGINE_CYNICAL_CAMERA_H

#include "cynical_math.h"

typedef enum {
    CAMERA_ORTHO,
    CAMERA_PERSPECTIVE
} CAMERA_TYPE_T;

typedef struct ortho_camera_s {
    float near;
    float far;

    float left;
    float right;

    float bottom;
    float top;
} ortho_camera_t;

typedef struct perspective_camera_s {
    float fov;
    float aspect;
    float near;
    float far;
} perspective_camera_t;

typedef struct camera_s {
    CAMERA_TYPE_T type;

    matrix4x4_t* view;
    matrix4x4_t* projection;
    transform_t* transform;

    union {
        ortho_camera_t* ortho;
        perspective_camera_t* perspective;
    };
} camera_t;

camera_t* make_base_camera(CAMERA_TYPE_T type);

void free_camera(camera_t* camera);

camera_t* make_perspective_camera(float fov, float aspect, float near, float far);

void free_perspective_camera(perspective_camera_t* camera);

camera_t* make_ortho_camera(float left, float right, float bottom, float top, float near, float far);

void free_ortho_camera(ortho_camera_t* camera);

void camera_update_matrix(camera_t* camera);

void camera_set_perspective_matrix(perspective_camera_t* perspective,
                                   transform_t* camera_trans,
                                   matrix4x4_t*
                                   projection,
                                   matrix4x4_t* view);

void camera_set_ortho_matrix(ortho_camera_t* ortho, transform_t* camera_trans, matrix4x4_t* projection, matrix4x4_t* view);

vector3_t camera_screen_to_world_coord(camera_t* camera, vector3_t screen_coord);

vector2_t camera_world_to_screen_coord(camera_t* camera, vector3_t world_coord);

void camera_get_vp_matrix(matrix4x4_t* result, camera_t* camera);

#endif //CYNICAL_ENGINE_CYNICAL_CAMERA_H