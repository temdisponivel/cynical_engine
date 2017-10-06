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

vector3 center, eye, up;
matrix4x4 projection, view, mvp;

transform* triangle;

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
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    eye.z += yoffset;
}

void test_math_lib();

int main(void) {

    center.x = 0;
    center.y = 0;
    center.z = 10000;

    eye.x = 0;
    eye.y = 0;
    eye.z = -10;

    up.x = 0;
    up.y = 1;
    up.z = 0;

    test_math_lib();

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

    triangle = make_transform();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        transform_update_matrix(triangle);

        set_matrix4x4_identity(&projection);
        matrix4x4_perspective(&projection, 90, ratio, 0, -1000);

        set_matrix4x4_identity(&view);
        matrix4x4_look_at(&view, eye, center, up);

        //matrix4x4_ortho(projection, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        set_matrix4x4_identity(&mvp);
        matrix4x4_mul(&mvp, &projection, &view);
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

void assert(matrix4x4* matrix, mat4x4 mat);

void assert_data(float data[4][4], float mat[4][4]);

void test_math_lib() {

    matrix4x4 test_matrix;
    mat4x4 mat;

    set_matrix4x4_identity(&test_matrix);
    mat4x4_identity(mat);

    assert(&test_matrix, mat);

    matrix4x4 translate_matrix;
    matrix4x4_translate(&translate_matrix, make_vector3(10, -3.5f, -780.0f));

    mat4x4 mat_translate;
    mat4x4_translate(mat_translate, 10, -3.5f, -780.0f);

    assert(&translate_matrix, mat_translate);

    mat4x4 mat_translated;
    mat4x4_mul(mat_translated, mat, mat_translate);

    matrix4x4 matrix_translated;
    matrix4x4_mul(&matrix_translated, &test_matrix, &translate_matrix);

    assert(&matrix_translated, mat_translate);

    float data[4][4];
    get_gl_matrix4x4(data, &matrix_translated);

    assert_data(data, mat_translated);

    matrix4x4 to_translate_in_place;
    set_matrix4x4_identity(&to_translate_in_place);
    matrix4x4_translate_in_place(&to_translate_in_place, make_vector3(10, -3.5f, -780.0f));

    mat4x4 mat_to_translate_in_place;
    mat4x4_identity(mat_to_translate_in_place);
    mat4x4_translate_in_place(mat_to_translate_in_place, 10, -3.5f, -780.0f);

    assert(&to_translate_in_place, mat_to_translate_in_place);

    matrix4x4 look_at;
    set_matrix4x4_identity(&look_at);
    matrix4x4_look_at(&look_at, eye, center, up);

    mat4x4 old_look_at;
    mat4x4_identity(old_look_at);

    vec3 veye;
    veye[0] = eye.x;
    veye[1] = eye.y;
    veye[2] = eye.z;

    vec3 vcenter;
    vcenter[0] = center.x;
    vcenter[1] = center.y;
    vcenter[2] = center.z;

    vec3 vup;
    vup[0] = up.x;
    vup[1] = up.y;
    vup[2] = up.z;

    mat4x4_look_at(old_look_at, veye, vcenter, vup);

    assert(&look_at, old_look_at);

    float ratio;
    ratio = 800 / (float) 600;

    matrix4x4 matrix_proj;
    set_matrix4x4_identity(&matrix_proj);
    matrix4x4_perspective(&matrix_proj, 90, ratio, 0, -1000);

    mat4x4 mat_proj;
    mat4x4_identity(mat_proj);
    mat4x4_perspective(mat_proj, 90, ratio, 0, -1000);

    assert(&matrix_proj, mat_proj);

    set_matrix4x4_from_gl(&matrix_proj, mat_proj);

    mat4x4 d;
    get_gl_matrix4x4(d, &matrix_proj);
    assert_data(d, mat_proj);
}

void assert(matrix4x4* matrix, mat4x4 mat) {
    if (matrix->xx != mat[0][0]) {
        printf("matrix xx is different! \n");
    };

    if (matrix->xy != mat[0][1]) {
        printf("matrix xy is different! \n");
    };

    if (matrix->xz != mat[0][2]) {
        printf("matrix xz is different! \n");
    };

    if (matrix->xw != mat[0][3]) {
        printf("matrix xw is different! \n");
    };

    if (matrix->yx != mat[1][0]) {
        printf("matrix yx is different! \n");
    };

    if (matrix->yy != mat[1][1]) {
        printf("matrix yy is different! \n");
    };

    if (matrix->yz != mat[1][2]) {
        printf("matrix yz is different! \n");
    };

    if (matrix->yw != mat[1][3]) {
        printf("matrix yw is different! \n");
    };

    if (matrix->zx != mat[2][0]) {
        printf("matrix zx is different! \n");
    };

    if (matrix->zy != mat[2][1]) {
        printf("matrix.zy is different! \n");
    };

    if (matrix->zz != mat[2][2]) {
        printf("matrix zz is different! \n");
    };

    if (matrix->zw != mat[2][3]) {
        printf("matrix zw is different! \n");
    };

    if (matrix->wx != mat[3][0]) {
        printf("matrix wx is different! \n");
    };

    if (matrix->wy != mat[3][1]) {
        printf("matrix wy is different! \n");
    };

    if (matrix->wz != mat[3][2]) {
        printf("matrix wz is different! \n");
    };

    if (matrix->ww != mat[3][3]) {
        printf("matrix ww is different! \n");
    };
}

void assert_data(float data[4][4], float mat[4][4]) {
    if (data[0][0] != mat[0][0]) {
        printf("data is different at: [0][0]! \n");
    }
    if (data[0][1] != mat[0][1]) {
        printf("data is different at: [0][1]! \n");
    }
    if (data[0][2] != mat[0][2]) {
        printf("data is different at: [0][2]! \n");
    }
    if (data[0][3] != mat[0][3]) {
        printf("data is different at: [0][3]! \n");
    }


    if (data[1][0] != mat[1][0]) {
        printf("data is different at: [1][0]! \n");
    }
    if (data[1][1] != mat[1][1]) {
        printf("data is different at: [1][1]! \n");
    }
    if (data[1][2] != mat[1][2]) {
        printf("data is different at: [1][2]! \n");
    }
    if (data[1][3] != mat[1][3]) {
        printf("data is different at: [1][3]! \n");
    }


    if (data[2][0] != mat[2][0]) {
        printf("data is different at: [2][0]! \n");
    }
    if (data[2][1] != mat[2][1]) {
        printf("data is different at: [2][1]! \n");
    }
    if (data[2][2] != mat[2][2]) {
        printf("data is different at: [2][2]! \n");
    }
    if (data[2][3] != mat[2][3]) {
        printf("data is different at: [2][3]! \n");
    }


    if (data[3][0] != mat[3][0]) {
        printf("data is different at: [3][0]! \n");
    }
    if (data[3][1] != mat[3][1]) {
        printf("data is different at: [3][1]! \n");
    }
    if (data[3][2] != mat[3][2]) {
        printf("data is different at: [3][2]! \n");
    }
    if (data[3][3] != mat[3][3]) {
        printf("data is different at: [3][3]! \n");
    }
}