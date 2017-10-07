//
// Created by Morpheus on 07-Oct-17.
//

#include <mem.h>
#include <cynical_log.h>
#include "cynical_input.h"

input_state* main_input_state;
GLFWwindow* input_window;

input_state* make_input_state() {
    input_state* state = malloc(sizeof(input_state));
    for (int i = 0; i < TOTAL_KEYS; ++i) {
        state->states[i] = KEY_STATE_RELEASED;
    }
    return state;
}

void free_input_state(input_state* state) {
    free(state);
}

void update_input_state() {

    int current;
    KEY_STATE previous;
    KEY_STATE updated;

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

    UPDATE_KEY(input_window, KEY_SPACE, false);
    UPDATE_KEY(input_window, KEY_APOSTROPHE, false);
    UPDATE_KEY(input_window, KEY_COMMA, false);
    UPDATE_KEY(input_window, KEY_MINUS, false);
    UPDATE_KEY(input_window, KEY_PERIOD, false);
    UPDATE_KEY(input_window, KEY_SLASH, false);
    UPDATE_KEY(input_window, KEY_0, false);
    UPDATE_KEY(input_window, KEY_1, false);
    UPDATE_KEY(input_window, KEY_2, false);
    UPDATE_KEY(input_window, KEY_3, false);
    UPDATE_KEY(input_window, KEY_4, false);
    UPDATE_KEY(input_window, KEY_5, false);
    UPDATE_KEY(input_window, KEY_6, false);
    UPDATE_KEY(input_window, KEY_7, false);
    UPDATE_KEY(input_window, KEY_8, false);
    UPDATE_KEY(input_window, KEY_9, false);
    UPDATE_KEY(input_window, KEY_SEMICOLON, false);
    UPDATE_KEY(input_window, KEY_EQUAL, false);
    UPDATE_KEY(input_window, KEY_A, false);
    UPDATE_KEY(input_window, KEY_B, false);
    UPDATE_KEY(input_window, KEY_C, false);
    UPDATE_KEY(input_window, KEY_D, false);
    UPDATE_KEY(input_window, KEY_E, false);
    UPDATE_KEY(input_window, KEY_F, false);
    UPDATE_KEY(input_window, KEY_G, false);
    UPDATE_KEY(input_window, KEY_H, false);
    UPDATE_KEY(input_window, KEY_I, false);
    UPDATE_KEY(input_window, KEY_J, false);
    UPDATE_KEY(input_window, KEY_K, false);
    UPDATE_KEY(input_window, KEY_L, false);
    UPDATE_KEY(input_window, KEY_M, false);
    UPDATE_KEY(input_window, KEY_N, false);
    UPDATE_KEY(input_window, KEY_O, false);
    UPDATE_KEY(input_window, KEY_P, false);
    UPDATE_KEY(input_window, KEY_Q, false);
    UPDATE_KEY(input_window, KEY_R, false);
    UPDATE_KEY(input_window, KEY_S, false);
    UPDATE_KEY(input_window, KEY_T, false);
    UPDATE_KEY(input_window, KEY_U, false);
    UPDATE_KEY(input_window, KEY_V, false);
    UPDATE_KEY(input_window, KEY_W, false);
    UPDATE_KEY(input_window, KEY_X, false);
    UPDATE_KEY(input_window, KEY_Y, false);
    UPDATE_KEY(input_window, KEY_Z, false);
    UPDATE_KEY(input_window, KEY_LEFT_BRACKET, false);
    UPDATE_KEY(input_window, KEY_BACKSLASH, false);
    UPDATE_KEY(input_window, KEY_RIGHT_BRACKET, false);
    UPDATE_KEY(input_window, KEY_GRAVE_ACCENT, false);
    UPDATE_KEY(input_window, KEY_WORLD_1, false);
    UPDATE_KEY(input_window, KEY_WORLD_2, false);
    UPDATE_KEY(input_window, KEY_ESCAPE, false);
    UPDATE_KEY(input_window, KEY_ENTER, false);
    UPDATE_KEY(input_window, KEY_TAB, false);
    UPDATE_KEY(input_window, KEY_BACKSPACE, false);
    UPDATE_KEY(input_window, KEY_INSERT, false);
    UPDATE_KEY(input_window, KEY_DELETE, false);
    UPDATE_KEY(input_window, KEY_RIGHT, false);
    UPDATE_KEY(input_window, KEY_LEFT, false);
    UPDATE_KEY(input_window, KEY_DOWN, false);
    UPDATE_KEY(input_window, KEY_UP, false);
    UPDATE_KEY(input_window, KEY_PAGE_UP, false);
    UPDATE_KEY(input_window, KEY_PAGE_DOWN, false);
    UPDATE_KEY(input_window, KEY_HOME, false);
    UPDATE_KEY(input_window, KEY_END, false);
    UPDATE_KEY(input_window, KEY_CAPS_LOCK, false);
    UPDATE_KEY(input_window, KEY_SCROLL_LOCK, false);
    UPDATE_KEY(input_window, KEY_NUM_LOCK, false);
    UPDATE_KEY(input_window, KEY_PRINT_SCREEN, false);
    UPDATE_KEY(input_window, KEY_PAUSE, false);
    UPDATE_KEY(input_window, KEY_F1, false);
    UPDATE_KEY(input_window, KEY_F2, false);
    UPDATE_KEY(input_window, KEY_F3, false);
    UPDATE_KEY(input_window, KEY_F4, false);
    UPDATE_KEY(input_window, KEY_F5, false);
    UPDATE_KEY(input_window, KEY_F6, false);
    UPDATE_KEY(input_window, KEY_F7, false);
    UPDATE_KEY(input_window, KEY_F8, false);
    UPDATE_KEY(input_window, KEY_F9, false);
    UPDATE_KEY(input_window, KEY_F10, false);
    UPDATE_KEY(input_window, KEY_F11, false);
    UPDATE_KEY(input_window, KEY_F12, false);
    UPDATE_KEY(input_window, KEY_F13, false);
    UPDATE_KEY(input_window, KEY_F14, false);
    UPDATE_KEY(input_window, KEY_F15, false);
    UPDATE_KEY(input_window, KEY_F16, false);
    UPDATE_KEY(input_window, KEY_F17, false);
    UPDATE_KEY(input_window, KEY_F18, false);
    UPDATE_KEY(input_window, KEY_F19, false);
    UPDATE_KEY(input_window, KEY_F20, false);
    UPDATE_KEY(input_window, KEY_F21, false);
    UPDATE_KEY(input_window, KEY_F22, false);
    UPDATE_KEY(input_window, KEY_F23, false);
    UPDATE_KEY(input_window, KEY_F24, false);
    UPDATE_KEY(input_window, KEY_F25, false);
    UPDATE_KEY(input_window, KEY_KP_0, false);
    UPDATE_KEY(input_window, KEY_KP_1, false);
    UPDATE_KEY(input_window, KEY_KP_2, false);
    UPDATE_KEY(input_window, KEY_KP_3, false);
    UPDATE_KEY(input_window, KEY_KP_4, false);
    UPDATE_KEY(input_window, KEY_KP_5, false);
    UPDATE_KEY(input_window, KEY_KP_6, false);
    UPDATE_KEY(input_window, KEY_KP_7, false);
    UPDATE_KEY(input_window, KEY_KP_8, false);
    UPDATE_KEY(input_window, KEY_KP_9, false);
    UPDATE_KEY(input_window, KEY_KP_DECIMAL, false);
    UPDATE_KEY(input_window, KEY_KP_DIVIDE, false);
    UPDATE_KEY(input_window, KEY_KP_MULTIPLY, false);
    UPDATE_KEY(input_window, KEY_KP_SUBTRACT, false);
    UPDATE_KEY(input_window, KEY_KP_ADD, false);
    UPDATE_KEY(input_window, KEY_KP_ENTER, false);
    UPDATE_KEY(input_window, KEY_KP_EQUAL, false);
    UPDATE_KEY(input_window, KEY_LEFT_SHIFT, false);
    UPDATE_KEY(input_window, KEY_LEFT_CONTROL, false);
    UPDATE_KEY(input_window, KEY_LEFT_ALT, false);
    UPDATE_KEY(input_window, KEY_LEFT_SUPER, false);
    UPDATE_KEY(input_window, KEY_RIGHT_SHIFT, false);
    UPDATE_KEY(input_window, KEY_RIGHT_CONTROL, false);
    UPDATE_KEY(input_window, KEY_RIGHT_ALT, false);
    UPDATE_KEY(input_window, KEY_RIGHT_SUPER, false);
    UPDATE_KEY(input_window, KEY_MENU, false);

    UPDATE_KEY(input_window, MOUSE_BUTTON_1, true);
    UPDATE_KEY(input_window, MOUSE_BUTTON_2, true);
    UPDATE_KEY(input_window, MOUSE_BUTTON_3, true);
    UPDATE_KEY(input_window, MOUSE_BUTTON_4, true);
    UPDATE_KEY(input_window, MOUSE_BUTTON_5, true);
    UPDATE_KEY(input_window, MOUSE_BUTTON_6, true);
    UPDATE_KEY(input_window, MOUSE_BUTTON_7, true);
    UPDATE_KEY(input_window, MOUSE_BUTTON_8, true);

    double x, y;
    glfwGetCursorPos(input_window, &x, &y);
    x = normalize((float) x, 0, 800);
    y = normalize((float) y, 0, 600);
    main_input_state->mouse_position = make_vector2((float) x, (float) y);
}

KEY_STATE get_key_state(key_code key) {
    if (key >= TOTAL_KEYS)
        key = TOTAL_KEYS - 1;

    return main_input_state->states[key];
}

bool is_key_down(key_code key) {
    return get_key_state(key) == KEY_STATE_DOWN;
}

bool is_key_up(key_code key) {
    return get_key_state(key) == KEY_STATE_UP;
}

bool is_key_pressed(key_code key) {
    return get_key_state(key) == KEY_STATE_PRESSED;
}

bool is_key_released(key_code key) {
    return get_key_state(key) == KEY_STATE_RELEASED;
}
