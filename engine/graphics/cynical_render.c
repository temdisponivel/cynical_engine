//
// Created by Morpheus on 08-Oct-17.
//

#include <cynical_render.h>
#include <cynical_video.h>

void start_draw() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void bind_material(material_t* material) {
    glUseProgram(material->shader->program_handle);
    CHECK_GL_ERROR();

    rebuff_multiple_uniform_data(material->uniforms, material->uniform_size);
}

void draw(mesh_t* mesh) {
    if (mesh->rebuff) {
        buff_mesh_data(mesh);
        mesh->rebuff = false;
    }

    glBindVertexArray(mesh->vao_handle);
    CHECK_GL_ERROR();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo_handle);
    CHECK_GL_ERROR();

    glDrawElements(
            GL_TRIANGLES,
            mesh->indices_count,
            GL_UNSIGNED_INT,
            NULL
    );
    CHECK_GL_ERROR();
}

void end_draw() {
    glfwSwapBuffers(main_window->glfw_main_window);
}