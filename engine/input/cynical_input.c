//
// Created by Morpheus on 07-Oct-17.
//

#include <mem.h>
#include <cynical_debug.h>
#include <cynical_video.h>
#include <cynical_engine.h>
#include "cynical_input.h"

input_state_t* main_input_state;

void scroll_callback(GLFWwindow* window, double x_offset, double y_offset);

void frame_buffer_resized_callback(GLFWwindow* window, int width, int height);

void window_resized_callback(GLFWwindow* window, int width, int height);

void window_position_changed_callback(GLFWwindow* window, int x, int y);

input_state_t* make_input_state() {
    input_state_t* state = malloc(sizeof(input_state_t));
    for (int i = 0; i < TOTAL_KEYS; ++i) {
        state->states[i] = KEY_STATE_RELEASED;
    }
    state->invert_y = true;
    return state;
}

void free_input_state(input_state_t* state) {
    free(state);
}

void input_init() {
    main_input_state = make_input_state();
    glfwSetScrollCallback(main_window->glfw_main_window, &scroll_callback);
    glfwSetWindowSizeCallback(main_window->glfw_main_window, &window_resized_callback);
    glfwSetFramebufferSizeCallback(main_window->glfw_main_window, &frame_buffer_resized_callback);
}

void input_release() {
    free_input_state(main_input_state);
    glfwSetScrollCallback(main_window->glfw_main_window, NULL);
    glfwSetWindowSizeCallback(main_window->glfw_main_window, NULL);
    glfwSetFramebufferSizeCallback(main_window->glfw_main_window, NULL);
}

void update_key_and_mouse() {

#define UPDATE_KEY(WINDOW, KEY, IS_MOUSE) {\
    if (IS_MOUSE)\
        current = glfwGetMouseButton(WINDOW,GLFW_##KEY);\
    else\
        current = glfwGetKey(WINDOW,GLFW_##KEY);\
    previous = main_input_state->states[KEY];\
    updated = previous;\
\
    if (current == GLFW_PRESS) {\
        if (previous == KEY_STATE_RELEASED || previous == KEY_STATE_UP) {\
            updated = KEY_STATE_DOWN;\
        }\
        else if (previous == KEY_STATE_DOWN) {\
            updated = KEY_STATE_PRESSED;\
        }\
    } else if (current == GLFW_RELEASE){\
        if (previous == KEY_STATE_PRESSED || previous == KEY_STATE_DOWN)\
            updated = KEY_STATE_UP;\
        else if (previous == KEY_STATE_UP)\
            updated = KEY_STATE_RELEASED;\
    }\
    if (updated != previous)\
        main_input_state->states[KEY] = updated;\
}\

    int current;
    KEY_STATE_T previous;
    KEY_STATE_T updated;

    GLFWwindow* glfw_main_window = main_window->glfw_main_window;

    UPDATE_KEY(glfw_main_window, KEY_SPACE, false);
    UPDATE_KEY(glfw_main_window, KEY_APOSTROPHE, false);
    UPDATE_KEY(glfw_main_window, KEY_COMMA, false);
    UPDATE_KEY(glfw_main_window, KEY_MINUS, false);
    UPDATE_KEY(glfw_main_window, KEY_PERIOD, false);
    UPDATE_KEY(glfw_main_window, KEY_SLASH, false);
    UPDATE_KEY(glfw_main_window, KEY_0, false);
    UPDATE_KEY(glfw_main_window, KEY_1, false);
    UPDATE_KEY(glfw_main_window, KEY_2, false);
    UPDATE_KEY(glfw_main_window, KEY_3, false);
    UPDATE_KEY(glfw_main_window, KEY_4, false);
    UPDATE_KEY(glfw_main_window, KEY_5, false);
    UPDATE_KEY(glfw_main_window, KEY_6, false);
    UPDATE_KEY(glfw_main_window, KEY_7, false);
    UPDATE_KEY(glfw_main_window, KEY_8, false);
    UPDATE_KEY(glfw_main_window, KEY_9, false);
    UPDATE_KEY(glfw_main_window, KEY_SEMICOLON, false);
    UPDATE_KEY(glfw_main_window, KEY_EQUAL, false);
    UPDATE_KEY(glfw_main_window, KEY_A, false);
    UPDATE_KEY(glfw_main_window, KEY_B, false);
    UPDATE_KEY(glfw_main_window, KEY_C, false);
    UPDATE_KEY(glfw_main_window, KEY_D, false);
    UPDATE_KEY(glfw_main_window, KEY_E, false);
    UPDATE_KEY(glfw_main_window, KEY_F, false);
    UPDATE_KEY(glfw_main_window, KEY_G, false);
    UPDATE_KEY(glfw_main_window, KEY_H, false);
    UPDATE_KEY(glfw_main_window, KEY_I, false);
    UPDATE_KEY(glfw_main_window, KEY_J, false);
    UPDATE_KEY(glfw_main_window, KEY_K, false);
    UPDATE_KEY(glfw_main_window, KEY_L, false);
    UPDATE_KEY(glfw_main_window, KEY_M, false);
    UPDATE_KEY(glfw_main_window, KEY_N, false);
    UPDATE_KEY(glfw_main_window, KEY_O, false);
    UPDATE_KEY(glfw_main_window, KEY_P, false);
    UPDATE_KEY(glfw_main_window, KEY_Q, false);
    UPDATE_KEY(glfw_main_window, KEY_R, false);
    UPDATE_KEY(glfw_main_window, KEY_S, false);
    UPDATE_KEY(glfw_main_window, KEY_T, false);
    UPDATE_KEY(glfw_main_window, KEY_U, false);
    UPDATE_KEY(glfw_main_window, KEY_V, false);
    UPDATE_KEY(glfw_main_window, KEY_W, false);
    UPDATE_KEY(glfw_main_window, KEY_X, false);
    UPDATE_KEY(glfw_main_window, KEY_Y, false);
    UPDATE_KEY(glfw_main_window, KEY_Z, false);
    UPDATE_KEY(glfw_main_window, KEY_LEFT_BRACKET, false);
    UPDATE_KEY(glfw_main_window, KEY_BACKSLASH, false);
    UPDATE_KEY(glfw_main_window, KEY_RIGHT_BRACKET, false);
    UPDATE_KEY(glfw_main_window, KEY_GRAVE_ACCENT, false);
    UPDATE_KEY(glfw_main_window, KEY_WORLD_1, false);
    UPDATE_KEY(glfw_main_window, KEY_WORLD_2, false);
    UPDATE_KEY(glfw_main_window, KEY_ESCAPE, false);
    UPDATE_KEY(glfw_main_window, KEY_ENTER, false);
    UPDATE_KEY(glfw_main_window, KEY_TAB, false);
    UPDATE_KEY(glfw_main_window, KEY_BACKSPACE, false);
    UPDATE_KEY(glfw_main_window, KEY_INSERT, false);
    UPDATE_KEY(glfw_main_window, KEY_DELETE, false);
    UPDATE_KEY(glfw_main_window, KEY_RIGHT, false);
    UPDATE_KEY(glfw_main_window, KEY_LEFT, false);
    UPDATE_KEY(glfw_main_window, KEY_DOWN, false);
    UPDATE_KEY(glfw_main_window, KEY_UP, false);
    UPDATE_KEY(glfw_main_window, KEY_PAGE_UP, false);
    UPDATE_KEY(glfw_main_window, KEY_PAGE_DOWN, false);
    UPDATE_KEY(glfw_main_window, KEY_HOME, false);
    UPDATE_KEY(glfw_main_window, KEY_END, false);
    UPDATE_KEY(glfw_main_window, KEY_CAPS_LOCK, false);
    UPDATE_KEY(glfw_main_window, KEY_SCROLL_LOCK, false);
    UPDATE_KEY(glfw_main_window, KEY_NUM_LOCK, false);
    UPDATE_KEY(glfw_main_window, KEY_PRINT_SCREEN, false);
    UPDATE_KEY(glfw_main_window, KEY_PAUSE, false);
    UPDATE_KEY(glfw_main_window, KEY_F1, false);
    UPDATE_KEY(glfw_main_window, KEY_F2, false);
    UPDATE_KEY(glfw_main_window, KEY_F3, false);
    UPDATE_KEY(glfw_main_window, KEY_F4, false);
    UPDATE_KEY(glfw_main_window, KEY_F5, false);
    UPDATE_KEY(glfw_main_window, KEY_F6, false);
    UPDATE_KEY(glfw_main_window, KEY_F7, false);
    UPDATE_KEY(glfw_main_window, KEY_F8, false);
    UPDATE_KEY(glfw_main_window, KEY_F9, false);
    UPDATE_KEY(glfw_main_window, KEY_F10, false);
    UPDATE_KEY(glfw_main_window, KEY_F11, false);
    UPDATE_KEY(glfw_main_window, KEY_F12, false);
    UPDATE_KEY(glfw_main_window, KEY_F13, false);
    UPDATE_KEY(glfw_main_window, KEY_F14, false);
    UPDATE_KEY(glfw_main_window, KEY_F15, false);
    UPDATE_KEY(glfw_main_window, KEY_F16, false);
    UPDATE_KEY(glfw_main_window, KEY_F17, false);
    UPDATE_KEY(glfw_main_window, KEY_F18, false);
    UPDATE_KEY(glfw_main_window, KEY_F19, false);
    UPDATE_KEY(glfw_main_window, KEY_F20, false);
    UPDATE_KEY(glfw_main_window, KEY_F21, false);
    UPDATE_KEY(glfw_main_window, KEY_F22, false);
    UPDATE_KEY(glfw_main_window, KEY_F23, false);
    UPDATE_KEY(glfw_main_window, KEY_F24, false);
    UPDATE_KEY(glfw_main_window, KEY_F25, false);
    UPDATE_KEY(glfw_main_window, KEY_KP_0, false);
    UPDATE_KEY(glfw_main_window, KEY_KP_1, false);
    UPDATE_KEY(glfw_main_window, KEY_KP_2, false);
    UPDATE_KEY(glfw_main_window, KEY_KP_3, false);
    UPDATE_KEY(glfw_main_window, KEY_KP_4, false);
    UPDATE_KEY(glfw_main_window, KEY_KP_5, false);
    UPDATE_KEY(glfw_main_window, KEY_KP_6, false);
    UPDATE_KEY(glfw_main_window, KEY_KP_7, false);
    UPDATE_KEY(glfw_main_window, KEY_KP_8, false);
    UPDATE_KEY(glfw_main_window, KEY_KP_9, false);
    UPDATE_KEY(glfw_main_window, KEY_KP_DECIMAL, false);
    UPDATE_KEY(glfw_main_window, KEY_KP_DIVIDE, false);
    UPDATE_KEY(glfw_main_window, KEY_KP_MULTIPLY, false);
    UPDATE_KEY(glfw_main_window, KEY_KP_SUBTRACT, false);
    UPDATE_KEY(glfw_main_window, KEY_KP_ADD, false);
    UPDATE_KEY(glfw_main_window, KEY_KP_ENTER, false);
    UPDATE_KEY(glfw_main_window, KEY_KP_EQUAL, false);
    UPDATE_KEY(glfw_main_window, KEY_LEFT_SHIFT, false);
    UPDATE_KEY(glfw_main_window, KEY_LEFT_CONTROL, false);
    UPDATE_KEY(glfw_main_window, KEY_LEFT_ALT, false);
    UPDATE_KEY(glfw_main_window, KEY_LEFT_SUPER, false);
    UPDATE_KEY(glfw_main_window, KEY_RIGHT_SHIFT, false);
    UPDATE_KEY(glfw_main_window, KEY_RIGHT_CONTROL, false);
    UPDATE_KEY(glfw_main_window, KEY_RIGHT_ALT, false);
    UPDATE_KEY(glfw_main_window, KEY_RIGHT_SUPER, false);
    UPDATE_KEY(glfw_main_window, KEY_MENU, false);

    UPDATE_KEY(glfw_main_window, MOUSE_BUTTON_1, true);
    UPDATE_KEY(glfw_main_window, MOUSE_BUTTON_2, true);
    UPDATE_KEY(glfw_main_window, MOUSE_BUTTON_3, true);
    UPDATE_KEY(glfw_main_window, MOUSE_BUTTON_4, true);
    UPDATE_KEY(glfw_main_window, MOUSE_BUTTON_5, true);
    UPDATE_KEY(glfw_main_window, MOUSE_BUTTON_6, true);
    UPDATE_KEY(glfw_main_window, MOUSE_BUTTON_7, true);
    UPDATE_KEY(glfw_main_window, MOUSE_BUTTON_8, true);

    main_input_state->last_mouse_scroll = main_input_state->mouse_scroll;
    main_input_state->mouse_scroll = vector2_zero();

    main_input_state->last_mouse_position = main_input_state->mouse_position;

    double x, y;
    glfwGetCursorPos(glfw_main_window, &x, &y);

    main_input_state->mouse_position = make_vector2((float) x, (float) y);
    if (main_input_state->invert_y)
        main_input_state->mouse_position.y = main_input_state->mouse_position.y * -1.f;

    float x_norm = normalize((float) x, 0, main_window->frame_buffer_size.x);
    float y_norm = normalize((float) y, 0, main_window->frame_buffer_size.y);

    main_input_state->mouse_position_view_port = make_vector2((x_norm * 2.f) - 1.f, (y_norm * 2.f) - 1.f);
    if (main_input_state->invert_y)
        main_input_state->mouse_position_view_port.y = main_input_state->mouse_position_view_port.y * -1.f;
}

void update_input_state() {
    if (glfwWindowShouldClose(main_window->glfw_main_window)) {
        quit();
    } else {
        update_key_and_mouse();
    }
}

KEY_STATE_T get_key_state(key_code_t key) {
    if (key >= TOTAL_KEYS)
        key = TOTAL_KEYS - 1;

    return main_input_state->states[key];
}

bool_t is_key_down(key_code_t key) {
    return get_key_state(key) == KEY_STATE_DOWN;
}

bool_t is_key_up(key_code_t key) {
    return get_key_state(key) == KEY_STATE_UP;
}

bool_t is_key_pressed(key_code_t key) {
    return get_key_state(key) == KEY_STATE_PRESSED;
}

bool_t is_key_released(key_code_t key) {
    return get_key_state(key) == KEY_STATE_RELEASED;
}

vector2_t get_mouse_position() {
    return main_input_state->mouse_position;
}

vector2_t get_mouse_view_port_position() {
    return main_input_state->mouse_position_view_port;
}

vector2_t get_mouse_delta() {
    return vector2_sub(main_input_state->mouse_position, main_input_state->last_mouse_position);
}

vector2_t get_mouse_scroll() {
    return vector2_sub(main_input_state->mouse_scroll, main_input_state->last_mouse_scroll);
}

void scroll_callback(GLFWwindow* window, double x_offset, double y_offset) {
    main_input_state->mouse_scroll = make_vector2((float) x_offset, (float) y_offset);
}

void frame_buffer_resized_callback(GLFWwindow* window, int width, int height) {
    frame_buffer_updated(make_vector2(width, height));
}

void window_resized_callback(GLFWwindow* window, int width, int height) {
    window_resized(make_vector2(width, height));
}

void window_position_changed_callback(GLFWwindow* window, int x, int y) {
    window_moved(make_vector2(x, y));
}