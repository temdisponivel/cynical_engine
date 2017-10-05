#include "glew/glew.h"
#include <GLFW/glfw3.h>
#include "linmath/linmath.h"
#include "cynical_math.h"
#include <stdlib.h>
#include <stdio.h>

static const struct {
    float x, y;
    float r, g, b;
} vertices[3] =
        {
                {-0.5f, -0.5f, 1.f, 0.f, 0.f},
                {0.5f,  -0.5f, 0.f, 1.f, 0.f},
                {0,   0.5f,  0.f, 0.f, 1.f}
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

typedef struct {
    mat4x4 trans;
    mat4x4 rotation;
    mat4x4 scale;

    mat4x4 transform_matrix;
} transform;

transform triangle_trans;

vec3 center, eye, up;
mat4x4 projection, view, mvp;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    int shiftted = (mods & GLFW_MOD_SHIFT) == GLFW_MOD_SHIFT;

    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        if (key == GLFW_KEY_X) {

            mat4x4 rot;
            mat4x4_identity(rot);
            mat4x4_rotate_X(rot, rot, to_rad(shiftted ? -30 : 30));
            mat4x4_mul(triangle_trans.rotation, triangle_trans.rotation, rot);

        }

        if (key == GLFW_KEY_Y) {

            mat4x4 rot;
            mat4x4_identity(rot);
            mat4x4_rotate_Y(rot, rot, to_rad(shiftted ? -30 : 30));
            mat4x4_mul(triangle_trans.rotation, triangle_trans.rotation, rot);
        }

        if (key == GLFW_KEY_Z) {

            mat4x4 rot;
            mat4x4_identity(rot);
            mat4x4_rotate_Z(rot, rot, to_rad(shiftted ? -30 : 30));
            mat4x4_mul(triangle_trans.rotation, triangle_trans.rotation, rot);
        }

        if (key == GLFW_KEY_S) {
            mat4x4 scale;
            mat4x4_identity(scale);
            float scaleFactor = shiftted ? 0.5f : 2.0f;
            mat4x4_scale_aniso(scale, scale, scaleFactor, scaleFactor, scaleFactor);
            mat4x4_mul(triangle_trans.scale, triangle_trans.scale, scale);
        }

        if (key == GLFW_KEY_RIGHT) {
            mat4x4 translate;
            mat4x4_identity(translate);

            mat4x4_translate(translate, 1, 0, 0);
            mat4x4_mul(triangle_trans.trans, triangle_trans.trans, translate);
        }

        if (key == GLFW_KEY_LEFT) {
            mat4x4 translate;
            mat4x4_identity(translate);

            mat4x4_translate(translate, -1, 0, 0);
            mat4x4_mul(triangle_trans.trans, triangle_trans.trans, translate);
        }
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    eye[0] += yoffset;
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

    center[0] = 10000;
    center[1] = 0;
    center[2] = 0;

    eye[0] = 0;
    eye[1] = 0;
    eye[2] = 0;

    up[0] = 0;
    up[1] = 1;
    up[2] = 0;

    mat4x4_identity(triangle_trans.rotation);
    mat4x4_identity(triangle_trans.scale);
    mat4x4_identity(triangle_trans.trans);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        mat4x4_identity(triangle_trans.transform_matrix);
        mat4x4_mul(triangle_trans.transform_matrix, triangle_trans.scale, triangle_trans.rotation);
        mat4x4_mul(triangle_trans.transform_matrix, triangle_trans.transform_matrix, triangle_trans.trans);

        mat4x4_identity(projection);
        mat4x4_perspective(projection, 90, ratio, 0, -1000);

        mat4x4_identity(view);
        mat4x4_look_at(view, eye, center, up);

        //mat4x4_ortho(projection, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_identity(mvp);
        mat4x4_mul(mvp, projection, view);
        mat4x4_mul(mvp, mvp, triangle_trans.transform_matrix);

        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}