#define STB_IMAGE_IMPLEMENTATION

#include <cynical_includes.h>
#include <cynical_math.h>
#include <cynical_camera.h>
#include <cynical_video.h>
#include <cynical_engine.h>
#include <cynical_memory.h>
#include <cynical_graphics.h>
#include <cynical_render.h>
#include <cynical_input.h>
#include <cynical_time.h>

#include "dependencies/include/linmath/linmath.h"

vertex_t plane[] = {
        // POSITION         // COLOR            // UV
        -0.5f, -0.5f, 0.f, 1.f, 0.f, 0.f, 1.0f, 0, 1, // bottom left
        -0.5f, 0.5f, 0.f, 0.f, 1.f, 0.f, 1.0f,  0, 0,// top left
        0.5f, 0.5f, 0.f, 0.f, 0.f, 1.f, 1.0f,   1, 1,// top right
        0.5f, -0.5f, 0.f, 0.f, 1.f, 1.f, 1.0f,  1, 0,// bottom right
};

vertex_t box[] = {
        // POSITION         // COLOR
        -0.5f, -0.5f, 0.f, 1.f, 0.f, 0.f, 1.0f,
        -0.5f, 0.5f, 0.f, 0.f, 1.f, 0.f, 1.0f,  // FRONT-FACE
        0.5f, 0.5f, 0.f, 0.f, 0.f, 1.f, 1.0f,
        0.5f, -0.5f, 0.f, 0.f, 1.f, 1.f, 1.0f,

        -0.5f, -0.5f, 1.f, 1.f, 0.f, 0.f, 1.0f,
        -0.5f, 0.5f, 1.f, 0.f, 1.f, 0.f, 1.0f,
        0.5f, 0.5f, 1.f, 0.f, 0.f, 1.f, 1.0f,   // BACK-FACE
        0.5f, -0.5f, 1.f, 0.f, 1.f, 1.f, 1.0f,

        0.5f, -0.5f, 0.f, 1.f, 0.f, 0.f, 1.0f,
        0.5f, 0.5f, 0.f, 0.f, 1.f, 0.f, 1.0f,
        0.5f, 0.5f, 1.f, 0.f, 0.f, 1.f, 1.0f,   // RIGHT-FACE
        0.5f, -0.5f, 1.f, 0.f, 1.f, 1.f, 1.0f,

        -0.5f, -0.5f, 0.f, 1.f, 0.f, 0.f, 1.0f,
        -0.5f, 0.5f, 0.f, 0.f, 1.f, 0.f, 1.0f,
        -0.5f, 0.5f, 1.f, 0.f, 0.f, 1.f, 1.0f,    // LEFT-FACE
        -0.5f, -0.5f, 1.f, 0.f, 1.f, 1.f, 1.0f,

        -0.5f, 0.5f, 0.f, 1.f, 0.f, 0.f, 1.0f,
        -0.5f, 0.5f, 1.f, 0.f, 1.f, 0.f, 1.0f,
        0.5f, 0.5f, 1.f, 0.f, 0.f, 1.f, 1.0f,   // TOP-FACE
        0.5f, 0.5f, 0.f, 0.f, 1.f, 1.f, 1.0f,

        -0.5f, -0.5f, 0.f, 1.f, 0.f, 0.f, 1.0f,
        -0.5f, -0.5f, 1.f, 0.f, 1.f, 0.f, 1.0f,
        0.5f, -0.5f, 1.f, 0.f, 0.f, 1.f, 1.0f,    // BOTTOM-FACE
        0.5f, -0.5f, 0.f, 0.f, 1.f, 1.f, 1.0f,
};

int quad_indices[] = {
        0, 1, 2, 2, 3, 0
};

int cube_indices[] = {
        0, 1, 2, 2, 3, 0,
        0, 1, 2, 2, 3, 0,
};

static const char* vertex_shader_text =
        "#version 400\n"
                "uniform mat4 MVP;\n"
                "in vec3 vPos;\n"
                "in vec4 vCol;\n"
                "in vec2 vUv;\n"
                "out vec4 color;\n"
                "out vec2 uv;\n"
                "void main()\n"
                "{\n"
                "    gl_Position = MVP * vec4(vPos, 1.0);\n"
                "    color = vCol;\n"
                "    uv = vUv;\n"
                "}\n";
static const char* fragment_shader_text =
                "#version 400\n"
                "in vec4 color;\n"
                "in vec2 uv;\n"
                "uniform sampler2D white;\n"
                "out vec4 result_color;\n"
                "void main()\n"
                "{\n"
                "    result_color = texture(white, uv);\n"
                "}\n";

void setup();

void draw_scene();

void update();

void handle_input();

transform_t* quad_parent;
transform_t* quad;
transform_t* cube;
camera_t* game_camera;

matrix4x4_t mvp;
shader_t* main_shader;
material_t* quad_material;
material_t* cube_material;

mesh_t* quad_mesh;
mesh_t* cube_mesh;

int main(void) {
    if (!engine_init(&update, &draw_scene)) {
        ERROR(engine_error_description);
        exit(EXIT_FAILURE);
    }

    setup();

    run_loop();

    free_shader(main_shader);
    free_material(quad_material);
    free_mesh(quad_mesh);

    engine_release();
    exit(EXIT_SUCCESS);
}

void setup() {

    quad = make_transform();
    quad->position = make_vector3(0, -1, 5);

    cube = make_transform();
    cube->position.z = -10;

    vector2_t frame_buffer = main_window->frame_buffer_size;
    float ratio = frame_buffer.x / frame_buffer.y;

    game_camera = make_perspective_camera(60, ratio, .01f, 10);


    main_shader = make_shader(vertex_shader_text, fragment_shader_text);
    ASSERT(main_shader);

    vertex_attribute_defition_t pos_attribute;
    pos_attribute.type = VERTEX_ATTRIB_POS;
    pos_attribute.name = "vPos";

    vertex_attribute_defition_t col_attribute;
    col_attribute.type = VERTEX_ATTRIB_COLOR;
    col_attribute.name = "vCol";

    vertex_attribute_defition_t uv_attribute;
    uv_attribute.type = VERTEX_ATTRIB_UV0;
    uv_attribute.name = "vUv";

    uniform_definition_t mvp_attribute;
    mvp_attribute.name = "MVP";
    mvp_attribute.data_type = UNIFORM_MATRIX4X4;
    mvp_attribute.data.matrix4x4_value = mvp;
    mvp_attribute.tag = UNIFORM_TAG_MVP;


    texture_defition_t def;
    def.file_name = "raw/white.png";
    def.min_filer = GL_LINEAR;
    def.min_filer = GL_NEAREST;

    uniform_definition_t white_attribute;
    white_attribute.name = "white";
    white_attribute.data_type = UNIFORM_TEXTURE;
    white_attribute.data.texture_value = load_texture(def);
    white_attribute.tag = USER_DEFINED;

    vertex_attribute_defition_t attributes[] = {pos_attribute, col_attribute, uv_attribute};
    uniform_definition_t uniforms[] = {mvp_attribute, white_attribute};
    quad_material = make_material(main_shader, uniforms, 2, attributes, 3);
    ASSERT(quad_material);

    cube_material = make_material(main_shader, uniforms, 2, attributes, 3);
    ASSERT(cube_material);

    size_t quad_indices_count = 5;
    size_t cube_indices_count = 30;

    quad_mesh = make_mesh(
            plane,
            4,
            quad_indices,
            quad_indices_count);

    ASSERT(quad_mesh);

    cube_mesh = make_mesh(
            box,
            32,
            cube_indices,
            cube_indices_count);

    ASSERT(cube_mesh);

    set_mesh_material(quad_mesh, quad_material);
    set_mesh_material(cube_mesh, cube_material);
}

void update_transforms() {
    transform_update_matrix(game_camera->transform);
    transform_update_direction_vectors(game_camera->transform);

    transform_update_matrix(quad);
    transform_update_direction_vectors(quad);
}

void update() {
    handle_input();
}

void draw_scene() {
    render_start_draw(game_camera);

    render_bind_material(quad_material);
    transform_update_matrix(quad);
    render_draw(quad, quad_mesh);

//    render_bind_material(cube_material);
//    transform_update_matrix(cube);
//    render_draw(cube, cube_mesh);

    render_end_draw();
}

void move_camera();

void validate_look_at();

void handle_input() {
    move_camera();
    //validate_look_at();
}

void move_camera() {
    transform_t* transform = game_camera->transform;

    float rotation_velocity = 20 * get_delta_time();
    float velocity = 10 * get_delta_time();

    update_transforms();

    if (is_key_pressed(KEY_W)) {
        transform->position = vector3_add(transform->position, vector3_scale(transform->forward, velocity));
    }

    update_transforms();

    if (is_key_pressed(KEY_S)) {
        transform->position = vector3_add(transform->position, vector3_scale(transform->forward, -velocity));
    }

    update_transforms();

    if (is_key_pressed(KEY_D)) {
        transform->position = vector3_add(transform->position, vector3_scale(transform->right, -velocity));
    }

    update_transforms();

    if (is_key_pressed(KEY_A)) {
        transform->position = vector3_add(transform->position, vector3_scale(transform->right, velocity));
    }

    update_transforms();

    if (is_key_pressed(KEY_UP)) {
        transform->rotation = quaternion_rotate(transform->rotation, rotation_velocity, vector3_right());
    }

    update_transforms();

    if (is_key_pressed(KEY_DOWN)) {
        transform->rotation = quaternion_rotate(transform->rotation, -rotation_velocity, vector3_right());
    }

    update_transforms();

    if (is_key_pressed(KEY_RIGHT)) {
        transform->rotation = quaternion_rotate(transform->rotation, -rotation_velocity, vector3_up());
    }

    update_transforms();

    if (is_key_pressed(KEY_LEFT)) {
        transform->rotation = quaternion_rotate(transform->rotation, rotation_velocity, vector3_up());
    }

    update_transforms();

    if (is_key_pressed(KEY_SPACE)) {
//          transform_look_at(transform, quad->position);
//        transform_rotate_around(transform, quad->position, vector3_up(), rotation_velocity * 5);

        //transform_set_up(transform, vector3_forward());
        vector3_t direction = transform_vector3_direction(quad, vector3_scale(vector3_backward(), 10));
        transform->position = vector3_add(transform->position, direction);
    }

    update_transforms();
}

void validate_look_at() {
    matrix4x4_t* look_at = make_matrix4x4();
    mat4x4 look_at_mat;

    set_matrix4x4_identity(look_at);
    matrix4x4_look_at(look_at, make_vector3(10, -50, 300), vector3_right(), vector3_up());

    mat4x4_identity(look_at_mat);
    vec3 eye;
    eye[0] = 10;
    eye[1] = -50;
    eye[2] = 300;

    vec3 center;
    center[0] = 1;
    center[1] = 0;
    center[2] = 0;

    vec3 up;
    up[0] = 0;
    up[1] = 1;
    up[2] = 0;
    mat4x4_look_at(look_at_mat, eye, center, up);

    matrix4x4_t* converted = make_matrix4x4();
    set_matrix4x4_from_gl(converted, look_at_mat);
    ASSERT(matrix4x4_compare(look_at, converted));
}