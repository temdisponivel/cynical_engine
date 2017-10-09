//
// Created by Morpheus on 07-Oct-17.
//

#ifndef CYNICAL_ENGINE_CYNICAL_RENDER_H
#define CYNICAL_ENGINE_CYNICAL_RENDER_H

#include "cynical_graphics.h"
#include "cynical_camera.h"

typedef struct render_state_s {
    camera_t* current_camera;
    material_t* current_material;

    matrix4x4_t* vp_matrix;
    uniform_t* mvp_uniform;
} render_state_t;

void render_init();

void render_release();

void render_start_draw(camera_t* camera);

void render_bind_material(material_t* material);

void render_draw(transform_t* mesh_transform, mesh_t* mesh);

void render_end_draw();

#endif //CYNICAL_ENGINE_MFE_RENDER_H
