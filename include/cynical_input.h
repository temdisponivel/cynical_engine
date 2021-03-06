//
// Created by Morpheus on 07-Oct-17.
//

#ifndef CYNICAL_ENGINE_CYNICAL_INPUT_H
#define CYNICAL_ENGINE_CYNICAL_INPUT_H

#include <stddef.h>
#include <cynical_includes.h>
#include "cynical_math.h"

#define KEY_SPACE              0
#define KEY_APOSTROPHE         1  /* ' */
#define KEY_COMMA              2  /* , */
#define KEY_MINUS              3  /* - */
#define KEY_PERIOD             4  /* . */
#define KEY_SLASH              5  /* / */
#define KEY_0                  6
#define KEY_1                  7
#define KEY_2                  8
#define KEY_3                  9
#define KEY_4                  10
#define KEY_5                  11
#define KEY_6                  12
#define KEY_7                  13
#define KEY_8                  14
#define KEY_9                  15
#define KEY_SEMICOLON          16  /* ; */
#define KEY_EQUAL              17  /* = */
#define KEY_A                  18
#define KEY_B                  19
#define KEY_C                  20
#define KEY_D                  21
#define KEY_E                  22
#define KEY_F                  23
#define KEY_G                  24
#define KEY_H                  25
#define KEY_I                  26
#define KEY_J                  27
#define KEY_K                  28
#define KEY_L                  29
#define KEY_M                  30
#define KEY_N                  31
#define KEY_O                  32
#define KEY_P                  33
#define KEY_Q                  34
#define KEY_R                  35
#define KEY_S                  36
#define KEY_T                  37
#define KEY_U                  38
#define KEY_V                  39
#define KEY_W                  40
#define KEY_X                  41
#define KEY_Y                  42
#define KEY_Z                  43
#define KEY_LEFT_BRACKET       44 /* [ */
#define KEY_BACKSLASH          45 /* \ */
#define KEY_RIGHT_BRACKET      46 /* ] */
#define KEY_GRAVE_ACCENT       47 /* ` */
#define KEY_WORLD_1            48 /* non-US #1 */
#define KEY_WORLD_2            49 /* non-US #2 */
#define KEY_ESCAPE             50
#define KEY_ENTER              51
#define KEY_TAB                52
#define KEY_BACKSPACE          53
#define KEY_INSERT             54
#define KEY_DELETE             55
#define KEY_RIGHT              56
#define KEY_LEFT               57
#define KEY_DOWN               58
#define KEY_UP                 59
#define KEY_PAGE_UP            60
#define KEY_PAGE_DOWN          61
#define KEY_HOME               62
#define KEY_END                63
#define KEY_CAPS_LOCK          64
#define KEY_SCROLL_LOCK        65
#define KEY_NUM_LOCK           66
#define KEY_PRINT_SCREEN       67
#define KEY_PAUSE              68
#define KEY_F1                 69
#define KEY_F2                 70
#define KEY_F3                 71
#define KEY_F4                 72
#define KEY_F5                 73
#define KEY_F6                 74
#define KEY_F7                 75
#define KEY_F8                 76
#define KEY_F9                 77
#define KEY_F10                78
#define KEY_F11                79
#define KEY_F12                80
#define KEY_F13                81
#define KEY_F14                82
#define KEY_F15                83
#define KEY_F16                84
#define KEY_F17                85
#define KEY_F18                86
#define KEY_F19                87
#define KEY_F20                88
#define KEY_F21                89
#define KEY_F22                90
#define KEY_F23                91
#define KEY_F24                92
#define KEY_F25                93
#define KEY_KP_0               94
#define KEY_KP_1               95
#define KEY_KP_2               96
#define KEY_KP_3               97
#define KEY_KP_4               98
#define KEY_KP_5               99
#define KEY_KP_6               100
#define KEY_KP_7               101
#define KEY_KP_8               102
#define KEY_KP_9               103
#define KEY_KP_DECIMAL         104
#define KEY_KP_DIVIDE          105
#define KEY_KP_MULTIPLY        106
#define KEY_KP_SUBTRACT        107
#define KEY_KP_ADD             108
#define KEY_KP_ENTER           109
#define KEY_KP_EQUAL           110
#define KEY_LEFT_SHIFT         111
#define KEY_LEFT_CONTROL       112
#define KEY_LEFT_ALT           113
#define KEY_LEFT_SUPER         114
#define KEY_RIGHT_SHIFT        115
#define KEY_RIGHT_CONTROL      116
#define KEY_RIGHT_ALT          117
#define KEY_RIGHT_SUPER        118
#define KEY_MENU               119

#define MOUSE_BUTTON_1         120
#define MOUSE_BUTTON_2         121
#define MOUSE_BUTTON_3         122
#define MOUSE_BUTTON_4         123
#define MOUSE_BUTTON_5         124
#define MOUSE_BUTTON_6         125
#define MOUSE_BUTTON_7         126
#define MOUSE_BUTTON_8         127
#define MOUSE_BUTTON_LEFT      MOUSE_BUTTON_1
#define MOUSE_BUTTON_RIGHT     MOUSE_BUTTON_2
#define MOUSE_BUTTON_MIDDLE    MOUSE_BUTTON_3

#define TOTAL_KEYS (MOUSE_BUTTON_8 + 1)

typedef enum {
    KEY_STATE_DOWN,
    KEY_STATE_UP,
    KEY_STATE_PRESSED,
    KEY_STATE_RELEASED,
} KEY_STATE_T;

typedef unsigned short key_code_t;

typedef struct input_state_s {
    KEY_STATE_T states[TOTAL_KEYS];

    vector2_t mouse_position;
    vector2_t last_mouse_position;

    vector2_t mouse_position_view_port;

    vector2_t mouse_scroll;
    vector2_t last_mouse_scroll;

    bool_t invert_y;
} input_state_t;

input_state_t* make_input_state();
void free_input_state(input_state_t* state);

void input_init();
void input_release();

void update_input_state();

KEY_STATE_T get_key_state(key_code_t key);

bool_t is_key_down(key_code_t key);
bool_t is_key_up(key_code_t key);

bool_t is_key_pressed(key_code_t key);
bool_t is_key_released(key_code_t key);

vector2_t get_mouse_position();
vector2_t get_mouse_view_port_position();
vector2_t get_mouse_delta();
vector2_t get_mouse_scroll();

#endif //CYNICAL_ENGINE_CYNICAL_INPUT_H