#include "glew/glew.h"
#include <GLFW/glfw3.h>
#include "linmath/linmath.h"
#include "include/cynical_math.h"
#include <stdio.h>
#include <cynical_camera.h>
#include <cynical_log.h>
#include <cynical_input.h>

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

static void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

transform* triangle;
camera* game_camera;

void handle_input() {

    int shiftted = false;

    if (is_key_pressed(KEY_ESCAPE)) {
        glfwSetWindowShouldClose(NULL, GLFW_TRUE);
    }

    if (is_key_pressed(MOUSE_BUTTON_LEFT)) {
        triangle->rotation = quaternion_rotate(triangle->rotation, shiftted ? -10 : 10, vector3_right());
    }

    if (is_key_pressed(MOUSE_BUTTON_MIDDLE)) {
        triangle->rotation = quaternion_rotate(triangle->rotation, shiftted ? -10 : 10, vector3_up());
    }

    if (is_key_pressed(MOUSE_BUTTON_RIGHT)) {
        triangle->rotation = quaternion_rotate(triangle->rotation, shiftted ? -10 : 10, vector3_forward());
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

    if (is_key_pressed(KEY_C)) {
        free_camera(game_camera);

        //matrix4x4_ortho(projection, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        int width, height;
        glfwGetFramebufferSize(NULL, &width, &height);
        float ratio = width / (float) height;
        game_camera = make_ortho_camera(-ratio, ratio, -1.f, 1.f, 1, -10000);
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    game_camera->entity->transform->position.z += yoffset;
}

void test_matrix_revert();

int main(void) {

    test_matrix_revert();

    GLFWwindow* window;
    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
    GLint mvp_location, vpos_location, vcol_location;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetScrollCallback(window, scroll_callback);
    glfwMakeContextCurrent(window);
    glewInit();
    glfwSwapInterval(1);
    // NOTE: OpenGL error checks have been omitted for brevity
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
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
                          sizeof(float) * 5, (void*) 0);
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                          sizeof(float) * 5, (void*) (sizeof(float) * 2));

    glfwSwapInterval(1);

    float ratio;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float) height;
    glViewport(0, 0, width, height);

    game_camera = make_perspective_camera(90, ratio, 0.0001f, -10000);
    //game_camera = make_ortho_camera(-ratio, ratio, -1.f, 1.f, 0.0001f, -10000);
    triangle = make_transform();
    matrix4x4 mvp;

    main_input_state = make_input_state();
    main_input_state->invert_y = true;
    input_window = window;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        handle_input();

        transform_update_matrix(triangle);
        camera_update_matrix(game_camera);

        camera_get_vp_matrix(&mvp, game_camera);
        matrix4x4_mul(&mvp, &mvp, triangle->matrix);

        float mvp_data[4][4];
        get_gl_matrix4x4(mvp_data, &mvp);
        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp_data);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();

        update_input_state();

        //triangle->position = make_vector3(main_input_state->mouse_position.x, main_input_state->mouse_position.y, 0);
        vector3 m = make_vector3(main_input_state->mouse_position.x, main_input_state->mouse_position.y, 1.f);

        vector3 fake_pos = make_vector3(1, 1, -10000);
        vector2 screen_mouse = camera_world_to_screen_coord(game_camera, fake_pos);
        vector3 screen_pos = make_vector3(screen_mouse.x, screen_mouse.y, 1.f);

        vector3 new_world_pos = camera_screen_to_world_coord(game_camera, screen_pos);

        triangle->position = screen_pos;

        //glfwtime
    }
    free_input_state(main_input_state);
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void compare(matrix4x4 matrix, mat4x4 mat);

void test_matrix_revert() {
    const float ratio = 640 / 480.f;
    matrix4x4 projection;
    matrix4x4_perspective(&projection, 90, ratio, 0.00001, -10000);

    mat4x4 mat_proj;
    mat4x4_perspective(mat_proj, to_rad(90), ratio, 0.00001, -10000);

    MESSAGE("COMPARE PERSPECTIVE");
    compare(projection, mat_proj);

    mat4x4 mat_project_invertion;
    mat4x4_invert(mat_project_invertion, mat_proj);

    matrix4x4 invertion_result;
    matrix4x4_invert(&invertion_result, &projection);

    MESSAGE("COMPARE INVERTION");
    compare(invertion_result, mat_project_invertion);
}

void compare(matrix4x4 matrix, mat4x4 mat) {
    ASSERT_BREAK(matrix.xx == mat[0][0]);
    ASSERT_BREAK(matrix.xy == mat[0][1]);
    ASSERT_BREAK(matrix.xz == mat[0][2]);
    ASSERT_BREAK(matrix.xw == mat[0][3]);

    ASSERT_BREAK(matrix.yx == mat[1][0]);
    ASSERT_BREAK(matrix.yy == mat[1][1]);
    ASSERT_BREAK(matrix.yz == mat[1][2]);
    ASSERT_BREAK(matrix.yw == mat[1][3]);

    ASSERT_BREAK(matrix.zx == mat[2][0]);
    ASSERT_BREAK(matrix.zy == mat[2][1]);
    ASSERT_BREAK(matrix.zz == mat[2][2]);
    ASSERT_BREAK(matrix.zw == mat[2][3]);

    ASSERT_BREAK(matrix.wx == mat[3][0]);
    ASSERT_BREAK(matrix.wy == mat[3][1]);
    ASSERT_BREAK(matrix.wz == mat[3][2]);
    ASSERT_BREAK(matrix.ww == mat[3][3]);
}