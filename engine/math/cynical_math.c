//
// Created by Morpheus on 06-Oct-17.
//

#include <cynical_math.h>
#include <math.h>
#include <stdio.h>
#include <cynical_log.h>


// ################ VECTOR 2 ##########################

void get_gl_vector2(float* result, vector2 vector) {
    result[0] = vector.x;
    result[1] = vector.y;
}

vector2 get_vector2_from_gl(float* data) {
    vector2 result;
    result.x = data[0];
    result.y = data[1];
    return result;
}

vector2 make_vector2(float x, float y) {
    vector2 result;
    result.x = x;
    result.y = y;
    return result;
}

vector2 vector2_negate(vector2 vector) {
    float x = -vector.x;
    float y = -vector.y;
    return make_vector2(x, y);
}

vector2 vector2_zero() {
    return make_vector2(0, 0);
}

vector2 vector2_one() {
    return make_vector2(1, 1);
}

vector2 vector2_right() {
    return make_vector2(1, 0);
}

vector2 vector2_left() {
    return vector2_negate(vector2_right());
}

vector2 vector2_up() {
    return make_vector2(0, 1);
}

vector2 vector2_down() {
    return vector2_negate(vector2_up());
}

vector2 vector2_add(vector2 a, vector2 b) {
    return make_vector2(a.x + b.x, a.y + b.y);
}

vector2 vector2_sub(vector2 a, vector2 b) {
    return make_vector2(a.x - b.x, a.y - b.y);
}

vector2 vector2_scale(vector2 vector, float scale) {
    return make_vector2(vector.x * scale, vector.y * scale);
}

float vector2_inner_mul(vector2 a, vector2 b) {
    float result = 0.0f;
    result += a.x * b.x;
    result += a.y * b.y;
    return result;
}

float vector2_sqrd_len(vector2 vector) {
    return vector2_inner_mul(vector, vector);
}

float vector2_len(vector2 vector) {
    return sqrtf(vector2_sqrd_len(vector));
}

vector2 vector2_norm(vector2 vector) {
    float scale = vector2_len(vector);
    float scale_factor = 1.0f / scale;
    return vector2_scale(vector, scale_factor);
}

vector2 vector2_min(vector2 a, vector2 b) {
    float x = min(a.x, b.x);
    float y = min(a.y, b.y);
    return make_vector2(x, y);
}

vector2 vector2_max(vector2 a, vector2 b) {
    float x = max(a.x, b.x);
    float y = max(a.y, b.y);
    return make_vector2(x, y);
}

vector2 lerp_vector2(vector2 a, vector2 b, float delta) {
    float x = lerp(a.x, b.x, delta);
    float y = lerp(a.y, b.y, delta);
    return make_vector2(x, y);
}

vector2 vector2_move_towards(vector2 a, vector2 b, float maxDistance) {
    float x = move_towards(a.x, b.x, maxDistance);
    float y = move_towards(a.y, b.y, maxDistance);
    return make_vector2(x, y);
}

float vector2_dot(vector2 a, vector2 b) {
    float result = 0;
    result += a.x * b.x;
    result += a.y * b.y;
    return result;
}

float vector2_angle(vector2 a, vector2 b) {
    a = vector2_norm(a);
    b = vector2_norm(b);
    float rad_angle = acos(vector2_dot(a, b));
    return to_degree(rad_angle);
}

bool vector2_compare(vector2 a, vector2 b) {
    return a.x == b.x && a.y == b.y;
}

void vector2_string(char* result, vector2 vector) {
    char fmt[] = "x: %f y: %f";
    sprintf(result, fmt, vector.x, vector.y);
}

// ################ VECTOR 3 ##########################

void get_gl_vector3(float* result, vector3 vector) {
    result[0] = vector.x;
    result[1] = vector.y;
    result[2] = vector.z;
}

vector3 get_vector3_from_gl(float* data) {
    vector3 result;
    result.x = data[0];
    result.y = data[1];
    result.z = data[2];
    return result;
}

vector3 make_vector3(float x, float y, float z) {
    vector3 result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

vector3 make_vector3_vec2(vector2 vec, float z) {
    return make_vector3(vec.x, vec.y, z);
}

vector3 vector3_negate(vector3 vector) {
    float x = -vector.x;
    float y = -vector.y;
    float z = -vector.z;
    return make_vector3(x, y, z);
}

vector3 vector3_zero() {
    return make_vector3(0, 0, 0);
}

vector3 vector3_one() {
    return make_vector3(1, 1, 1);
}

vector3 vector3_right() {
    return make_vector3(1, 0, 0);
}

vector3 vector3_left() {
    return vector3_negate(vector3_right());
}

vector3 vector3_up() {
    return make_vector3(0, 1, 0);
}

vector3 vector3_down() {
    return vector3_negate(vector3_up());
}

vector3 vector3_forward() {
    return make_vector3(0, 0, 1);
}

vector3 vector3_backward() {
    return vector3_negate(vector3_forward());
}

vector3 vector3_add(vector3 a, vector3 b) {
    return make_vector3(a.x + b.x, a.y + b.y, a.z + b.z);
}

vector3 vector3_sub(vector3 a, vector3 b) {
    return make_vector3(a.x - b.x, a.y - b.y, a.z - b.z);
}

vector3 vector3_scale(vector3 vector, float scale) {
    return make_vector3(vector.x * scale, vector.y * scale, vector.z * scale);
}

float vector3_inner_mul(vector3 a, vector3 b) {
    float result = 0.0f;
    result += a.x * b.x;
    result += a.y * b.y;
    result += a.z * b.z;
    return result;
}

float vector3_sqrd_len(vector3 vector) {
    return vector3_inner_mul(vector, vector);
}

float vector3_len(vector3 vector) {
    return sqrtf(vector3_sqrd_len(vector));
}

vector3 vector3_norm(vector3 vector) {
    float scale = vector3_len(vector);
    float scale_factor = 1.0f / scale;
    return vector3_scale(vector, scale_factor);
}

vector3 vector3_min(vector3 a, vector3 b) {
    float x = min(a.x, b.x);
    float y = min(a.y, b.y);
    float z = min(a.z, b.z);
    return make_vector3(x, y, z);
}

vector3 vector3_max(vector3 a, vector3 b) {
    float x = max(a.x, b.x);
    float y = max(a.y, b.y);
    float z = max(a.z, b.z);
    return make_vector3(x, y, z);
}

vector3 vector3_cross(vector3 a, vector3 b) {
    float x = (a.y * b.z) - (a.z * b.y);
    float y = (a.z * b.x) - (a.x * b.z);
    float z = (a.x * b.y) - (a.y * b.x);
    return make_vector3(x, y, z);
}

vector3 vector3_reflect(vector3 a, vector3 b) {
    float p = 2.f * vector3_inner_mul(a, b);

    float x = a.x - p * b.x;
    float y = a.y - p * b.y;
    float z = a.z - p * b.z;

    return make_vector3(x, y, z);
}

vector3 vector3_lerp(vector3 a, vector3 b, float delta) {
    float x = lerp(a.x, b.x, delta);
    float y = lerp(a.y, b.y, delta);
    float z = lerp(a.z, b.z, delta);
    return make_vector3(x, y, z);
}

vector3 vector3_move_towards(vector3 a, vector3 b, float maxDistance) {
    float x = move_towards(a.x, b.x, maxDistance);
    float y = move_towards(a.y, b.y, maxDistance);
    float z = move_towards(a.z, b.z, maxDistance);
    return make_vector3(x, y, z);
}

float vector3_dot(vector3 a, vector3 b) {
    float result = 0;
    result += a.x * b.x;
    result += a.y * b.y;
    result += a.z * b.z;
    return result;
}

float vector3_angle(vector3 a, vector3 b) {
    a = vector3_norm(a);
    b = vector3_norm(b);
    float dot = vector3_dot(a, b);
    float rad_angle = acos(dot);
    return to_degree(rad_angle);
}

bool vector3_compare(vector3 a, vector3 b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

void vector3_string(char* result, vector3 vector) {
    char fmt[] = "x: %f y: %f z: %f";
    sprintf(result, fmt, vector.x, vector.y, vector.z);
}

// ################ VECTOR 4 ##########################

void get_gl_vector4(float* result, vector4 vector) {
    result[0] = vector.x;
    result[1] = vector.y;
    result[2] = vector.z;
    result[3] = vector.w;
}

vector4 get_vector4_from_gl(float* data) {
    vector4 result;
    result.x = data[0];
    result.y = data[1];
    result.z = data[2];
    result.w = data[3];
    return result;
}


vector4 make_vector4(float x, float y, float z, float w) {
    vector4 result;
    result.x = x;
    result.y = y;
    result.z = z;
    result.w = w;
    return result;
}

vector4 make_vector4_vec3(vector3 vec, float w) {
    return make_vector4(vec.x, vec.y, vec.z, w);
}

vector4 vector4_negate(vector4 vector) {
    float x = -vector.x;
    float y = -vector.y;
    float z = -vector.z;
    float w = -vector.w;
    return make_vector4(x, y, z, w);
}

vector4 vector4_zero() {
    return make_vector4(0, 0, 0, 0);
}

vector4 vector4_one() {
    return make_vector4(1, 1, 1, 1);
}

vector4 vector4_add(vector4 a, vector4 b) {
    return make_vector4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

vector4 vector4_sub(vector4 a, vector4 b) {
    return make_vector4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

vector4 vector4_scale(vector4 vector, float scale) {
    return make_vector4(vector.x * scale, vector.y * scale, vector.z * scale, vector.w * scale);
}

float vector4_inner_mul(vector4 a, vector4 b) {
    float result = 0.0f;
    result += a.x * b.x;
    result += a.y * b.y;
    result += a.z * b.z;
    result += a.w * b.w;
    return result;
}

float vector4_sqrd_len(vector4 vector) {
    return vector4_inner_mul(vector, vector);
}

float vector4_len(vector4 vector) {
    return sqrtf(vector4_sqrd_len(vector));
}

vector4 vector4_norm(vector4 vector) {
    float scale = vector4_len(vector);
    float scale_factor = 1.0f / scale;
    return vector4_scale(vector, scale_factor);
}

vector4 vector4_min(vector4 a, vector4 b) {
    float x = min(a.x, b.x);
    float y = min(a.y, b.y);
    float z = min(a.z, b.z);
    float w = min(a.w, b.w);
    return make_vector4(x, y, z, w);
}

vector4 vector4_max(vector4 a, vector4 b) {
    float x = max(a.x, b.x);
    float y = max(a.y, b.y);
    float z = max(a.z, b.z);
    float w = max(a.w, b.w);
    return make_vector4(x, y, z, w);
}

vector4 vector4_cross(vector4 a, vector4 b) {
    float x = (a.y * b.z) - (a.z * b.y);
    float y = (a.z * b.x) - (a.x * b.z);
    float z = (a.x * b.y) - (a.y * b.x);
    float w = 1.0f;
    return make_vector4(x, y, z, w);
}

vector4 vector4_reflect(vector4 a, vector4 b) {
    float p = 2.f * vector4_inner_mul(a, b);

    float x = a.x - p * b.x;
    float y = a.y - p * b.y;
    float z = a.z - p * b.z;
    float w = a.w - p * b.w;

    return make_vector4(x, y, z, w);
}

bool vector4_compare(vector4 a, vector4 b) {
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

void vector4_string(char* result, vector4 vector) {
    char fmt[] = "x: %f y: %f z: %f w: %f";
    sprintf(result, fmt, vector.x, vector.y, vector.z, vector.w);
}

// #################### MATRIX 4X4 #######################


void get_gl_matrix4x4(float result[4][4], matrix4x4* matrix) {
    result[0][0] = matrix->xx;
    result[0][1] = matrix->xy;
    result[0][2] = matrix->xz;
    result[0][3] = matrix->xw;

    result[1][0] = matrix->yx;
    result[1][1] = matrix->yy;
    result[1][2] = matrix->yz;
    result[1][3] = matrix->yw;

    result[2][0] = matrix->zx;
    result[2][1] = matrix->zy;
    result[2][2] = matrix->zz;
    result[2][3] = matrix->zw;

    result[3][0] = matrix->wx;
    result[3][1] = matrix->wy;
    result[3][2] = matrix->wz;
    result[3][3] = matrix->ww;
}

void set_matrix4x4_from_gl(matrix4x4* result, float data[4][4]) {
    result->xx = data[0][0];
    result->xy = data[0][1];
    result->xz = data[0][2];
    result->xw = data[0][3];

    result->yx = data[1][0];
    result->yy = data[1][1];
    result->yz = data[1][2];
    result->yw = data[1][3];

    result->zx = data[2][0];
    result->zy = data[2][1];
    result->zz = data[2][2];
    result->zw = data[2][3];

    result->wx = data[3][0];
    result->wy = data[3][1];
    result->wz = data[3][2];
    result->ww = data[3][3];
}

void set_matrix4x4_identity(matrix4x4* matrix) {
    matrix->xx = 1;
    matrix->xy = 0;
    matrix->xz = 0;
    matrix->xw = 0;

    matrix->yx = 0;
    matrix->yy = 1;
    matrix->yz = 0;
    matrix->yw = 0;

    matrix->zx = 0;
    matrix->zy = 0;
    matrix->zz = 1;
    matrix->zw = 0;

    matrix->wx = 0;
    matrix->wy = 0;
    matrix->wz = 0;
    matrix->ww = 1;

    normalize(10, 5, 20);
}

matrix4x4* make_matrix4x4() {
    matrix4x4* result = malloc(sizeof(matrix4x4));
    set_matrix4x4_identity(result);
    return result;
}

void free_matrix4x4(matrix4x4* matrix) {
    free(matrix);
}

void copy_matrix4x4(matrix4x4* result, matrix4x4* data) {
    data->xx = result->xx;
    data->xy = result->xy;
    data->xz = result->xz;
    data->xw = result->xw;

    data->yx = result->yx;
    data->yy = result->yy;
    data->yz = result->yz;
    data->yw = result->yw;

    data->zx = result->zx;
    data->zy = result->zy;
    data->zz = result->zz;
    data->zw = result->zw;

    data->wx = result->wx;
    data->wy = result->wy;
    data->wz = result->wz;
    data->ww = result->ww;
}

void copy_matrix4x4_row(vector4* result, matrix4x4* data, int row) {
    if (row < 0)
        row = 0;
    else if (row > 3)
        row = 3;

    if (row == 0) {
        result->x = data->xx;
        result->y = data->yx;
        result->z = data->zx;
        result->w = data->wx;
    } else if (row == 1) {
        result->x = data->xy;
        result->y = data->yy;
        result->z = data->zy;
        result->w = data->wy;
    } else if (row == 2) {
        result->x = data->xz;
        result->y = data->yz;
        result->z = data->zz;
        result->w = data->zw;
    } else if (row == 3) {
        result->x = data->xw;
        result->y = data->yw;
        result->z = data->zw;
        result->w = data->ww;
    }
}

void copy_matrix4x4_column(vector4* result, matrix4x4* data, int column) {
    if (column < 0)
        column = 0;
    else if (column > 3)
        column = 3;

    if (column == 0) {
        result->x = data->xx;
        result->y = data->xy;
        result->z = data->xz;
        result->w = data->xw;
    } else if (column == 1) {
        result->x = data->yx;
        result->y = data->yy;
        result->z = data->yz;
        result->w = data->yw;
    } else if (column == 2) {
        result->x = data->zx;
        result->y = data->zy;
        result->z = data->zz;
        result->w = data->zw;
    } else if (column == 3) {
        result->x = data->wx;
        result->y = data->wy;
        result->z = data->wz;
        result->w = data->ww;
    }
}

void matrix4x4_transpose(matrix4x4* matrix) {
    matrix4x4* temp = malloc(sizeof(matrix4x4));
    copy_matrix4x4(matrix, temp);

    matrix->xx = temp->xx;
    matrix->xy = temp->yx;
    matrix->xz = temp->zx;
    matrix->xw = temp->wx;

    matrix->yx = temp->xy;
    matrix->yy = temp->yy;
    matrix->yz = temp->zy;
    matrix->yw = temp->wy;

    matrix->zx = temp->xz;
    matrix->zy = temp->yz;
    matrix->zz = temp->zz;
    matrix->zw = temp->wz;

    matrix->wx = temp->xw;
    matrix->wy = temp->yw;
    matrix->wz = temp->zw;
    matrix->ww = temp->ww;

    free(temp);
}

void matrix4x4_add(matrix4x4* result, matrix4x4* a, matrix4x4* b) {
    result->xx = a->xx + b->xx;
    result->xy = a->xy + b->xy;
    result->xz = a->xz + b->xz;
    result->xw = a->xw + b->xw;

    result->yx = a->yx + b->yx;
    result->yy = a->yy + b->yy;
    result->yz = a->yz + b->yz;
    result->yw = a->yw + b->yw;

    result->zx = a->zx + b->zx;
    result->zy = a->zy + b->zy;
    result->zz = a->zz + b->zz;
    result->zw = a->zw + b->zw;

    result->wx = a->wx + b->wx;
    result->wy = a->wy + b->wy;
    result->wz = a->wz + b->wz;
    result->xw = a->ww + b->ww;
}

void matrix4x4_sub(matrix4x4* result, matrix4x4* left, matrix4x4* right) {
    result->xx = left->xx - right->xx;
    result->xy = left->xy - right->xy;
    result->xz = left->xz - right->xz;
    result->xw = left->xw - right->xw;

    result->yx = left->yx - right->yx;
    result->yy = left->yy - right->yy;
    result->yz = left->yz - right->yz;
    result->yw = left->yw - right->yw;

    result->zx = left->zx - right->zx;
    result->zy = left->zy - right->zy;
    result->zz = left->zz - right->zz;
    result->zw = left->zw - right->zw;

    result->wx = left->wx - right->wx;
    result->wy = left->wy - right->wy;
    result->wz = left->wz - right->wz;
    result->xw = left->ww - right->ww;
}

void matrix4x4_scale(matrix4x4* result, matrix4x4* data, float factor) {
    result->xx = data->xx * factor;
    result->xy = data->xy * factor;
    result->xz = data->xz * factor;
    result->xw = data->xw * factor;

    result->yx = data->yx * factor;
    result->yy = data->yy * factor;
    result->yz = data->yz * factor;
    result->yw = data->yw * factor;

    result->zx = data->zx * factor;
    result->zy = data->zy * factor;
    result->zz = data->zz * factor;
    result->zw = data->zw * factor;

    result->wx = data->wx * factor;
    result->wy = data->wy * factor;
    result->wz = data->wz * factor;
    result->xw = data->ww * factor;
}

void matrix4x4_scale_anisio(matrix4x4* result, matrix4x4* data, vector3 scale) {
    result->xx = data->xx * scale.x;
    result->xy = data->xy * scale.x;
    result->xz = data->xz * scale.x;
    result->xw = data->xw * scale.x;

    result->yx = data->yx * scale.y;
    result->yy = data->yy * scale.y;
    result->yz = data->yz * scale.y;
    result->yw = data->yw * scale.y;

    result->zx = data->zx * scale.z;
    result->zy = data->zy * scale.z;
    result->zz = data->zz * scale.z;
    result->zw = data->zw * scale.z;

    result->wx = data->wx;
    result->wy = data->wy;
    result->wz = data->wz;
    result->ww = data->ww;
}

void matrix4x4_mul(matrix4x4* result, matrix4x4* left, matrix4x4* right) {
    float left_data[4][4];
    float right_data[4][4];
    float result_data[4][4];

    get_gl_matrix4x4(left_data, left);
    get_gl_matrix4x4(right_data, right);

    int counter, row, column;
    for (column = 0; column < 4; ++column) {
        for (row = 0; row < 4; ++row) {
            result_data[column][row] = 0.f;
            for (counter = 0; counter < 4; ++counter) {
                result_data[column][row] += left_data[counter][row] * right_data[column][counter];
            }
        }
    }

    set_matrix4x4_from_gl(result, result_data);
}

void matrix4x4_translate_in_place(matrix4x4* result, vector3 trans) {
    vector4 translation = make_vector4(trans.x, trans.y, trans.z, 0);

    vector4 row;
    copy_matrix4x4_row(&row, result, 0);
    result->wx += vector4_inner_mul(row, translation);

    copy_matrix4x4_row(&row, result, 1);
    result->wy += vector4_inner_mul(row, translation);

    copy_matrix4x4_row(&row, result, 2);
    result->wz += vector4_inner_mul(row, translation);

    copy_matrix4x4_row(&row, result, 3);
    result->ww += vector4_inner_mul(row, translation);
}

void matrix4x4_mul_vector4(vector4* result, matrix4x4* matrix, vector4* multiplier) {
    result->x = result->y = result->z = result->w = 0;

    result->x = (matrix->xx * multiplier->x) + (matrix->yx * multiplier->y) + (matrix->zx * multiplier->z) +
                (matrix->wx * multiplier->w);

    result->y = (matrix->xy * multiplier->x) + (matrix->yy * multiplier->y) + (matrix->zy * multiplier->z) +
                (matrix->wy * multiplier->w);

    result->z = (matrix->xz * multiplier->x) + (matrix->yz * multiplier->y) + (matrix->zz * multiplier->z) +
                (matrix->wz * multiplier->w);

    result->w = (matrix->xw * multiplier->x) + (matrix->yw * multiplier->y) + (matrix->zw * multiplier->z) +
                (matrix->ww * multiplier->w);
}

void matrix4x4_translate(matrix4x4* matrix, vector3 translation) {
    set_matrix4x4_identity(matrix);
    matrix->wx = translation.x;
    matrix->wy = translation.y;
    matrix->wz = translation.z;
}

void matrix4x4_from_vector3_mul_outer(matrix4x4* result, vector3 left, vector3 right) {

    result->xx = left.x * right.x;
    result->xy = left.x * right.y;
    result->xz = left.x * right.z;
    result->xw = 0;

    result->yx = left.y * right.x;
    result->yy = left.y * right.y;
    result->yz = left.y * right.z;
    result->yw = 0;

    result->zx = left.z * right.x;
    result->zy = left.z * right.y;
    result->zz = left.z * right.z;
    result->zw = 0;

    result->wx = 0;
    result->wy = 0;
    result->wz = 0;
    result->ww = 0;
}

void matrix4x4_rotate_x(matrix4x4* result, matrix4x4* data, float degrees) {
    float radians = to_rad(degrees);
    float s = sinf(radians);
    float c = cosf(radians);

    matrix4x4 multiplier;
    set_matrix4x4_identity(&multiplier);

    multiplier.xx = 1.f;
    multiplier.yy = c;
    multiplier.yz = s;
    multiplier.zy = -s;
    multiplier.zz = c;
    multiplier.ww = 1.f;

    matrix4x4_mul(result, data, &multiplier);
}

void matrix4x4_rotate_y(matrix4x4* result, matrix4x4* data, float degrees) {
    float radians = to_rad(degrees);
    float s = sinf(radians);
    float c = cosf(radians);

    matrix4x4 multiplier;
    set_matrix4x4_identity(&multiplier);

    multiplier.xx = c;
    multiplier.xz = s;
    multiplier.yy = 1.f;
    multiplier.zx = -s;
    multiplier.zz = c;
    multiplier.ww = 1.f;

    matrix4x4_mul(result, data, &multiplier);
}

void matrix4x4_rotate_z(matrix4x4* result, matrix4x4* data, float degrees) {
    float radians = to_rad(degrees);
    float s = sinf(radians);
    float c = cosf(radians);

    matrix4x4 multiplier;
    set_matrix4x4_identity(&multiplier);

    multiplier.xx = c;
    multiplier.xy = s;
    multiplier.yx = -s;
    multiplier.yy = c;
    multiplier.zz = 1.f;
    multiplier.ww = 1.f;

    matrix4x4_mul(result, data, &multiplier);
}

void matrix4x4_invert(matrix4x4* result_matrix, matrix4x4* matrix) {
    float data[4][4];
    float result[4][4];

    get_gl_matrix4x4(data, matrix);

    float s[6];
    float c[6];
    s[0] = data[0][0] * data[1][1] - data[1][0] * data[0][1];
    s[1] = data[0][0] * data[1][2] - data[1][0] * data[0][2];
    s[2] = data[0][0] * data[1][3] - data[1][0] * data[0][3];
    s[3] = data[0][1] * data[1][2] - data[1][1] * data[0][2];
    s[4] = data[0][1] * data[1][3] - data[1][1] * data[0][3];
    s[5] = data[0][2] * data[1][3] - data[1][2] * data[0][3];

    c[0] = data[2][0] * data[3][1] - data[3][0] * data[2][1];
    c[1] = data[2][0] * data[3][2] - data[3][0] * data[2][2];
    c[2] = data[2][0] * data[3][3] - data[3][0] * data[2][3];
    c[3] = data[2][1] * data[3][2] - data[3][1] * data[2][2];
    c[4] = data[2][1] * data[3][3] - data[3][1] * data[2][3];
    c[5] = data[2][2] * data[3][3] - data[3][2] * data[2][3];

    /* Assumes it is invertible */
    float idet = 1.0f / (s[0] * c[5] - s[1] * c[4] + s[2] * c[3] + s[3] * c[2] - s[4] * c[1] + s[5] * c[0]);

    result[0][0] = (data[1][1] * c[5] - data[1][2] * c[4] + data[1][3] * c[3]) * idet;
    result[0][1] = (-data[0][1] * c[5] + data[0][2] * c[4] - data[0][3] * c[3]) * idet;
    result[0][2] = (data[3][1] * s[5] - data[3][2] * s[4] + data[3][3] * s[3]) * idet;
    result[0][3] = (-data[2][1] * s[5] + data[2][2] * s[4] - data[2][3] * s[3]) * idet;

    result[1][0] = (-data[1][0] * c[5] + data[1][2] * c[2] - data[1][3] * c[1]) * idet;
    result[1][1] = (data[0][0] * c[5] - data[0][2] * c[2] + data[0][3] * c[1]) * idet;
    result[1][2] = (-data[3][0] * s[5] + data[3][2] * s[2] - data[3][3] * s[1]) * idet;
    result[1][3] = (data[2][0] * s[5] - data[2][2] * s[2] + data[2][3] * s[1]) * idet;

    result[2][0] = (data[1][0] * c[4] - data[1][1] * c[2] + data[1][3] * c[0]) * idet;
    result[2][1] = (-data[0][0] * c[4] + data[0][1] * c[2] - data[0][3] * c[0]) * idet;
    result[2][2] = (data[3][0] * s[4] - data[3][1] * s[2] + data[3][3] * s[0]) * idet;
    result[2][3] = (-data[2][0] * s[4] + data[2][1] * s[2] - data[2][3] * s[0]) * idet;

    result[3][0] = (-data[1][0] * c[3] + data[1][1] * c[1] - data[1][2] * c[0]) * idet;
    result[3][1] = (data[0][0] * c[3] - data[0][1] * c[1] + data[0][2] * c[0]) * idet;
    result[3][2] = (-data[3][0] * s[3] + data[3][1] * s[1] - data[3][2] * s[0]) * idet;
    result[3][3] = (data[2][0] * s[3] - data[2][1] * s[1] + data[2][2] * s[0]) * idet;

    set_matrix4x4_from_gl(result_matrix, result);
}

void matrix4x4_frustum(matrix4x4* result, float left, float right, float bottom, float top, float near, float far) {
    result->xx = 2.f * near / (right - left);
    result->xy = result->xz = result->xw = 0.f;

    result->yy = 2.f * near / (top - bottom);
    result->yx = result->yz = result->yw = 0.f;

    result->zx = (right + left) / (right - left);
    result->zy = (top + bottom) / (top - bottom);
    result->zz = -(far + near) / (far - near);
    result->zw = -1.f;

    result->wz = -2.f * (far * near) / (far - near);
    result->wx = result->wy = result->ww = 0.f;
}

void matrix4x4_ortho(matrix4x4* result, float left, float right, float bottom, float top, float near, float far) {
    result->xx = 2.f / (right - left);
    result->xy = result->xz = result->xw = 0.f;

    result->yy = 2.f / (top - bottom);
    result->yx = result->yz = result->yw = 0.f;

    result->zz = -2.f / (far - near);
    result->zx = result->zy = result->zw = 0.f;

    result->wx = -(right + left) / (right - left);
    result->wy = -(top + bottom) / (top - bottom);
    result->wz = -(far + near) / (far - near);
    result->ww = 1.f;
}

void matrix4x4_perspective(matrix4x4* result, float y_fov, float aspect, float near, float far) {
    y_fov = to_rad(y_fov);
    float const a = 1.f / tan(y_fov / 2.f);

    result->xx = a / aspect;
    result->xy = 0.f;
    result->xz = 0.f;
    result->xw = 0.f;

    result->yx = 0.f;
    result->yy = a;
    result->yz = 0.f;
    result->yw = 0.f;

    result->zx = 0.f;
    result->zy = 0.f;
    result->zz = -((far + near) / (far - near));
    result->zw = -1.f;

    result->wx = 0.f;
    result->wy = 0.f;
    result->wz = -((2.f * far * near) / (far - near));
    result->ww = 0.f;
}

void matrix4x4_look_at(matrix4x4* result, vector3 eye, vector3 look_at_pos, vector3 up) {

    vector3 f = vector3_sub(look_at_pos, eye);
    f = vector3_norm(f);

    vector3 s = vector3_cross(f, up);
    s = vector3_norm(s);

    vector3 t = vector3_cross(s, f);

    result->xx = s.x;
    result->xy = t.x;
    result->xz = -f.x;
    result->xw = 0.f;

    result->yx = s.y;
    result->yy = t.y;
    result->yz = -f.y;
    result->yw = 0.f;

    result->zx = s.z;
    result->zy = t.z;
    result->zz = -f.z;
    result->zw = 0.f;

    result->wx = 0.f;
    result->wy = 0.f;
    result->wz = 0.f;
    result->ww = 1.f;

    matrix4x4_translate_in_place(result, vector3_negate(eye));
}

bool matrix4x4_compare(matrix4x4* a, matrix4x4* b) {
    return
            a->xx == b->xx &&
            a->xy == b->xy &&
            a->xz == b->xz &&
            a->xw == b->xw &&
            a->yx == b->yx &&
            a->yy == b->yy &&
            a->yz == b->yz &&
            a->yw == b->yw &&
            a->zx == b->zx &&
            a->zy == b->zy &&
            a->zz == b->zz &&
            a->zw == b->zw &&
            a->wx == b->wx &&
            a->wy == b->wy &&
            a->wz == b->wz &&
            a->ww == b->ww;
}

void matrix4x4_string(char* result, matrix4x4* vector) {
    char fmt[] =
            "xx: %f xy: %f xz: %f xw: %f" "\n"
            "yx: %f yy: %f yz: %f yw: %f" "\n"
            "zx: %f zy: %f zz: %f zw: %f" "\n"
            "wx: %f wy: %f wz: %f ww: %f" "\n";

    sprintf(result,
            fmt,
            vector->xx,
            vector->xy,
            vector->xz,
            vector->xw,
            vector->yx,
            vector->yy,
            vector->yz,
            vector->yw,
            vector->zx,
            vector->zy,
            vector->zz,
            vector->zw,
            vector->wx,
            vector->wy,
            vector->wz,
            vector->ww);
}

void matrix4x4_print(matrix4x4* matrix) {
    char buff[512];
    matrix4x4_string(buff, matrix);
    MESSAGE(buff);
}

// ######################## QUATERNION ###########################################

quaternion make_quaternion(float x, float y, float z, float w) {
    quaternion quat;
    quat.x = x;
    quat.y = y;
    quat.z = z;
    quat.w = w;
    return quat;
}

quaternion quaternion_identity() {
    return make_quaternion(0, 0, 0, 1);
}

quaternion quaternion_add(quaternion a, quaternion b) {
    return make_quaternion(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

quaternion quaternion_sub(quaternion a, quaternion b) {
    return make_quaternion(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

quaternion quaternion_mul(quaternion quat_a, quaternion quat_b) {
    vector3 a = make_vector3(quat_a.x, quat_a.y, quat_a.z);
    vector3 b = make_vector3(quat_b.x, quat_b.y, quat_b.z);

    vector3 result = vector3_cross(a, b);
    vector3 w = vector3_scale(a, quat_b.w);

    result = vector3_add(result, w);

    w = vector3_scale(b, quat_a.w);
    result = vector3_add(result, w);

    quaternion quat_result = make_quaternion(result.x, result.y, result.z, 0);
    quat_result.w = quat_a.w * quat_b.w - vector3_inner_mul(a, b);

    return quat_result;
}

quaternion quaternion_scale(quaternion quat, float factor) {
    float x = quat.x * factor;
    float y = quat.y * factor;
    float z = quat.z * factor;
    float w = quat.w * factor;

    return make_quaternion(x, y, z, w);
}

float quaternion_inner_product(quaternion quat_a, quaternion quat_b) {
    float x = quat_a.x * quat_b.x;
    float y = quat_a.y * quat_b.y;
    float z = quat_a.z * quat_b.z;
    float w = quat_a.w * quat_b.w;

    return x + y + z + w;
}

quaternion quaternion_conj(quaternion quat) {
    float x = -quat.x;
    float y = -quat.y;
    float z = -quat.z;
    float w = quat.w;
    return make_quaternion(x, y, z, w);
}

quaternion quaternion_rotate(quaternion quat, float degrees, vector3 axis) {
    float radians = to_rad(degrees);
    vector3 v = vector3_scale(axis, sinf(radians / 2.0f));
    float w = cosf(radians / 2.0f);

    quaternion rot;
    rot.x = v.x;
    rot.y = v.y;
    rot.z = v.z;
    rot.w = w;

    return quaternion_mul(quat, rot);
}

vector3 quaternion_mul_vec3(quaternion quat, vector3 vector) {
/*
 * Method by Fabian 'ryg' Giessen (of Farbrausch)
t = 2 * cross(q.xyz, v)
v' = v + q.w * t + cross(q.xyz, t)
 */
    vector3 q_xyz = make_vector3(quat.x, quat.y, quat.z);

    vector3 t = vector3_cross(q_xyz, vector);
    t = vector3_scale(t, 2);

    vector3 u = vector3_cross(q_xyz, t);
    t = vector3_scale(t, quat.w);

    vector3 result;
    result = vector3_add(vector, t);
    result = vector3_add(result, u);

    return result;
}

void set_matrix4x4_data_from_quaternion(matrix4x4* result, quaternion quat) {
    float a = quat.w;
    float b = quat.x;
    float c = quat.y;
    float d = quat.z;
    float a2 = a * a;
    float b2 = b * b;
    float c2 = c * c;
    float d2 = d * d;

    result->xx = a2 + b2 - c2 - d2;
    result->xy = 2.f * (b * c + a * d);
    result->xz = 2.f * (b * d - a * c);
    result->xw = 0.f;

    result->yx = 2 * (b * c - a * d);
    result->yy = a2 - b2 + c2 - d2;
    result->yz = 2.f * (c * d + a * b);
    result->yw = 0.f;

    result->zx = 2.f * (b * d + a * c);
    result->zy = 2.f * (c * d - a * b);
    result->zz = a2 - b2 - c2 + d2;
    result->zw = 0.f;

    result->wx = result->wy = result->wz = 0.f;
    result->ww = 1.f;
}

void matrix4x4_mul_quat(matrix4x4* result, matrix4x4* matrix, quaternion quat) {
    vector3 row;
    vector3 mul_result;

    row = make_vector3(matrix->xx, matrix->xy, matrix->xz);
    mul_result = quaternion_mul_vec3(quat, row);
    result->xx = mul_result.x;
    result->xy = mul_result.y;
    result->xz = mul_result.z;

    row = make_vector3(matrix->yx, matrix->yy, matrix->yz);
    mul_result = quaternion_mul_vec3(quat, row);
    result->yx = mul_result.x;
    result->yy = mul_result.y;
    result->yz = mul_result.z;

    row = make_vector3(matrix->zx, matrix->zy, matrix->zz);
    mul_result = quaternion_mul_vec3(quat, row);
    result->zx = mul_result.x;
    result->zy = mul_result.y;
    result->zz = mul_result.z;

    result->wx = result->wy = result->wz = 0.f;
    result->ww = 1.f;
}

quaternion quaternion_from_matrix4x4(matrix4x4* data) {
    float r = 0.f;
    int i;

    int perm[] = {0, 1, 2, 0, 1};
    int* p = perm;

    float matrix[4][4];
    get_gl_matrix4x4(matrix, data);

    for (i = 0; i < 3; i++) {
        float m = matrix[i][i];
        if (m < r)
            continue;
        m = r;
        p = &perm[i];
    }

    r = sqrtf(1.f + matrix[p[0]][p[0]] - matrix[p[1]][p[1]] - matrix[p[2]][p[2]]);

    quaternion quat;
    if (r < 1e-6) {
        quat.x = 1.f;
        quat.y = quat.z = quat.w = 0.f;
    } else {
        quat.x = r / 2.f;
        quat.y = (matrix[p[0]][p[1]] - matrix[p[1]][p[0]]) / (2.f * r);
        quat.z = (matrix[p[2]][p[0]] - matrix[p[0]][p[2]]) / (2.f * r);
        quat.w = (matrix[p[2]][p[1]] - matrix[p[1]][p[2]]) / (2.f * r);
    }

    return quat;
}

quaternion quaternion_from_euler(vector3 euler) {
    double cp = cos(euler.x * 0.5);
    double sp = sin(euler.x * 0.5);
    double cy = cos(euler.y * 0.5);
    double sy = sin(euler.y * 0.5);
    double cr = cos(euler.z * 0.5);
    double sr = sin(euler.z * 0.5);

    double x = cy * sr * cp - sy * cr * sp;
    double y = cy * cr * sp + sy * sr * cp;
    double z = sy * cr * cp - cy * sr * sp;
    double w = cy * cr * cp + sy * sr * sp;

    return make_quaternion(x, y, z, w);
}

vector3 quaternion_to_euler(quaternion quat) {
    double sinr = +2.0 * (quat.w * quat.x + quat.y * quat.z);
    double cosr = +1.0 - 2.0 * (quat.x * quat.x + quat.y) * quat.y;
    float x = atan2(sinr, cosr);

    float y;
    double sinp = +2.0 * (quat.w * quat.y - quat.z * quat.x);
    if (fabs(sinp) >= 1)
        y = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
    else
        y = asin(sinp);

    // yaw (z-axis rotation)
    double siny = +2.0 * (quat.w * quat.z + quat.x * quat.y);
    double cosy = +1.0 - 2.0 * (quat.y * quat.y + quat.z * quat.z);
    float z = atan2(siny, cosy);

    return make_vector3(x, y, z);
}

quaternion quaternion_normalize(quaternion quat) {
    vector4 vec = make_vector4(quat.x, quat.y, quat.z, quat.w);
    vec = vector4_norm(vec);
    return make_quaternion(vec.x, vec.y, vec.z, vec.w);
}

bool quaternion_compare(quaternion a, quaternion b) {
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w && b.w;
}

void quaternion_string(char* result, quaternion quat) {
    char fmt[] = "x: %f y: %f z: %f w: %f";
    sprintf(result, fmt, quat.x, quat.y, quat.z, quat.w);
}

// ########################## TRANSFORM ###############################

transform* make_transform() {
    transform* result = malloc(sizeof(transform));

    result->matrix = make_matrix4x4();
    result->position = vector3_zero();
    result->scale = vector3_one();
    result->rotation = quaternion_identity();
    result->forward = vector3_forward();
    result->right = vector3_right();
    result->up = vector3_up();

    return result;
}

void free_transform(transform* transform) {
    free_matrix4x4(transform->matrix);
    free(transform);
}

void transform_update_matrix(transform* transform) {
    matrix4x4 scale_matrix;
    set_matrix4x4_identity(&scale_matrix);
    matrix4x4_scale_anisio(&scale_matrix, &scale_matrix, transform->scale);

    matrix4x4 rotation_matrix;
    set_matrix4x4_data_from_quaternion(&rotation_matrix, transform->rotation);

    matrix4x4 translation_matrix;
    set_matrix4x4_identity(&translation_matrix);
    matrix4x4_translate(&translation_matrix, transform->position);

    set_matrix4x4_identity(transform->matrix);
    matrix4x4_mul(transform->matrix, &scale_matrix, &rotation_matrix);
    matrix4x4_mul(transform->matrix, transform->matrix, &translation_matrix);
}