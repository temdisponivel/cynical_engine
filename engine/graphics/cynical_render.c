//
// Created by Morpheus on 08-Oct-17.
//

#include <cynical_render.h>
#include <cynical_video.h>

void bind_attributes(vertex_attribute** attributes, size_t length);

void set_uniforms_data(uniform** uniforms, size_t length);

void start_draw() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void draw(material* material, mesh* mesh) {
    glUseProgram(material->shader->program_handle);

    vertex_attribute** attributes = material->attributes;
    size_t attributes_len = material->attribute_size;

    glBindBuffer(GL_VERTEX_ARRAY, mesh->vbo_handle);
    bind_attributes(attributes, attributes_len);

    glDrawElements(
            GL_TRIANGLES,
            mesh->vertices_count,
            GL_UNSIGNED_BYTE,
            NULL
    );
}

void end_draw() {
    glfwSwapBuffers(main_window->glfw_main_window);
}

void bind_attributes(vertex_attribute** attributes, size_t length) {
    for (int i = 0; i < length; ++i) {
        vertex_attribute* attribute = attributes[i];

        // enable and setup the attribute of the currently binded vertex array
        glEnableVertexAttribArray(attribute->handle);
        glVertexAttribPointer(
                attribute->handle,
                attribute->dimention,
                get_gl_attribute_type(attribute->type),
                get_gl_bool(attribute->normalized),
                attribute->padding,
                (void*) attribute->offset
        );
    }
}