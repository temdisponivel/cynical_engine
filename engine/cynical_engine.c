//
// Created by Morpheus on 07-Oct-17.
//

#include <cynical_includes.h>
#include <cynical_video.h>
#include <cynical_input.h>
#include <cynical_time.h>
#include <cynical_engine.h>
#include <cynical_memory.h>
#include <cynical_render.h>

#define FRAME_MEMORY_TOTAL_SIZE ((1024 * 1024) * 5)

int engine_error_code;
int glfw_error_code;
char* engine_error_description;

engine_state_t main_engine_state;

update_callback_t main_update_callback;
draw_callback_t main_draw_callback;

static void error_callback(int error, const char* description) {
    error = ERROR_GLFW;
    glfw_error_code = error;
    engine_error_description = (char*) description;
    ERROR(description);
    exit(EXIT_FAILURE);
}

bool_t engine_init(const update_callback_t update, const draw_callback_t draw) {

    ASSERT(update);
    ASSERT(draw);

    main_update_callback = update;
    main_draw_callback = draw;

    glfwSetErrorCallback(&error_callback);

    if (!glfwInit()) {
        engine_error_code = ERROR_GLFW_INIT;
        return false;
    }

    frame_memory_init(FRAME_MEMORY_TOTAL_SIZE);

    // TODO: read this from file or string or something
    init_video_options_t video_options;
    video_options.window_settings.window_position = make_vector2(100, 200);
    video_options.window_settings.full_screen = false;
    video_options.window_settings.use_vsync = true;
    video_options.window_settings.resolution = make_vector2(1024, 768);
    video_options.resizable = true;
    video_options.hide_controls = false;
    video_options.always_on_top = false;
    video_options.window_settings.title = "Cynical Engine Window!";
    video_options.max_resolution = false;

    if (!video_init(video_options)) {
        engine_error_code = ERROR_VIDEO_INIT;
        return false;
    }

    GLenum error = glewInit();
    if (error != GL_NO_ERROR) {
        engine_error_code = ERROR_GLEW_INIT;
        engine_error_description = (char*) glewGetErrorString(error);
        return false;
    }

    render_init();
    input_init();
    time_init();

    return true;
}

void engine_release() {
    input_release();
    time_release();
    render_release();
    video_release();
    frame_memory_release();
    glfwTerminate();
}

void run_loop() {
    while (!main_engine_state.quit) {
        frame_memory_reset_allocator();

        if (main_engine_state.paused) {

            // on pause, we do this stuff to prevent the window from freezing
            time_start_frame();
            glfwPollEvents();
            time_end_frame();

        } else {
            run_one_frame();
        }
    }
}

void run_one_frame() {
    time_start_frame();

    glfwPollEvents();
    update_input_state();

    main_update_callback();
    main_draw_callback();

    time_end_frame();
}

void toggle_pause() {
    if (main_engine_state.paused) {
        unpause();
    } else {
        pause();
    }
}

void pause() {
    main_engine_state.paused = true;
}

void unpause() {
    main_engine_state.paused = true;
}

engine_state_t get_engine_state() {
    return main_engine_state;
}

void quit() {
    main_engine_state.quit = true;
}