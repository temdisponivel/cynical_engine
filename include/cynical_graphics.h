//
// Created by Morpheus on 07-Oct-17.
//

#ifndef CYNICAL_ENGINE_CYNICAL_GRAPHICS_H
#define CYNICAL_ENGINE_CYNICAL_GRAPHICS_H

#include <cynical_collections.h>
#include <cynical_includes.h>

typedef struct shader_s {
    GLuint vertex_handle;
    GLuint fragment_handle;
    GLuint program_handle;
} shader;

typedef enum {
    VERTEX_ATTRIB_POS,
    VERTEX_ATTRIB_COLOR,
} VERTEX_ATTRIB_TYPE;

typedef struct vertex_attribute_s {
    VERTEX_ATTRIB_TYPE type;
    size_t dimention;
    bool normalized;
    int padding;
    int offset;
    GLint handle;
    char* name;
} vertex_attribute;

typedef struct vertex_attribute_defition_s {
    char* name;
    bool normalized;
    int padding;
    int offset;
    VERTEX_ATTRIB_TYPE type;
} vertex_attribute_defition;

typedef enum {
    UNIFORM_FLOAT,
    UNIFORM_VECTOR2,
    UNIFORM_VECTOR3,
    UNIFORM_VECTOR4,
    UNIFORM_MATRIX4X4,
} UNIFORM_TYPE;

typedef union uniform_data_u {
    float float_value;
    vector2 vector2_value;
    vector3 vector3_value;
    vector4 vector4_value;
    matrix4x4* matrix4x4_value;
} uniform_data;

typedef struct uniform_s {
    GLint handle;
    UNIFORM_TYPE type;
    char* name;
    uniform_data data;
    bool rebuff;
} uniform;

typedef struct uniform_definition_s {
    char* name;
    UNIFORM_TYPE type;
    uniform_data data;
} uniform_definition;

typedef struct material_s {
    uniform** uniforms;
    size_t uniform_size;
    vertex_attribute** attributes;
    size_t attribute_size;
    shader* shader;
} material;

typedef struct mesh_s {
    float* vertices;
    size_t vertices_count;

    float* colors;
    size_t colors_count;

    int* indices;
    size_t indices_count;

    GLuint vbo_handle;
    GLuint ibo_handle;
    GLuint vao_handle;

    material* material;

    bool rebuff;
} mesh;

mesh* make_mesh(float* vertices,
                size_t vertice_count,
                float* colors,
                size_t color_count,
                int* indices_data,
                size_t indices_count);

void free_mesh(mesh* mesh);

void buff_mesh_data(mesh* mesh);

shader* make_shader(const char* vertex_source, const char* fragment_source);

void free_shader(shader* shader);

material* make_material(shader* shader,
                        uniform_definition* uniforms,
                        size_t uniforms_size,
                        vertex_attribute_defition* vertex_attributes,
                        size_t vertex_attributes_size);

void free_material(material* material);

GLenum get_gl_attribute_type(VERTEX_ATTRIB_TYPE type);

GLboolean get_gl_bool(bool value);

void set_uniforms_data_on_gl(uniform** uniforms, size_t length);

void set_uniform_data_on_gl(uniform* uniform);

#endif //CYNICAL_ENGINE_CYNICAL_GRAPHICS_H
