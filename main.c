#include <cynical_includes.h>
#include <cynical_math.h>
#include <cynical_camera.h>
#include <cynical_video.h>
#include <cynical_engine.h>
#include <cynical_memory.h>
#include <cynical_graphics.h>
#include <cynical_render.h>


vertex_t vertices[] = {
        // POSITION         // COLOR
        -0.5f, -0.5f, 0.f, 1.f, 0.f, 0.f, 1.0f, // bottom left
        -0.5f, 0.5f, 0.f, 0.f, 1.f, 0.f, 1.0f, // top left
        0.5f, 0.5f, 0.f, 0.f, 0.f, 1.f, 1.0f, // top right
        0.5f, -0.5f, 0.f, 0.f, 1.f, 1.f, 1.0f, // bottom right
};

int indices[] = {
        0, 1, 2, 2, 3, 0
};

static const char* vertex_shader_text =
        "attribute vec3 vPos;\n"
                "attribute vec4 vCol;\n"
                "uniform mat4 MVP;\n"
                "varying vec4 color;\n"
                "void main()\n"
                "{\n"
                "    gl_Position = MVP * vec4(vPos, 1.0);\n"
                "    color = vCol;\n"
                "}\n";
static const char* fragment_shader_text =
        "varying vec4 color;\n"
                "uniform mat4 MVP;\n"
                "void main()\n"
                "{\n"
                "    gl_FragColor = color;\n"
                "}\n";

void setup();

void draw_scene();

void update();

transform_t* triangle;
camera_t* game_camera;

matrix4x4_t mvp;
shader_t* main_shader;
material_t* main_material;
mesh_t* main_mesh;

int main(void) {

    if (!engine_init(&update, &draw_scene)) {
        ERROR(engine_error_description);
        exit(EXIT_FAILURE);
    }

    setup();

    run_loop();

    free_shader(main_shader);
    free_material(main_material);
    free_mesh(main_mesh);

    engine_release();
    exit(EXIT_SUCCESS);
}

void setup() {

    triangle = make_transform();

    vector2_t frame_buffer = main_window->frame_buffer_size;
    float ratio = frame_buffer.x / frame_buffer.y;
    game_camera = make_ortho_camera(-ratio, ratio, -1.f, 1.f, 0.0001f, -10000);

    main_shader = make_shader(vertex_shader_text, fragment_shader_text);
    ASSERT(main_shader);

    vertex_attribute_defition_t pos_attribute;
    pos_attribute.type = VERTEX_ATTRIB_POS;
    pos_attribute.name = "vPos";

    vertex_attribute_defition_t col_attribute;
    col_attribute.type = VERTEX_ATTRIB_COLOR;
    col_attribute.name = "vCol";

    uniform_definition_t mvp_attribute;
    mvp_attribute.name = "MVP";
    mvp_attribute.data_type = UNIFORM_MATRIX4X4;
    mvp_attribute.data.matrix4x4_value = mvp;
    mvp_attribute.tag = UNIFORM_TAG_MVP;

    vertex_attribute_defition_t attributes[] = {pos_attribute, col_attribute};
    uniform_definition_t uniforms[] = {mvp_attribute};
    main_material = make_material(main_shader, uniforms, 1, attributes, 2);
    ASSERT(main_material);

    int* indices_array = indices;
    size_t indices_count = 5;

    main_mesh = make_mesh(
            vertices,
            4,
            indices_array,
            indices_count);

    ASSERT(main_mesh);

    set_mesh_material(main_mesh, main_material);

    render_bind_material(main_material);
}

void update() {
    //handle_input();
}

void draw_scene() {
    render_start_draw(game_camera);
    render_bind_material(main_material);
    transform_update_matrix(triangle);
    render_draw(triangle, main_mesh);
    render_end_draw();
}