//
// Created by Morpheus on 07-Oct-17.
//

#ifndef CYNICAL_ENGINE_CYNICAL_ENGINE_H
#define CYNICAL_ENGINE_CYNICAL_ENGINE_H

#include "cynical_math.h"

int engine_error_code;
int glfw_error_code;
char* engine_error_description;

#define ERROR_GLFW_INIT 1
#define ERROR_VIDEO_INIT 2
#define ERROR_GLEW_INIT 3
#define ERROR_GLFW 4

typedef struct engine_state_s {
    bool paused;
    bool quit;
} engine_state;

typedef void (* update_callback)();

typedef void (* draw_callback)();

bool engine_init(update_callback update, draw_callback draw);

void engine_release();

void run_loop();

void toggle_pause();

void pause();

void unpause();

void run_one_frame();

engine_state get_engine_state();

void quit();

#endif //CYNICAL_ENGINE_CYNICAL_ENGINE_H
