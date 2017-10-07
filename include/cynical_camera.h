//
// Created by Morpheus on 06-Oct-17.
//

#ifndef CYNICAL_ENGINE_CYNICAL_GRAPHICS_H
#define CYNICAL_ENGINE_CYNICAL_GRAPHICS_H

#include "cynical_math.h"

typedef enum {
    CAMERA_ORTHO,
    CAMERA_PERSPECTIVE
} CAMERA_TYPE;

typedef struct ortho_camera_s {
    float near;
    float far;

    float left;
    float right;

    float bottom;
    float top;
} ortho_camera;

typedef struct perspective_camera_s {
    float fov;
    float aspect;
    float near;
    float far;
} perspective_camera;

typedef struct camera_s {
    CAMERA_TYPE type;

    matrix4x4* view;
    matrix4x4* projection;
    transform* transform;

    union {
        ortho_camera* ortho;
        perspective_camera* perspective;
    };
} camera;

camera* make_base_camera(CAMERA_TYPE type);
void free_camera(camera* camera);

camera* make_perspective_camera(float fov, float aspect, float near, float far);
void free_perspective_camera(perspective_camera* camera);

camera* make_ortho_camera(float left, float right, float bottom, float top, float near, float far);
void free_ortho_camera(ortho_camera* camera);

void camera_update_matrix(camera* camera);
void camera_set_perspective_matrix(perspective_camera* perspective, transform* trans, matrix4x4* projection, matrix4x4* view);
void camera_set_ortho_matrix(ortho_camera* ortho, transform* trans, matrix4x4* projection, matrix4x4* view);

vector3 camera_screen_to_world_coord(camera* camera, vector3 screen_coord);
vector2 camera_world_to_screen_coord(camera* camera, vector3 world_coord);

void camera_get_vp_matrix(matrix4x4* result, camera* camera);

#endif //CYNICAL_ENGINE_CYNICAL_GRAPHICS_H
