//
// Created by Morpheus on 07-Oct-17.
//

#include <cynical_graphics.h>
#include <cynical_memory.h>

mesh* make_mesh(float* vertices,
                size_t vertice_count,
                float* colors,
                size_t color_count,
                int* indices_data,
                size_t indices_count) {

    mesh* mesh = malloc(sizeof(mesh));
    mesh->vertices = vertices;
    mesh->vertices_count = vertice_count;

    mesh->colors = colors;
    mesh->colors_count = color_count;

    mesh->indices = indices_data;
    mesh->indices_count = indices_count;

    GLuint vbo_handle;
    glGenBuffers(1, &vbo_handle);

    ASSERT(vbo_handle);

    float* buffer = frame_memory_malloc(sizeof(float) * (vertice_count + color_count));
    memcpy(buffer, vertices, vertice_count * sizeof(float));
    memcpy(buffer + (vertice_count * sizeof(float)), colors, color_count * sizeof(float));

    glBindBuffer(GL_VERTEX_ARRAY, vbo_handle);
    glBufferData(vbo_handle, vertice_count + color_count, buffer, GL_STATIC_DRAW);

    frame_memory_free(buffer);

    GLuint ibo_handle;
    glGenBuffers(1, &ibo_handle);

    ASSERT(ibo_handle);

    glBindBuffer(GL_INDEX_ARRAY, ibo_handle);
    glBufferData(ibo_handle, indices_count, indices_data, GL_STATIC_DRAW);

    mesh->vbo_handle = vbo_handle;
    mesh->ibo_handle = ibo_handle;

    return mesh;
}

void free_mesh(mesh* mesh) {
    GLuint buffers[] = {mesh->vbo_handle, mesh->ibo_handle};
    glDeleteBuffers(2, buffers);
    free(mesh);
}

shader* make_shader(const char* vertex_source, const char* fragment_source) {
    GLuint vertex_handle = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_handle, 1, &vertex_source, NULL);
    glCompileShader(vertex_handle);

    CHECK_SHADER_COMPILE_STATUS(vertex_handle, vertex_source);

    GLuint fragment_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_handle, 1, &fragment_source, NULL);
    glCompileShader(fragment_handle);

    CHECK_SHADER_COMPILE_STATUS(fragment_handle, fragment_source);

    GLuint program_handle = glCreateProgram();
    glAttachShader(program_handle, vertex_handle);
    glAttachShader(program_handle, fragment_handle);
    glLinkProgram(program_handle);

    CHECK_SHADER_LINK_STATUS(program_handle);

    shader* result = malloc(sizeof(shader));
    result->program_handle = program_handle;
    result->vertex_handle = vertex_handle;
    result->fragment_handle = fragment_handle;
    return result;
}

void free_shader(shader* shader) {
    glDeleteShader(shader->vertex_handle);
    glDeleteShader(shader->fragment_handle);
    glDeleteProgram(shader->program_handle);
    free(shader);
}

size_t get_attribute_dimention(VERTEX_ATTRIB_TYPE type) {
    switch (type) {
        case VERTEX_ATTRIB_FLOAT:
            return 1;
        case VERTEX_ATTRIB_VECTOR2:
            return 2;
        case VERTEX_ATTRIB_VECTOR3:
            return 3;
        case VERTEX_ATTRIB_VECTOR4:
            return 4;
        case VERTEX_ATTRIB_MATRIX4X4:
            return 16;
    }
}

vertex_attribute* make_vertex_attribute(shader* shader, vertex_attribute_defition definition) {

    vertex_attribute* attribute = malloc(sizeof(vertex_attribute));
    attribute->type = definition.type;
    attribute->offset = definition.offset;
    attribute->padding = definition.padding;
    attribute->name = definition.name;
    attribute->normalized = definition.normalized;
    attribute->dimention = get_attribute_dimention(definition.type);

    attribute->handle = glGetAttribLocation(shader->program_handle, definition.name);
    ASSERT(attribute->handle >= 0);

    return attribute;
}

void free_vertex_attribute(vertex_attribute* attribute) {
    free(attribute);
}

uniform* make_uniform(shader* shader, uniform_definition definition) {
    uniform* result = malloc(sizeof(uniform));
    result->name = definition.name;
    result->type = definition.type;
    result->data = definition.data;

    result->handle = glGetUniformLocation(shader->program_handle, definition.name);
    ASSERT_BREAK(result->handle >= 0);

    return result;
}

void free_uniform(uniform* uniform) {
    free(uniform);
}

material* make_material(shader* shader,
                        uniform_definition* uniforms,
                        size_t uniforms_size,
                        vertex_attribute_defition* vertex_attributes,
                        size_t vertex_attributes_size) {

    uniform** uniform_list = malloc(sizeof(uniform*) * uniforms_size);
    for (int i = 0; i < uniforms_size; ++i) {
        uniform_list[i] = make_uniform(shader, uniforms[i]);
    }

    vertex_attribute** vertex_attribute_list = malloc(sizeof(vertex_attribute*) * vertex_attributes_size);
    for (int i = 0; i < vertex_attributes_size; ++i) {
        vertex_attribute_list[i] = make_vertex_attribute(shader, vertex_attributes[i]);
    }

    material* material = malloc(sizeof(material));
    material->shader = shader;
    material->uniforms = uniform_list;
    material->uniform_size = uniforms_size;
    material->attributes = vertex_attribute_list;
    material->attribute_size = vertex_attributes_size;
    return material;
}

void free_material(material* material) {
    size_t uniform_size = material->uniform_size;
    uniform** uniforms = material->uniforms;
    for (int i = 0; i < uniform_size; ++i) {
        free_uniform(uniforms[i]);
    }

    size_t attributes_size = material->attribute_size;
    vertex_attribute** attributes = material->attributes;
    for (int i = 0; i < attributes_size; ++i) {
        free_vertex_attribute(attributes[i]);
    }

    free(material);
}

GLenum get_gl_attribute_type(VERTEX_ATTRIB_TYPE type) {
    switch (type) {
        case VERTEX_ATTRIB_FLOAT:
            return GL_FLOAT;
        case VERTEX_ATTRIB_VECTOR2:
            return GL_FLOAT;
        case VERTEX_ATTRIB_VECTOR3:
            return GL_FLOAT;
        case VERTEX_ATTRIB_VECTOR4:
            return GL_FLOAT;
        case VERTEX_ATTRIB_MATRIX4X4:
            return GL_FLOAT;
    }

    return GL_FLOAT;
}

GLboolean get_gl_bool(bool value) {
    if (value)
        return GL_TRUE;
    else
        return GL_FALSE;
}

void set_uniforms_data_on_gl(uniform** uniforms, size_t length) {
    for (int i = 0; i < length; ++i) {
        uniform* uniform = uniforms[i];
        set_uniform_data_on_gl(uniform);
    }
}

void set_uniform_data_on_gl(uniform* uniform) {
    uniform_data data = uniform->data;
    float matrix_data[4][4];
    switch (uniform->type) {
        case UNIFORM_FLOAT:
            glUniform1f(uniform->handle, data.float_value);
            break;
        case UNIFORM_VECTOR2:
            glUniform2f(uniform->handle, data.vector2_value.x, data.vector2_value.y);
            break;
        case UNIFORM_VECTOR3:
            glUniform3f(uniform->handle,
                        data.vector3_value.x,
                        data.vector3_value.y,
                        data.vector3_value.z);
            break;
        case UNIFORM_VECTOR4:
            glUniform4f(uniform->handle,
                        data.vector4_value.x,
                        data.vector4_value.y,
                        data.vector4_value.z,
                        data.vector4_value.w);
            break;
        case UNIFORM_MATRIX4X4:
            get_gl_matrix4x4(matrix_data, data.matrix4x4_value);
            glUniformMatrix4fv(uniform->handle, 1, GL_FALSE, (const GLfloat*) matrix_data);
            glUniform1f(uniform->handle, uniform->data.float_value);
            break;
    }
}