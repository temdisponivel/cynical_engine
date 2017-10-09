//
// Created by Morpheus on 07-Oct-17.
//

#include <cynical_graphics.h>
#include <cynical_memory.h>

#define VERTEX_POS_ATTRIBUTE_INDEX 0
#define VERTEX_COLOR_ATTRIBUTE_INDEX 1

size_t get_vertex_byte_size() {
    // 3 floats for position
    // 4 floats for color
    return sizeof(float) * (3 + 4);
}

vertex_attribute_t* find_vertex_attrib_by_type(material_t* material, VERTEX_ATTRIB_TYPE_T type) {
    size_t length = material->attribute_size;
    for (int i = 0; i < length; ++i) {
        vertex_attribute_t* attr = material->attributes[i];
        if (attr->type == type) {
            return attr;
        }
    }

    return NULL;
}

GLuint get_vertex_attrib_index(material_t* material, VERTEX_ATTRIB_TYPE_T type) {
    GLint vertex_index = -1;
    if (material) {
        vertex_attribute_t* vertex_pos_attr = find_vertex_attrib_by_type(material, type);
        if (vertex_pos_attr) {
            vertex_index = vertex_pos_attr->handle;
        }
    }

    if (vertex_index < 0) {
        switch (type) {
            case VERTEX_ATTRIB_POS:
                vertex_index = VERTEX_POS_ATTRIBUTE_INDEX;
                break;
            case VERTEX_ATTRIB_COLOR:
                vertex_index = VERTEX_COLOR_ATTRIBUTE_INDEX;
                break;
        }
    }

    return (GLuint) vertex_index;
}

mesh_t* make_mesh(vertex_t* vertices_data,
                  size_t vertices_count,
                  int* indices_data,
                  size_t indices_count) {

    GLuint vao_handle;
    glGenVertexArrays(1, &vao_handle);
    ASSERT(vao_handle >= 0);
    glBindVertexArray(vao_handle);

    GLuint vertex_vbo;
    glGenBuffers(1, &vertex_vbo);
    ASSERT(vertex_vbo >= 0);

    GLuint indices_vbo;
    glGenBuffers(1, &indices_vbo);
    ASSERT(indices_vbo >= 0);

    mesh_t* mesh = calloc(1, sizeof(mesh_t));
    mesh->vertices = vertices_data;
    mesh->vertices_count = vertices_count;

    mesh->indices = indices_data;
    mesh->indices_count = indices_count;

    mesh->ibo_handle = indices_vbo;
    mesh->vbo_handle = vertex_vbo;
    mesh->vao_handle = vao_handle;

    return mesh;
}

void set_mesh_material(mesh_t* mesh, material_t* material) {
    mesh->material = material;
    buff_mesh_data(mesh);
}

void buff_mesh_data(mesh_t* mesh) {
    glBindVertexArray(mesh->vao_handle);

    CHECK_GL_ERROR();

    size_t full_vertex_data_byte_size = get_vertex_byte_size() * mesh->vertices_count;
    float* full_vertex_data = frame_memory_calloc(full_vertex_data_byte_size);

    int j = 0;
    for (int i = 0; i < mesh->vertices_count; i++) {
        vertex_t vertex = mesh->vertices[i];

        full_vertex_data[j++] = vertex.position.x;
        full_vertex_data[j++] = vertex.position.y;
        full_vertex_data[j++] = vertex.position.z;

        full_vertex_data[j++] = vertex.color.x;
        full_vertex_data[j++] = vertex.color.y;
        full_vertex_data[j++] = vertex.color.z;
        full_vertex_data[j++] = vertex.color.w;
    }

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo_handle);
    CHECK_GL_ERROR();

    glBufferData(GL_ARRAY_BUFFER, full_vertex_data_byte_size, full_vertex_data, GL_STATIC_DRAW);
    CHECK_GL_ERROR();

    size_t stride = sizeof(float) * (3 + 4);

    GLuint vertex_pos_index = get_vertex_attrib_index(mesh->material, VERTEX_ATTRIB_POS);

    glVertexAttribPointer(
            vertex_pos_index,
            3, // there's 3 floats representing position
            GL_FLOAT,
            GL_FALSE,
            stride,
            0
    );
    CHECK_GL_ERROR();

    glEnableVertexAttribArray(vertex_pos_index);
    CHECK_GL_ERROR();

    GLuint vertex_color_index = get_vertex_attrib_index(mesh->material, VERTEX_ATTRIB_COLOR);

    size_t offset = sizeof(float) * 3;
    glVertexAttribPointer(
            vertex_color_index,
            4, // there's 4 floats representing color
            GL_FLOAT,
            GL_FALSE,
            stride, // there's 3 floats of position between this color and the next
            offset // there's 3 floats of position before the first color
    );
    CHECK_GL_ERROR();

    glEnableVertexAttribArray(vertex_color_index);
    CHECK_GL_ERROR();

    frame_memory_free(full_vertex_data);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo_handle);
    CHECK_GL_ERROR();

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(size_t) * mesh->indices_count, mesh->indices, GL_STATIC_DRAW);
    CHECK_GL_ERROR();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    CHECK_GL_ERROR();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    CHECK_GL_ERROR();

    glBindVertexArray(0);
    CHECK_GL_ERROR();
}

void free_mesh(mesh_t* mesh) {
    glDeleteVertexArrays(1, &mesh->vao_handle);
    GLuint buffers[] = {mesh->vbo_handle, mesh->ibo_handle};
    glDeleteBuffers(2, buffers);
    free(mesh);
}

shader_t* make_shader(const char* vertex_source, const char* fragment_source) {
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

    shader_t* result = calloc(1, sizeof(shader_t));
    result->program_handle = program_handle;
    result->vertex_handle = vertex_handle;
    result->fragment_handle = fragment_handle;
    return result;
}

void free_shader(shader_t* shader) {
    glDeleteShader(shader->vertex_handle);
    glDeleteShader(shader->fragment_handle);
    glDeleteProgram(shader->program_handle);
    free(shader);
}

vertex_attribute_t* make_vertex_attribute(shader_t* shader, vertex_attribute_defition_t definition) {

    vertex_attribute_t* attribute = malloc(sizeof(vertex_attribute_t));
    attribute->type = definition.type;
    attribute->name = definition.name;

    attribute->handle = glGetAttribLocation(shader->program_handle, definition.name);
    CHECK_GL_ERROR()
    ASSERT(attribute->handle >= 0);

//    switch (attribute->type) {
//        case VERTEX_ATTRIB_POS:
//            glBindAttribLocation(shader->program_handle, VERTEX_POS_ATTRIBUTE_INDEX, definition.name);
//            CHECK_GL_ERROR();
//            break;
//        case VERTEX_ATTRIB_COLOR:
//            glBindAttribLocation(shader->program_handle, VERTEX_COLOR_ATTRIBUTE_INDEX, definition.name);
//            CHECK_GL_ERROR();
//            break;
//    }

    return attribute;
}

void free_vertex_attribute(vertex_attribute_t* attribute) {
    free(attribute);
}

uniform_t* make_uniform(shader_t* shader, uniform_definition_t definition) {
    uniform_t* result = malloc(sizeof(uniform_t));
    result->name = definition.name;
    result->type = definition.type;
    result->data = definition.data;

    result->handle = glGetUniformLocation(shader->program_handle, definition.name);
    ASSERT(result->handle >= 0);

    return result;
}

void free_uniform(uniform_t* uniform) {
    free(uniform);
}

material_t* make_material(shader_t* shader,
                          uniform_definition_t* uniforms,
                          size_t uniforms_size,
                          vertex_attribute_defition_t* vertex_attributes,
                          size_t vertex_attributes_size) {

    glUseProgram(shader->program_handle);

    uniform_t** uniform_list = calloc(uniforms_size, sizeof(uniform_t*));
    for (int i = 0; i < uniforms_size; ++i) {
        uniform_list[i] = make_uniform(shader, uniforms[i]);
    }

    vertex_attribute_t** vertex_attribute_list = calloc(vertex_attributes_size, sizeof(vertex_attribute_t*));
    for (int i = 0; i < vertex_attributes_size; ++i) {
        vertex_attribute_list[i] = make_vertex_attribute(shader, vertex_attributes[i]);
    }

    material_t* material = calloc(1, sizeof(material_t));
    material->shader = shader;
    material->uniforms = uniform_list;
    material->uniform_size = uniforms_size;
    material->attributes = vertex_attribute_list;
    material->attribute_size = vertex_attributes_size;
    return material;
}

void free_material(material_t* material) {
    size_t uniform_size = material->uniform_size;
    uniform_t** uniforms = material->uniforms;
    for (int i = 0; i < uniform_size; ++i) {
        free_uniform(uniforms[i]);
    }

    size_t attributes_size = material->attribute_size;
    vertex_attribute_t** attributes = material->attributes;
    for (int i = 0; i < attributes_size; ++i) {
        free_vertex_attribute(attributes[i]);
    }

    free(material);
}

GLenum get_gl_attribute_type(VERTEX_ATTRIB_TYPE_T type) {
    switch (type) {
        case VERTEX_ATTRIB_COLOR:
        case VERTEX_ATTRIB_POS:
            return GL_FLOAT;
    }

    return GL_FLOAT;
}

GLboolean get_gl_bool(bool_t value) {
    if (value)
        return GL_TRUE;
    else
        return GL_FALSE;
}

void rebuff_multiple_uniform_data(uniform_t** uniforms, size_t length) {
    for (int i = 0; i < length; ++i) {
        uniform_t* uniform = uniforms[i];
        rebuff_uniform_data(uniform);
    }
}

void rebuff_uniform_data(uniform_t* uniform) {
    uniform_data_t data = uniform->data;
    float matrix_data[4][4];
    switch (uniform->type) {
        case UNIFORM_FLOAT:
            glUniform1f(uniform->handle, data.float_value);
            CHECK_GL_ERROR();
            break;
        case UNIFORM_VECTOR2:
            glUniform2f(uniform->handle, data.vector2_value.x, data.vector2_value.y);
            CHECK_GL_ERROR();
            break;
        case UNIFORM_VECTOR3:
            glUniform3f(uniform->handle,
                        data.vector3_value.x,
                        data.vector3_value.y,
                        data.vector3_value.z);
            CHECK_GL_ERROR();
            break;
        case UNIFORM_VECTOR4:
            glUniform4f(uniform->handle,
                        data.vector4_value.x,
                        data.vector4_value.y,
                        data.vector4_value.z,
                        data.vector4_value.w);
            CHECK_GL_ERROR();
            break;
        case UNIFORM_MATRIX4X4:
            get_gl_matrix4x4(matrix_data, &data.matrix4x4_value);
            glUniformMatrix4fv(uniform->handle, 1, GL_FALSE, (const GLfloat*) matrix_data);
            CHECK_GL_ERROR();
            break;
    }
}