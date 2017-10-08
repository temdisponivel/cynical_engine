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
    bool full_screen;
    vector2 resolution;
    bool use_vsync;
    bool max_resolution;
    vector2 window_position;
} window_settings;

typedef struct window_s {
    GLFWwindow* glfw_main_window;
    window_settings settings;
    vector2 frame_buffer_size;
} window;

typedef struct video_options_s {
    window_settings window_settings;
    bool resizable;
    bool hide_controls;
    bool always_on_top;
    bool max_resolution;
} init_video_options;

window* main_window;

bool video_init(init_video_options params);

void video_release();

void set_window_settings(window_settings settings);

void frame_buffer_updated(vector2 new_size);

void set_window_size(vector2 new_size);

void window_resized(vector2 new_size);

void window_moved(vector2 new_pos);

void window_moved(vector2 new_pos);

#endif //CYNICAL_ENGINE_CYNICAL_WINDOW_H
