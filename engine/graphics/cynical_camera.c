//
// Created by Morpheus on 06-Oct-17.
//

#include <cynical_camera.h>

// ################### BASE CAMERA ##########################

camera* make_base_camera(CAMERA_TYPE type) {
    camera* result = malloc(sizeof(camera));

    result->type = type;
    result->projection = make_matrix4x4();
    result->view = make_matrix4x4();
    result->transform = make_transform();

    return result;
}

void free_camera(camera* camera) {
    free_matrix4x4(camera->view);
    free_matrix4x4(camera->projection);
    free_transform(camera->transform);

    switch (camera->type) {
        case CAMERA_ORTHO:
            free_ortho_camera(camera->ortho);
            break;
        case CAMERA_PERSPECTIVE:
            free_perspective_camera(camera->perspective);
            break;
    }
}

void camera_update_matrix(camera* camera) {
    switch (camera->type) {
        case CAMERA_ORTHO:
            camera_set_ortho_matrix(camera->ortho,
                                    camera->transform,
                                    camera->projection,
                                    camera->view);
            break;
        case CAMERA_PERSPECTIVE:
            camera_set_perspective_matrix(camera->perspective,
                                          camera->transform,
                                          camera->projection,
                                          camera->view);
            break;
    }
}

// ################# PERSPECTIVE #######################

camera* make_perspective_camera(float fov, float aspect, float near, float far) {
    camera* base = make_base_camera(CAMERA_PERSPECTIVE);
    perspective_camera* camera = malloc(sizeof(perspective_camera));

    camera->fov = fov;
    camera->aspect = aspect;
    camera->near = near;
    camera->far = far;

    base->perspective = camera;

    camera_set_perspective_matrix(camera, base->transform, base->projection, base->view);

    return base;
}

void free_perspective_camera(perspective_camera* camera) {
    free(camera);
}

// ##################### ORTHO ##########################

camera* make_ortho_camera(float left, float right, float bottom, float top, float near, float far) {
    camera* base = make_base_camera(CAMERA_ORTHO);
    ortho_camera* camera = malloc(sizeof(ortho_camera));

    camera->top = top;
    camera->bottom = bottom;

    camera->left = left;
    camera->right = right;

    camera->near = near;
    camera->far = far;

    base->ortho = camera;

    camera_set_ortho_matrix(camera, base->transform, base->projection, base->view);

    return base;
}

void free_ortho_camera(ortho_camera* camera) {
    free(camera);
}

// ################# MATRICES ####################

void camera_set_perspective_matrix(
        perspective_camera* perspective,
        transform* camera_trans,
        matrix4x4* projection,
        matrix4x4* view) {
    set_matrix4x4_identity(projection);
    matrix4x4_perspective(projection, perspective->fov, perspective->aspect, perspective->near, perspective->far);

    set_matrix4x4_identity(view);
    matrix4x4_look_at(view, camera_trans->position, camera_trans->forward, camera_trans->up);
}

void camera_set_ortho_matrix(ortho_camera* ortho, transform* camera_trans, matrix4x4* projection, matrix4x4* view) {
    set_matrix4x4_identity(projection);
    matrix4x4_ortho(
            projection,
            ortho->left,
            ortho->right,
            ortho->bottom,
            ortho->top,
            ortho->near,
            ortho->far
    );

    set_matrix4x4_identity(view);
    matrix4x4_look_at(view, camera_trans->position, camera_trans->forward, camera_trans->up);
}

void camera_get_vp_matrix(matrix4x4* result, camera* camera) {
    set_matrix4x4_identity(result);
    matrix4x4_mul(result, result, camera->projection);
    matrix4x4_mul(result, result, camera->view);
}

vector3 camera_screen_to_world_coord(camera* camera, vector3 screen_coord) {
    // https://stackoverflow.com/questions/7692988/opengl-math-projecting-screen-space-to-world-space-coords

    vector4 point = make_vector4(screen_coord.x, screen_coord.y, screen_coord.z, 1.f);

    matrix4x4 vp;
    camera_get_vp_matrix(&vp, camera);
    matrix4x4_invert(&vp, &vp);

    MATRIX4x4_PRINT(&vp);

    vector4 multiplied_vector;
    matrix4x4_mul_vector4(&multiplied_vector, &vp, &point);
    vector4 result_vector = vector4_scale(multiplied_vector, 1.f / multiplied_vector.w);

    return make_vector3(result_vector.x, result_vector.y, result_vector.z);
}

vector2 camera_world_to_screen_coord(camera* camera, vector3 world_coord) {
    vector4 point = make_vector4(world_coord.x, world_coord.y, world_coord.z, 1.f);
    matrix4x4 vp;
    camera_get_vp_matrix(&vp, camera);

    vector4 multiplied_vector;
    matrix4x4_mul_vector4(&multiplied_vector, &vp, &point);

    vector4 result_vector = vector4_scale(multiplied_vector, 1.f / multiplied_vector.w);
    return make_vector2(result_vector.x, result_vector.y);
}