#include "glew/glew.h"
#include <GLFW/glfw3.h>
#include "linmath/linmath.h"
#include "include/cynical_math.h"
#include <stdio.h>
#include <cynical_camera.h>
#include <cynical_log.h>
#include <cynical_input.h>
#include <cynical_time.h>
#include <cynical_video.h>
#include <cynical_engine.h>

static const struct {
    float x, y;
    float r, g, b;
} vertices[3] =
        {
                {-0.5f, -0.5f, 1.f, 0.f, 0.f},
                {0.5f,  -0.5f, 0.f, 1.f, 0.f},
                {0,     0.5f,  0.f, 0.f, 1.f}
        };
static const char* vertex_shader_text =
        "uniform mat4 MVP;\n"
                "attribute vec3 vCol;\n"
                "attribute vec2 vPos;\n"
                "varying vec3 color;\n"
                "void main()\n"
                "{\n"
                "    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
                "    color = vCol;\n"
                "}\n";
static const char* fragment_shader_text =
        "varying vec3 color;\n"
                "void main()\n"
                "{\n"
                "    gl_FragColor = vec4(color, 1.0);\n"
                "}\n";

static void error_callback(int error, const char* description);

void setup();

void update();

void draw();

void handle_input();

transform* triangle;
camera* game_camera;

GLuint vertex_buffer, vertex_shader, fragment_shader, program;
GLint mvp_location, vpos_location, vcol_location;
matrix4x4 mvp;

int main(void) {

    if (!engine_init(&update, &draw)) {
        ERROR(engine_error_description);
        exit(EXIT_FAILURE);
    }

    setup();

    run_loop();

    engine_release();
    exit(EXIT_SUCCESS);
}

void setup() {

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");


    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*) 0);

    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*) (sizeof(float) * 2));

    vector2 frame_buffer = main_window->frame_buffer_size;

    game_camera = make_perspective_camera(90, frame_buffer.x / frame_buffer.y, 0.0001f, -10000);
    //game_camera = make_ortho_camera(-ratio, ratio, -1.f, 1.f, 0.0001f, -10000);

    triangle = make_transform();
    game_camera->transform->position.z = -5;
}

void update() {
    handle_input();
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    transform_update_matrix(triangle);
    camera_update_matrix(game_camera);

    camera_get_vp_matrix(&mvp, game_camera);
    matrix4x4_mul(&mvp, &mvp, triangle->matrix);

    float mvp_data[4][4];
    get_gl_matrix4x4(mvp_data, &mvp);
    glUseProgram(program);
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp_data);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(main_window->glfw_main_window);
}

void handle_input() {

    int shiftted = false;

    float velocity = 10.f * get_delta_time();
    if (shiftted) {
        velocity = -velocity;
    }

    if (is_key_pressed(KEY_ESCAPE)) {
        glfwSetWindowShouldClose(NULL, GLFW_TRUE);
    }

    if (is_key_pressed(MOUSE_BUTTON_LEFT)) {
        triangle->rotation = quaternion_rotate(triangle->rotation, velocity, vector3_right());
    }

    if (is_key_pressed(MOUSE_BUTTON_MIDDLE)) {
        triangle->rotation = quaternion_rotate(triangle->rotation, velocity, vector3_up());
    }

    if (is_key_pressed(MOUSE_BUTTON_RIGHT)) {
        triangle->rotation = quaternion_rotate(triangle->rotation, velocity, vector3_forward());
    }

    if (is_key_pressed(KEY_RIGHT)) {
        triangle->scale = vector3_scale(triangle->scale, shiftted ? .5f : 2.0f);
    }

    if (is_key_pressed(KEY_RIGHT)) {
        triangle->position = vector3_add(triangle->position, vector3_right());
    }

    if (is_key_pressed(KEY_LEFT)) {
        triangle->position = vector3_add(triangle->position, vector3_left());
    }

    if (is_key_pressed(KEY_UP)) {
        triangle->position = vector3_add(triangle->position, vector3_up());
    }

    if (is_key_pressed(KEY_DOWN)) {
        triangle->position = vector3_add(triangle->position, vector3_down());
    }

    if (is_key_pressed(KEY_KP_ADD)) {
        set_time_scale(get_time_scale() + .1f);
    } else if (is_key_pressed(KEY_KP_SUBTRACT)) {
        set_time_scale(get_time_scale() - .1f);
    }

    vector2 scroll = get_mouse_delta();
    VECTOR2_PRINT(scroll);
    game_camera->transform->position = vector3_add(vector3_zero(), make_vector3_vec2(scroll, -5));
    VECTOR3_PRINT(game_camera->transform->position);

    if (is_key_pressed(KEY_C)) {
        free_camera(game_camera);

        //matrix4x4_ortho(projection, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        int width, height;
        glfwGetFramebufferSize(NULL, &width, &height);
        float ratio = width / (float) height;
        game_camera = make_ortho_camera(-ratio, ratio, -1.f, 1.f, 1, -10000);
    }
}

static void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}