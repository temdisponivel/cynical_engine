//
// Created by Morpheus on 08-Oct-17.
//

#include <cynical_render.h>
#include <cynical_video.h>

void start_draw() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void bind_material(material* material) {
    glUseProgram(material->shader->program_handle);

    for (int i = 0; i < material->uniform_size; ++i) {
        uniform* uni = material->uniforms[i];
        if (uni->rebuff) {
            set_uniform_data_on_gl(uni);
            uni->rebuff = false;
        }
    }
}

void draw(mesh* mesh) {
    if (mesh->rebuff) {
        buff_mesh_data(mesh);
        mesh->rebuff = false;
    }

    glBindVertexArray(mesh->vao_handle);

    glDrawElements(
            GL_TRIANGLES,
            mesh->vertices_count / 3,
            GL_UNSIGNED_BYTE,
            NULL
    );
}

void end_draw() {
    glfwSwapBuffers(main_window->glfw_main_window);
}