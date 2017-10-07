//
// Created by Morpheus on 07-Oct-17.
//

#ifndef CYNICAL_ENGINE_CYNICAL_TIME_H
#define CYNICAL_ENGINE_CYNICAL_TIME_H

typedef struct time_state_s {
    float delta_time;
    double time;

    float time_scale;

    float unscaled_delta_time;
    double unscaled_time;

    double current_frame_start_time;
    double current_frame_end_time;

    int current_refresh_rate;
    int frame_cap;
} time_state;

time_state* make_time_state();

void free_time_state(time_state* state);

void time_init();

void time_release();

void time_start_frame();

void time_end_frame();

void time_sleep(float seconds);

double get_time();
double get_unescaled_time();

float get_delta_time();
float get_unescaled_delta_time();

float get_time_scale();
void set_time_scale(float scale);

void set_frame_cap(int cap);
int get_frame_cap();

#endif //CYNICAL_ENGINE_CYNICAL_TIME_H
