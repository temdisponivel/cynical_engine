//
// Created by Morpheus on 07-Oct-17.
//

#ifndef CYNICAL_ENGINE_CYNICAL_GRAPHICS_H
#define CYNICAL_ENGINE_CYNICAL_GRAPHICS_H

#include <cynical_collections.h>
#include <cynical_includes.h>

typedef struct texture_definition_s {
    char* file_name;
    GLenum min_filer;
    GLenum max_filer;
} texture_defition_t;

typedef struct texture_s {
    GLuint handle;
    vector2_t size;
} texture_t;

typedef struct shader_s {
    GLuint vertex_handle;
    GLuint fragment_handle;
    GLuint program_handle;
} shader_t;

typedef enum {
    VERTEX_ATTRIB_POS,
    VERTEX_ATTRIB_COLOR,
    VERTEX_ATTRIB_UV0,
} VERTEX_ATTRIB_TYPE_T;

typedef struct vertex_attribute_s {
    VERTEX_ATTRIB_TYPE_T type;
    GLint handle;
    char* name;
} vertex_attribute_t;

typedef struct vertex_attribute_defition_s {
    char* name;
    VERTEX_ATTRIB_TYPE_T type;
} vertex_attribute_defition_t;

typedef enum {
    UNIFORM_FLOAT,
    UNIFORM_VECTOR2,
    UNIFORM_VECTOR3,
    UNIFORM_VECTOR4,
    UNIFORM_MATRIX4X4,
    UNIFORM_TEXTURE,
} UNIFORM_DATA_TYPE;

typedef union uniform_data_u {
    float float_value;
    vector2_t vector2_value;
    vector3_t vector3_value;
    vector4_t vector4_value;
    matrix4x4_t matrix4x4_value;
    texture_t texture_value;
} uniform_data_t;

typedef enum {
    UNIFORM_TAG_MVP,
    USER_DEFINED,
} UNIFORM_TAG_T;

typedef struct uniform_definition_s {
    char* name;
    UNIFORM_DATA_TYPE data_type;
    uniform_data_t data;
    UNIFORM_TAG_T tag;
} uniform_definition_t;

typedef struct uniform_s {
    GLint handle;
    UNIFORM_DATA_TYPE type;
    uniform_data_t data;
    char* name;
    UNIFORM_TAG_T tag;
} uniform_t;

typedef struct material_s {
    uniform_t** uniforms;
    size_t uniform_size;
    vertex_attribute_t** attributes;
    size_t attribute_size;
    shader_t* shader;
} material_t;

typedef struct vertex_s {
    vector3_t position;
    vector4_t color;
    vector2_t uv0;
} vertex_t;

typedef struct mesh_s {
    vertex_t* vertices;
    size_t vertices_count;

    int* indices;
    size_t indices_count;

    GLuint vbo_handle;
    GLuint ibo_handle;
    GLuint vao_handle;

    material_t* material;
} mesh_t;

// ################# MESH #########################

mesh_t* make_mesh(vertex_t* vertices_data,
                  size_t vertices_count,
                  int* indices_data,
                  size_t indices_count);

void free_mesh(mesh_t* mesh);

void set_mesh_material(mesh_t* mesh, material_t* material);

void buff_mesh_data(mesh_t* mesh);

// ################# SHADER ########################

shader_t* make_shader(const char* vertex_source, const char* fragment_source);

void free_shader(shader_t* shader);

// ################# MATERIAL ########################

material_t* make_material(shader_t* shader,
                          uniform_definition_t* uniforms,
                          size_t uniforms_size,
                          vertex_attribute_defition_t* vertex_attributes,
                          size_t vertex_attributes_size);

void free_material(material_t* material);

uniform_t* get_uniform_by_tag(material_t* material, UNIFORM_TAG_T tag);

void rebuff_uniform(uniform_t* uniform);

vertex_attribute_t* find_vertex_attrib_by_type(material_t* material, VERTEX_ATTRIB_TYPE_T type);

// ################## TEXTURE ##########################

texture_t load_texture(texture_defition_t);

void free_texture(texture_t texture);

#endif //CYNICAL_ENGINE_CYNICAL_GRAPHICS_H
