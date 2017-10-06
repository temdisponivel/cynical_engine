#include "glew/glew.h"
#include <GLFW/glfw3.h>
#include "linmath/linmath.h"
#include "include/cynical_math.h"
#include <stdio.h>
#include <cynical_camera.h>

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

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    int shiftted = (mods & GLFW_MOD_SHIFT) == GLFW_MOD_SHIFT;

    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        if (key == GLFW_KEY_X) {
            triangle->rotation = quaternion_rotate(triangle->rotation, shiftted ? -10 : 10, vector3_right());
        }

        if (key == GLFW_KEY_Y) {
            triangle->rotation = quaternion_rotate(triangle->rotation, shiftted ? -10 : 10, vector3_up());
        }

        if (key == GLFW_KEY_Z) {
            triangle->rotation = quaternion_rotate(triangle->rotation, shiftted ? -10 : 10, vector3_forward());
        }

        if (key == GLFW_KEY_S) {
            triangle->scale = vector3_scale(triangle->scale, shiftted ? .5f : 2.0f);
        }

        if (key == GLFW_KEY_RIGHT) {
            triangle->position = vector3_add(triangle->position, vector3_right());
        }

        if (key == GLFW_KEY_LEFT) {
            triangle->position = vector3_add(triangle->position, vector3_left());
        }

        if (key == GLFW_KEY_UP) {
            triangle->position = vector3_add(triangle->position, vector3_up());
        }

        if (key == GLFW_KEY_DOWN) {
            triangle->position = vector3_add(triangle->position, vector3_down());
        }

        if (key == GLFW_KEY_C) {
            free_camera(game_camera);

            //matrix4x4_ortho(projection, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
            float ratio = width / (float) height;
            game_camera = make_ortho_camera(-ratio, ratio, -1.f, 1.f, 1, -10000);
        }
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    game_camera->entity->transform->position.z += yoffset;
}

int main(void) {

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
    glfwSetKeyCallback(window, key_callback);
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

    float ratio;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float) height;
    glViewport(0, 0, width, height);

    game_camera = make_perspective_camera(90, ratio, 0, -1000);
    triangle = make_transform();
    matrix4x4 mvp;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        transform_update_matrix(triangle);
        camera_update_matrix(game_camera);

        set_matrix4x4_identity(&mvp);
        camera_get_model_view(&mvp, game_camera);
        matrix4x4_mul(&mvp, &mvp, triangle->matrix);

        float mvp_data[4][4];
        get_gl_matrix4x4(mvp_data, &mvp);
        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp_data);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}