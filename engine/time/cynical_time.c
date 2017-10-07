//
// Created by Morpheus on 07-Oct-17.
//

#include <malloc.h>
#include <glfw/glfw3.h>
#include <math.h>
#include <time.h>
#include <cynical_math.h>
#include "cynical_time.h"

time_state* main_time_state;

time_state* make_time_state() {
    time_state* result = calloc(1, sizeof(time_state));
    return result;
}

void free_time_state(time_state* state) {
    free(state);
}

void time_init() {
    main_time_state = make_time_state();
    main_time_state->time_scale = 1;
    main_time_state->frame_cap = 999999;
}

void time_release() {
    free_time_state(main_time_state);
}

void update_time() {
    float unscaled = (float) glfwGetTime();
    main_time_state->unscaled_time = unscaled;
    main_time_state->time = unscaled * main_time_state->time_scale;
}

void time_start_frame() {
    update_time();
    main_time_state->current_frame_start_time = main_time_state->unscaled_time;
}

void time_end_frame() {
    update_time();
    double end_frame_time = main_time_state->unscaled_time;

    float delta = (float) (end_frame_time - main_time_state->current_frame_start_time);
    float desired_delta = 1.f / main_time_state->frame_cap;
    float delta_diff = desired_delta - delta;
    if (delta_diff > 0) {
        time_sleep(delta_diff);
        delta += delta_diff;
    }

    main_time_state->unscaled_delta_time = delta;
    main_time_state->delta_time = delta * main_time_state->time_scale;
    main_time_state->current_refresh_rate = (int) roundf(1.f / delta);
}

void time_sleep(float seconds) {
    struct timespec spec;
    spec.tv_nsec = (int) roundf(seconds * SECONDS_TO_NANO); // transforms seconds into nano
    spec.tv_sec = 0;
    nanosleep(&spec, NULL);
}

double get_time() {
    return main_time_state->time;
}

double get_unescaled_time() {
    return main_time_state->unscaled_time;
}

float get_delta_time() {
    return main_time_state->delta_time;
}

float get_unescaled_delta_time() {
    return main_time_state->unscaled_delta_time;
}

float get_time_scale() {
    return main_time_state->time_scale;
}

void set_time_scale(float scale) {
    main_time_state->time_scale = scale;
}

void set_frame_cap(int cap) {
    main_time_state->frame_cap = cap;
}

int get_frame_cap() {
    return main_time_state->frame_cap;
}