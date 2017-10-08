//
// Created by Morpheus on 06-Oct-17.
//

#include <cynical_camera.h>

// ################### BASE CAMERA ##########################

camera_t* make_base_camera(CAMERA_TYPE_T type) {
    camera_t* result = malloc(sizeof(camera_t));

    result->type = type;
    result->projection = make_matrix4x4();
    result->view = make_matrix4x4();
    result->transform = make_transform();

    return result;
}

void free_camera(camera_t* camera) {
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

void camera_update_matrix(camera_t* camera) {
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

camera_t* make_perspective_camera(float fov, float aspect, float near, float far) {
    camera_t* base = make_base_camera(CAMERA_PERSPECTIVE);
    perspective_camera_t* camera = malloc(sizeof(perspective_camera_t));

    camera->fov = fov;
    camera->aspect = aspect;
    camera->near = near;
    camera->far = far;

    base->perspective = camera;

    camera_set_perspective_matrix(camera, base->transform, base->projection, base->view);

    return base;
}

void free_perspective_camera(perspective_camera_t* camera) {
    free(camera);
}

// ##################### ORTHO ##########################

camera_t* make_ortho_camera(float left, float right, float bottom, float top, float near, float far) {
    camera_t* base = make_base_camera(CAMERA_ORTHO);
    ortho_camera_t* camera = malloc(sizeof(ortho_camera_t));

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

void free_ortho_camera(ortho_camera_t* camera) {
    free(camera);
}

// ################# MATRICES ####################

void camera_set_perspective_matrix(
        perspective_camera_t* perspective,
        transform_t* camera_trans,
        matrix4x4_t* projection,
        matrix4x4_t* view) {
    set_matrix4x4_identity(projection);
    matrix4x4_perspective(projection, perspective->fov, perspective->aspect, perspective->near, perspective->far);

    set_matrix4x4_identity(view);
    matrix4x4_look_at(view, camera_trans->position, camera_trans->forward, camera_trans->up);
}

void camera_set_ortho_matrix(ortho_camera_t* ortho, transform_t* camera_trans, matrix4x4_t* projection, matrix4x4_t* view) {
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

void camera_get_vp_matrix(matrix4x4_t* result, camera_t* camera) {
    set_matrix4x4_identity(result);
    matrix4x4_mul(result, result, camera->projection);
    matrix4x4_mul(result, result, camera->view);
}

vector3_t camera_screen_to_world_coord(camera_t* camera, vector3_t screen_coord) {
    // https://stackoverflow.com/questions/7692988/opengl-math-projecting-screen-space-to-world-space-coords

    vector4_t point = make_vector4(screen_coord.x, screen_coord.y, screen_coord.z, 1.f);

    matrix4x4_t vp;
    camera_get_vp_matrix(&vp, camera);
    matrix4x4_invert(&vp, &vp);

    MATRIX4x4_PRINT(&vp);

    vector4_t multiplied_vector;
    matrix4x4_mul_vector4(&multiplied_vector, &vp, &point);
    vector4_t result_vector = vector4_scale(multiplied_vector, 1.f / multiplied_vector.w);

    return make_vector3(result_vector.x, result_vector.y, result_vector.z);
}

vector2_t camera_world_to_screen_coord(camera_t* camera, vector3_t world_coord) {
    vector4_t point = make_vector4(world_coord.x, world_coord.y, world_coord.z, 1.f);
    matrix4x4_t vp;
    camera_get_vp_matrix(&vp, camera);

    vector4_t multiplied_vector;
    matrix4x4_mul_vector4(&multiplied_vector, &vp, &point);

    vector4_t result_vector = vector4_scale(multiplied_vector, 1.f / multiplied_vector.w);
    return make_vector2(result_vector.x, result_vector.y);
}