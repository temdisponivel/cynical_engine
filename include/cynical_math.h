//
// Created by Morpheus on 04-Oct-17.
//

#ifndef CYNICAL_ENGINE_CYNICAL_MATH_H
#define CYNICAL_ENGINE_CYNICAL_MATH_H

#include <malloc.h>

#define false 0
#define true 1

typedef short bool;

typedef struct vector2_s {
    float x;
    float y;
} vector2;

typedef struct vector3_s {
    float x;
    float y;
    float z;
} vector3;

typedef struct vector4_s {
    float x;
    float y;
    float z;
    float w;
} vector4;

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
} matrix4x4;

typedef struct quaternion_s {
    float x;
    float y;
    float z;
    float w;
} quaternion;

typedef struct transform_s {
    vector3 position;
    vector3 scale;
    quaternion rotation;

    vector3 forward;
    vector3 up;
    vector3 right;

    matrix4x4* matrix;
} transform;

// ################ GENERAL #################################

const float RAD_TO_DEGREE;
const float DEGREE_TO_RAD;

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

void get_gl_vector2(float* result, vector2 vector);

vector2 get_vector2_from_gl(float* data);

vector2 make_vector2(float x, float y);

vector2 vector2_negate(vector2 vector);

vector2 vector2_zero();

vector2 vector2_one();

vector2 vector2_right();

vector2 vector2_left();

vector2 vector2_up();

vector2 vector2_down();

vector2 vector2_add(vector2 a, vector2 b);

vector2 vector2_sub(vector2 a, vector2 b);

vector2 vector2_scale(vector2 vector, float scale);

float vector2_inner_mul(vector2 a, vector2 b);

float vector2_sqrd_len(vector2 vector);

float vector2_len(vector2 vector);

vector2 vector2_norm(vector2 vector);

vector2 vector2_min(vector2 a, vector2 b);

vector2 vector2_max(vector2 a, vector2 b);

vector2 lerp_vector2(vector2 a, vector2 b, float delta);

vector2 vector2_move_towards(vector2 a, vector2 b, float maxDistance);

float vector2_dot(vector2 a, vector2 b);

float vector2_angle(vector2 a, vector2 b);

// ################ VECTOR 3 ##########################

void get_gl_vector3(float* result, vector3 vector);

vector3 get_vector3_from_gl(float* data);

vector3 make_vector3(float x, float y, float z);

vector3 vector3_negate(vector3 vector);

vector3 vector3_zero();

vector3 vector3_one();

vector3 vector3_right();

vector3 vector3_left();

vector3 vector3_up();

vector3 vector3_down();

vector3 vector3_forward();

vector3 vector3_backward();

vector3 vector3_add(vector3 a, vector3 b);

vector3 vector3_sub(vector3 a, vector3 b);

vector3 vector3_scale(vector3 vector, float scale);

float vector3_inner_mul(vector3 a, vector3 b);

float vector3_sqrd_len(vector3 vector);

float vector3_len(vector3 vector);

vector3 vector3_norm(vector3 vector);

vector3 vector3_min(vector3 a, vector3 b);

vector3 vector3_max(vector3 a, vector3 b);

vector3 vector3_cross(vector3 a, vector3 b);

vector3 vector3_reflect(vector3 a, vector3 b);

vector3 vector3_lerp(vector3 a, vector3 b, float delta);

vector3 vector3_move_towards(vector3 a, vector3 b, float maxDistance);

float vector3_dot(vector3 a, vector3 b);

float vector3_angle(vector3 a, vector3 b);

// ################ VECTOR 4 ##########################

void get_gl_vector4(float* result, vector4 vector);

vector4 get_vector4_from_gl(float* data);

vector4 make_vector4(float x, float y, float z, float w);

vector4 vector4_negate(vector4 vector);

vector4 vector4_zero();

vector4 vector4_one();

vector4 vector4_add(vector4 a, vector4 b);

vector4 vector4_sub(vector4 a, vector4 b);

vector4 vector4_scale(vector4 vector, float scale);

float vector4_inner_mul(vector4 a, vector4 b);

float vector4_sqrd_len(vector4 vector);

float vector4_len(vector4 vector);

vector4 vector4_norm(vector4 vector);

vector4 vector4_min(vector4 a, vector4 b);

vector4 vector4_max(vector4 a, vector4 b);

vector4 vector4_cross(vector4 a, vector4 b);

vector4 vector4_reflect(vector4 a, vector4 b);

// #################### MATRIX 4X4 #######################


void get_gl_matrix4x4(float result[4][4], matrix4x4* matrix);

void set_matrix4x4_from_gl(matrix4x4* result, float data[4][4]);

void set_matrix4x4_identity(matrix4x4* matrix);

matrix4x4* make_matrix4x4();

void free_matrix4x4(matrix4x4* matrix);

void copy_matrix4x4(matrix4x4* result, matrix4x4* data);

void copy_matrix4x4_row(vector4* result, matrix4x4* data, int row);

void copy_matrix4x4_column(vector4* result, matrix4x4* data, int column);

void matrix4x4_transpose(matrix4x4* matrix);

void matrix4x4_add(matrix4x4* result, matrix4x4* a, matrix4x4* b);

void matrix4x4_sub(matrix4x4* result, matrix4x4* left, matrix4x4* right);

void matrix4x4_scale(matrix4x4* result, matrix4x4* data, float factor);

void matrix4x4_scale_anisio(matrix4x4* result, matrix4x4* data, vector3 scale);

void matrix4x4_mul(matrix4x4* result, matrix4x4* left, matrix4x4* right);

void matrix4x4_translate_in_place(matrix4x4* result, vector3 trans);

void matrix4x4_mul_vector4(vector4* result, matrix4x4* matrix, vector4* multiplier);

void matrix4x4_translate(matrix4x4* matrix, vector3 translation);

void matrix4x4_from_vector3_mul_outer(matrix4x4* result, vector3 left, vector3 right);

void matrix4x4_rotate_x(matrix4x4* result, matrix4x4* data, float degrees);

void matrix4x4_rotate_y(matrix4x4* result, matrix4x4* data, float degrees);

void matrix4x4_rotate_z(matrix4x4* result, matrix4x4* data, float degrees);

void matrix4x4_invert(matrix4x4* result_matrix, matrix4x4* matrix);

void matrix4x4_frustum(matrix4x4* result, float left, float right, float bottom, float top, float near, float far);

void matrix4x4_ortho(matrix4x4* result, float left, float right, float bottom, float top, float near, float far);

void matrix4x4_perspective(matrix4x4* result, float y_fov, float aspect, float near, float far);

void matrix4x4_look_at(matrix4x4* result, vector3 eye, vector3 look_at_pos, vector3 up);

// ######################## QUATERNION ###########################################

quaternion make_quaternion(float x, float y, float z, float w);

quaternion quaternion_identity();

quaternion quaternion_add(quaternion a, quaternion b);

quaternion quaternion_sub(quaternion a, quaternion b);

quaternion quaternion_mul(quaternion quat_a, quaternion quat_b);

quaternion quaternion_scale(quaternion quat, float factor);

float quaternion_inner_product(quaternion quat_a, quaternion quat_b);

quaternion quaternion_conj(quaternion quat);

quaternion quaternion_rotate(quaternion quat, float degrees, vector3 axis);

vector3 quaternion_mul_vec3(quaternion quat, vector3 vector);

void set_matrix4x4_data_from_quaternion(matrix4x4* result, quaternion quat);

void matrix4x4_mul_quat(matrix4x4* result, matrix4x4* matrix, quaternion quat);

quaternion quaternion_from_matrix4x4(matrix4x4* data);

quaternion quaternion_from_euler(vector3 euler);

vector3 quaternion_to_euler(quaternion quat);

quaternion quaternion_normalize(quaternion quat);

// ########################## TRANSFORM ###############################

transform* make_transform();

void free_transform(transform* transform);

void transform_update_matrix(transform* transform);

#endif //CYNICAL_ENGINE_CYNICAL_MATH_H