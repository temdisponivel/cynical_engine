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
    result->entity = make_world_entity();

    return result;
}

void free_camera(camera* camera) {
    free_matrix4x4(camera->view);
    free_matrix4x4(camera->projection);
    free_world_entity(camera->entity);

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
                                    camera->entity->transform,
                                    camera->projection,
                                    camera->view);
            break;
        case CAMERA_PERSPECTIVE:
            camera_set_perspective_matrix(camera->perspective,
                                          camera->entity->transform,
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

    camera_set_perspective_matrix(camera, base->entity->transform, base->projection, base->view);

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

    camera_set_ortho_matrix(camera, base->entity->transform, base->projection, base->view);

    return base;
}

void free_ortho_camera(ortho_camera* camera) {
    free(camera);
}

// ################# MATRICES ####################

void camera_set_perspective_matrix(
        perspective_camera* perspective,
        transform* trans,
        matrix4x4* projection,
        matrix4x4* view) {
    set_matrix4x4_identity(projection);
    matrix4x4_perspective(projection, perspective->fov, perspective->aspect, perspective->near, perspective->far);

    set_matrix4x4_identity(view);
    matrix4x4_look_at(view, trans->position, trans->forward, trans->up);
}

void camera_set_ortho_matrix(ortho_camera* ortho, transform* trans, matrix4x4* projection, matrix4x4* view) {
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
    matrix4x4_look_at(view, trans->position, trans->forward, trans->up);
}

void camera_get_model_view(matrix4x4* model_view, camera* camera) {
    set_matrix4x4_identity(model_view);
    matrix4x4_mul(model_view, camera->projection, camera->view);
}