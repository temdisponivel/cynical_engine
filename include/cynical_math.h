//
// Created by Morpheus on 04-Oct-17.
//

#ifndef CYNICAL_ENGINE_CYNICAL_MATH_H
#define CYNICAL_ENGINE_CYNICAL_MATH_H

#include <malloc.h>
#include <cynical_debug.h>

#define false 0
#define true 1

typedef short bool_t;

typedef struct vector2_s {
    float x;
    float y;
} vector2_t;

typedef struct vector3_s {
    float x;
    float y;
    float z;
} vector3_t;

typedef struct vector4_s {
    float x;
    float y;
    float z;
    float w;
} vector4_t;

typedef struct matrix4x4_s {
    float xx;
    float xy;
    float xz;
    float xw;

    float yx;
    float yy;
    float yz;
    float yw;

    float zx;
    float zy;
    float zz;
    float zw;

    float wx;
    float wy;
    float wz;
    float ww;
} matrix4x4_t;

typedef struct quaternion_s {
    float x;
    float y;
    float z;
    float w;
} quaternion_t;

typedef struct transform_s {
    vector3_t position;
    vector3_t scale;
    quaternion_t rotation;

    vector3_t forward;
    vector3_t up;
    vector3_t right;

    matrix4x4_t* matrix;
} transform_t;

// ################ GENERAL #################################

#define RAD_TO_DEGREE 57.29578f
#define DEGREE_TO_RAD 0.01745329f
#define SECONDS_TO_NANO 100000000

static inline float normalize(float value, float min, float max) {
    return (value - min) / (max - min);
}

static inline float clamp(float value, float min, float max) {
    return (value < min ? min : (value > max ? max : value));
}

static inline float lerp(float a, float b, float delta) {
    return ((1 - delta) * a) + (delta * b);
}

static inline float move_towards(float a, float b, float maxDistance) {
    return clamp(a + maxDistance, -b, b);
}

static inline float to_degree(float rad) {
    return rad * RAD_TO_DEGREE;
}

static inline float to_rad(float degree) {
    return degree * DEGREE_TO_RAD;
}

static inline float min(float a, float b) {
    return a < b ? a : b;
}

static inline float max(float a, float b) {
    return a > b ? a : b;
}


// ################ VECTOR 2 ##########################

void get_gl_vector2(float* result, vector2_t vector);

vector2_t get_vector2_from_gl(float* data);

vector2_t make_vector2(float x, float y);

vector2_t vector2_negate(vector2_t vector);

vector2_t vector2_zero();

vector2_t vector2_one();

vector2_t vector2_right();

vector2_t vector2_left();

vector2_t vector2_up();

vector2_t vector2_down();

vector2_t vector2_add(vector2_t a, vector2_t b);

vector2_t vector2_sub(vector2_t a, vector2_t b);

vector2_t vector2_scale(vector2_t vector, float scale);

float vector2_inner_mul(vector2_t a, vector2_t b);

float vector2_sqrd_len(vector2_t vector);

float vector2_len(vector2_t vector);

vector2_t vector2_norm(vector2_t vector);

vector2_t vector2_min(vector2_t a, vector2_t b);

vector2_t vector2_max(vector2_t a, vector2_t b);

vector2_t lerp_vector2(vector2_t a, vector2_t b, float delta);

vector2_t vector2_move_towards(vector2_t a, vector2_t b, float maxDistance);

float vector2_dot(vector2_t a, vector2_t b);

float vector2_angle(vector2_t a, vector2_t b);

bool_t vector2_compare(vector2_t a, vector2_t b);

void vector2_string(char* result, vector2_t vector);

// ################ VECTOR 3 ##########################

void get_gl_vector3(float* result, vector3_t vector);

vector3_t get_vector3_from_gl(float* data);

vector3_t make_vector3(float x, float y, float z);

vector3_t make_vector3_vec2(vector2_t vec, float z);

vector3_t vector3_negate(vector3_t vector);

vector3_t vector3_zero();

vector3_t vector3_one();

vector3_t vector3_right();

vector3_t vector3_left();

vector3_t vector3_up();

vector3_t vector3_down();

vector3_t vector3_forward();

vector3_t vector3_backward();

vector3_t vector3_add(vector3_t a, vector3_t b);

vector3_t vector3_sub(vector3_t a, vector3_t b);

vector3_t vector3_scale(vector3_t vector, float scale);

float vector3_inner_mul(vector3_t a, vector3_t b);

float vector3_sqrd_len(vector3_t vector);

float vector3_len(vector3_t vector);

vector3_t vector3_norm(vector3_t vector);

vector3_t vector3_min(vector3_t a, vector3_t b);

vector3_t vector3_max(vector3_t a, vector3_t b);

vector3_t vector3_cross(vector3_t a, vector3_t b);

vector3_t vector3_reflect(vector3_t a, vector3_t b);

vector3_t vector3_lerp(vector3_t a, vector3_t b, float delta);

vector3_t vector3_move_towards(vector3_t a, vector3_t b, float maxDistance);

float vector3_dot(vector3_t a, vector3_t b);

float vector3_angle(vector3_t a, vector3_t b);

bool_t vector3_compare(vector3_t a, vector3_t b);

void vector3_string(char* result, vector3_t vector);

// ################ VECTOR 4 ##########################

vector4_t make_vector4(float x, float y, float z, float w);

vector4_t make_vector4_vec3(vector3_t vec, float w);

vector4_t vector4_negate(vector4_t vector);
vector4_t vector4_zero();

vector4_t vector4_one();

void get_gl_vector4(float* result, vector4_t vector);

vector4_t get_vector4_from_gl(float* data);

vector4_t vector4_add(vector4_t a, vector4_t b);

vector4_t vector4_sub(vector4_t a, vector4_t b);

vector4_t vector4_scale(vector4_t vector, float scale);

float vector4_inner_mul(vector4_t a, vector4_t b);

float vector4_sqrd_len(vector4_t vector);

float vector4_len(vector4_t vector);

vector4_t vector4_norm(vector4_t vector);

vector4_t vector4_min(vector4_t a, vector4_t b);

vector4_t vector4_max(vector4_t a, vector4_t b);

vector4_t vector4_cross(vector4_t a, vector4_t b);

vector4_t vector4_reflect(vector4_t a, vector4_t b);

bool_t vector4_compare(vector4_t a, vector4_t b);

void vector4_string(char* result, vector4_t vector);

// #################### MATRIX 4X4 #######################

void get_gl_matrix4x4(float result[4][4], const matrix4x4_t* matrix);

void set_matrix4x4_from_gl(matrix4x4_t* result, const float data[4][4]);

void set_matrix4x4_identity(matrix4x4_t* matrix);

matrix4x4_t* make_matrix4x4();

void free_matrix4x4(matrix4x4_t* matrix);

void copy_matrix4x4(matrix4x4_t* result, const matrix4x4_t* data);

void copy_matrix4x4_row(vector4_t* result, const matrix4x4_t* data, int row);

void copy_matrix4x4_column(vector4_t* result, const matrix4x4_t* data, int column);

void matrix4x4_transpose(matrix4x4_t* matrix);

void matrix4x4_add(matrix4x4_t* result, const matrix4x4_t* a, const matrix4x4_t* b);

void matrix4x4_sub(matrix4x4_t* result, const matrix4x4_t* left, const matrix4x4_t* right);

void matrix4x4_scale(matrix4x4_t* result, const matrix4x4_t* data, float factor);

void matrix4x4_scale_anisio(matrix4x4_t* result, const matrix4x4_t* data, vector3_t scale);

void matrix4x4_mul(matrix4x4_t* result, const matrix4x4_t* left, const matrix4x4_t* right);

void matrix4x4_translate_in_place(matrix4x4_t* result, vector3_t trans);

void matrix4x4_mul_vector4(vector4_t* result, const matrix4x4_t* matrix, const vector4_t* multiplier);

void matrix4x4_translate(matrix4x4_t* matrix, vector3_t translation);

void matrix4x4_from_vector3_mul_outer(matrix4x4_t* result, vector3_t left, vector3_t right);

void matrix4x4_rotate_x(matrix4x4_t* result, const matrix4x4_t* data, float degrees);

void matrix4x4_rotate_y(matrix4x4_t* result, const matrix4x4_t* data, float degrees);

void matrix4x4_rotate_z(matrix4x4_t* result, const matrix4x4_t* data, float degrees);

void matrix4x4_invert(matrix4x4_t* result_matrix, const matrix4x4_t* matrix);

void matrix4x4_frustum(matrix4x4_t* result, float left, float right, float bottom, float top, float near, float far);

void matrix4x4_ortho(matrix4x4_t* result, float left, float right, float bottom, float top, float near, float far);

void matrix4x4_perspective(matrix4x4_t* result, float y_fov, float aspect, float near, float far);

void matrix4x4_look_at(matrix4x4_t* result, vector3_t eye, vector3_t look_at_pos, vector3_t up);

bool_t matrix4x4_compare(const matrix4x4_t* a, const matrix4x4_t* b);

void matrix4x4_string(char* result, const matrix4x4_t* matrix);

// ######################## QUATERNION ###########################################

quaternion_t make_quaternion(float x, float y, float z, float w);

quaternion_t quaternion_identity();

quaternion_t quaternion_add(quaternion_t a, quaternion_t b);

quaternion_t quaternion_sub(quaternion_t a, quaternion_t b);

quaternion_t quaternion_mul(quaternion_t quat_a, quaternion_t quat_b);

quaternion_t quaternion_scale(quaternion_t quat, float factor);

float quaternion_inner_product(quaternion_t quat_a, quaternion_t quat_b);

quaternion_t quaternion_conj(quaternion_t quat);

quaternion_t quaternion_rotate(quaternion_t quat, float degrees, vector3_t axis);

vector3_t quaternion_mul_vec3(quaternion_t quat, vector3_t vector);

void set_matrix4x4_data_from_quaternion(matrix4x4_t* result, quaternion_t quat);

void matrix4x4_mul_quat(matrix4x4_t* result, const matrix4x4_t* matrix, quaternion_t quat);

quaternion_t quaternion_from_matrix4x4(matrix4x4_t* data);

quaternion_t quaternion_from_euler(vector3_t euler);

vector3_t quaternion_to_euler(quaternion_t quat);

quaternion_t quaternion_normalize(quaternion_t quat);

bool_t quaternion_compare(quaternion_t a, quaternion_t b);

void quaternion_string(char* result, quaternion_t quat);

// ########################## TRANSFORM ###############################

transform_t* make_transform();

void free_transform(transform_t* transform);

void transform_update_matrix(transform_t* transform);

#ifdef CYNICAL_DEBUG

#define VECTOR2_PRINT(VEC) {\
    char buff[128];                 \
    vector2_string(buff, (VEC));    \
    MESSAGE(buff);                  \
}

#define VECTOR3_PRINT(VEC) {        \
    char buff[128];                 \
    vector3_string(buff, (VEC));    \
    MESSAGE(buff);                  \
}

#define VECTOR4_PRINT(VEC) {        \
    char buff[128];                 \
    vector4_string(buff, (VEC));    \
    MESSAGE(buff);                  \
}

#define MATRIX4x4_PRINT(MATRIX) {    \
    char buff[512];                  \
    matrix4x4_string(buff, (MATRIX));\
    MESSAGE(buff);                   \
}

#define QUATERNION_PRINT(QUAT) {       \
    char buff[256];                 \
    quaternion_string(buff, (QUAT));  \
    MESSAGE(buff);                  \
}

#else

#define VECTOR2_PRINT(VEC)
#define VECTOR3_PRINT(VEC)
#define VECTOR4_PRINT(VEC)
#define MATRIX4x4_PRINT(MATRIX)
#define QUATERNION_PRINT(QUAT)

#endif

#endif //CYNICAL_ENGINE_CYNICAL_MATH_H