//
// Created by Morpheus on 08-Oct-17.
//

#include <cynical_render.h>
#include <cynical_video.h>
#include <cynical_camera.h>

render_state_t* main_render_state;

void render_init() {
    main_render_state = calloc(1, sizeof(render_state_t));
    main_render_state->vp_matrix = make_matrix4x4();
}

void render_release() {
    free_matrix4x4(main_render_state->vp_matrix);
    free(main_render_state);
}

void render_start_draw(camera_t* camera) {
    glClear(GL_COLOR_BUFFER_BIT);
    main_render_state->current_camera = camera;

    camera_update_matrix(camera);
    camera_get_vp_matrix(main_render_state->vp_matrix, camera);
}

void render_bind_material(material_t* material) {
    glUseProgram(material->shader->program_handle);
    CHECK_GL_ERROR();

    main_render_state->current_material = material;
    uniform_t* mvp_uniform = get_uniform_by_tag(material, UNIFORM_TAG_MVP);
    if (mvp_uniform) {
        main_render_state->mvp_uniform = mvp_uniform;
    }
}

void render_draw(transform_t* mesh_transform, mesh_t* mesh) {
    // if the currently binded shader has a MVP uniform, define it
    if (main_render_state->mvp_uniform) {
        matrix4x4_t mvp;
        matrix4x4_mul(&mvp, main_render_state->vp_matrix, mesh_transform->matrix);
        main_render_state->mvp_uniform->data.matrix4x4_value = mvp;
        rebuff_uniform(main_render_state->mvp_uniform);
    }

    glBindVertexArray(mesh->vao_handle);
    CHECK_GL_ERROR();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo_handle);
    CHECK_GL_ERROR();

    glDrawElements(
            GL_TRIANGLE_FAN,
            mesh->indices_count,
            GL_UNSIGNED_INT,
            NULL
    );
    CHECK_GL_ERROR();
}

void render_end_draw() {
    glfwSwapBuffers(main_window->glfw_main_window);

    main_render_state->current_material = NULL;
    main_render_state->current_camera = NULL;
    main_render_state->mvp_uniform = NULL;
}