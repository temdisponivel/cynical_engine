//
// Created by Morpheus on 07-Oct-17.
//

#ifndef CYNICAL_ENGINE_CYNICAL_VIDEO_H
#define CYNICAL_ENGINE_CYNICAL_VIDEO_H

#include <cynical_includes.h>
#include <math.h>
#include "cynical_math.h"

typedef struct window_settings_s {
    char* title;
    bool_t full_screen;
    vector2_t resolution;
    bool_t use_vsync;
    bool_t max_resolution;
    vector2_t window_position;
} window_settings_t;

typedef struct window_s {
    GLFWwindow* glfw_main_window;
    window_settings_t settings;
    vector2_t frame_buffer_size;
} window_t;

typedef struct video_options_s {
    window_settings_t window_settings;
    bool_t resizable;
    bool_t hide_controls;
    bool_t always_on_top;
    bool_t max_resolution;
} init_video_options_t;

window_t* main_window;

bool_t video_init(init_video_options_t params);

void video_release();

void set_window_settings(window_settings_t settings);

void frame_buffer_updated(vector2_t new_size);

void set_window_size(vector2_t new_size);

void window_resized(vector2_t new_size);

void window_moved(vector2_t new_pos);

void window_moved(vector2_t new_pos);

#endif //CYNICAL_ENGINE_CYNICAL_WINDOW_H
