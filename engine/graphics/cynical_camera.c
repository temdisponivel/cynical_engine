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
    ASSERT(near >= .01f);
    ASSERT(far >= near);
    ASSERT(fov >= 0);
    ASSERT(fov <= 179);

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
    ASSERT(near >= .01f);
    ASSERT(far >= near);

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
    matrix4x4_look_at(view, camera_trans->position, vector3_scale(camera_trans->forward, INT_MAX), camera_trans->up);
}

void camera_set_ortho_matrix(
        ortho_camera_t* ortho,
        transform_t* camera_trans,
        matrix4x4_t* projection,
        matrix4x4_t* view) {
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
    matrix4x4_look_at(view, camera_trans->position, vector3_scale(camera_trans->forward, INT_MAX), camera_trans->up);
}

void camera_get_vp_matrix(matrix4x4_t* result, camera_t* camera) {
    matrix4x4_mul(result, camera->projection, camera->view);
}

vector3_t camera_screen_to_world_coord(camera_t* camera, vector3_t screen_coord) {

    matrix4x4_t vp;
    camera_get_vp_matrix(&vp, camera);
    matrix4x4_invert(&vp, &vp);

    vector4_t point = make_vector4(screen_coord.x, screen_coord.y, screen_coord.z, 1.0f);
    vector4_t unprojected = matrix4x4_mul_vector4(&vp, point);

    vector3_t result = make_vector3(unprojected.x, unprojected.y, unprojected.z);
    result = vector3_scale(result, 1.0f / unprojected.w);
    return result;
}

vector2_t camera_world_to_screen_coord(camera_t* camera, vector3_t world_coord) {

    matrix4x4_t vp;
    camera_get_vp_matrix(&vp, camera);

    vector4_t point = make_vector4(world_coord.x, world_coord.y, world_coord.z, 1.0f);
    vector4_t projected = matrix4x4_mul_vector4(&vp, point);

    vector2_t result = make_vector2(projected.x, projected.y);
    result = vector2_scale(result, 1.0f / projected.w);
    return result;
}