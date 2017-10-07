//
// Created by Morpheus on 07-Oct-17.
//

#include <glfw/glfw3.h>
#include <cynical_video.h>

window* main_window;

vector2 get_frame_buffer_size();

bool video_init(init_video_options params) {
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* vid_mode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_RED_BITS, vid_mode->redBits);
    glfwWindowHint(GLFW_BLUE_BITS, vid_mode->blueBits);
    glfwWindowHint(GLFW_GREEN_BITS, vid_mode->greenBits);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE); // this sets the refresh rate to the highest

    // We don't set the context version here because GLFW will create one with the highest possible value

#ifdef CYNICAL_DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#else
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_FALSE);
#endif

    int width;
    int height;
    GLFWmonitor* monitor_to_use;

    if (params.window_settings.full_screen) {
        monitor_to_use = monitor;
    } else {
        if (params.hide_controls) {
            glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        } else {
            glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
        }

        if (params.resizable) {
            glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        } else {
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        }

        if (params.always_on_top) {
            glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
        } else {
            glfwWindowHint(GLFW_FLOATING, GLFW_FALSE);
        }

        if (params.max_resolution) {
            glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
        } else {
            glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
        }

        glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
        glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);

        monitor_to_use = NULL;
    }

    if (params.window_settings.use_vsync) {
        glfwSwapInterval(1);
    } else {
        glfwSwapInterval(0);
    }

    if (params.max_resolution) {
        width = vid_mode->width;
        height = vid_mode->height;
    } else {
        width = (int) params.window_settings.resolution.x;
        height = (int) params.window_settings.resolution.y;
    }

    GLFWwindow* glfw_main_window = glfwCreateWindow(width, height, params.window_settings.title, monitor_to_use, NULL);
    if (!glfw_main_window)
        return false;

    main_window = calloc(1, sizeof(window));
    main_window->glfw_main_window = glfw_main_window;
    main_window->settings = params.window_settings;

    if (!params.window_settings.full_screen) {
        vector2 win_pos = params.window_settings.window_position;
        glfwSetWindowPos(glfw_main_window, (int) roundf(win_pos.x), (int) roundf(win_pos.y));
    }

    glfwMakeContextCurrent(glfw_main_window);
    frame_buffer_updated(get_frame_buffer_size());

    return true;
}

void video_release() {
    glfwDestroyWindow(main_window->glfw_main_window);
    free(main_window);
}

void set_window_settings(window_settings opt) {
    main_window->settings = opt;

    const GLFWvidmode* vid_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    int width;
    int height;
    if (opt.max_resolution) {
        width = vid_mode->width;
        height = vid_mode->height;
    } else {
        width = (int) opt.resolution.x;
        height = (int) opt.resolution.y;
    }

    if (opt.full_screen) {

        GLFWmonitor* current_monitor = glfwGetWindowMonitor(main_window->glfw_main_window);
        if (current_monitor == NULL) {
            GLFWwindow* glfw_window = main_window->glfw_main_window;
            GLFWmonitor* monitor_to_use = glfwGetPrimaryMonitor();

            glfwSetWindowMonitor(glfw_window, monitor_to_use, 0, 0, width, height, vid_mode->refreshRate);
        } else {
            glfwSetWindowSize(main_window->glfw_main_window, width, height);
        }
    } else {

        if (opt.max_resolution) {
            glfwMaximizeWindow(main_window->glfw_main_window);
        } else {
            glfwSetWindowSize(main_window->glfw_main_window, width, height);
        }

        vector2 win_pos = opt.window_position;
        glfwSetWindowPos(main_window->glfw_main_window, (int) roundf(win_pos.x), (int) roundf(win_pos.y));
    }

    if (opt.use_vsync) {
        glfwSwapInterval(1);
    } else {
        glfwSwapInterval(0);
    }

    glfwSetWindowTitle(main_window->glfw_main_window, opt.title);
}

vector2 get_frame_buffer_size() {
    int buffer_width;
    int buffer_height;
    glfwGetFramebufferSize(main_window->glfw_main_window, &buffer_width, &buffer_height);
    return make_vector2(buffer_width, buffer_height);
}

void frame_buffer_updated(vector2 new_size) {
    main_window->frame_buffer_size = new_size;
    glViewport(0, 0, (int) main_window->frame_buffer_size.x, (int) main_window->frame_buffer_size.y);
}

void set_window_size(vector2 new_size) {
    glfwSetWindowSize(main_window->glfw_main_window, (int) new_size.x, (int) new_size.y);
    window_resized(new_size);
}

void window_resized(vector2 new_size) {
    main_window->settings.resolution = new_size;
}

void set_window_position(vector2 pos) {
    glfwSetWindowPos(main_window->glfw_main_window, (int) pos.x, (int) pos.y);
    window_moved(pos);
}

void window_moved(vector2 new_pos) {
    main_window->settings.window_position = new_pos;
}