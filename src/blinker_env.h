//  blinker_env.h
//  blinker

#ifndef BLINKER_ENV_H
#define BLINKER_ENV_H

#include <stdio.h>

/* Types */

typedef struct blinker_env_s *blinker_env_h;

typedef enum {
    blinker_env_lever_pos_up = 0,
    blinker_env_lever_pos_center = 1,
    blinker_env_lever_pos_down = 2,
} blinker_env_lever_pos_t;

typedef struct {
    int blinker_left_on;
    int blinker_right_on;
    int warning_indicator_on;
    blinker_env_lever_pos_t blinker_lever_pos;
    int wheel_pos;
} blinker_env_actuator_state_t;

typedef struct {
    int blinker_lever_move;
    int blinker_warning_pushed;
    int rotation;  
} blinker_env_input_t;

typedef enum {
    blinker_env_sensor_state_nothing,
    blinker_env_sensor_state_quit,
    blinker_env_sensor_state_blinker_lever_up,
    blinker_env_sensor_state_blinker_lever_down,
    blinker_env_sensor_state_warn_toggle,
    blinker_env_sensor_state_rotate_counter_clock,
    blinker_env_sensor_state_rotate_clock
} blinker_env_sensor_state_t;

/* Construction */

blinker_env_h blinker_env_make(void);

void blinker_env_destroy(blinker_env_h self);

/* Main API */

void blinker_env_actuate(blinker_env_h self, blinker_env_actuator_state_t *state);

blinker_env_sensor_state_t blinker_env_sense(blinker_env_h self);
void blinker_env_sense_all(blinker_env_h self, blinker_env_input_t *inputs);

/* Globals */
extern blinker_env_actuator_state_t actuator_state;
extern blinker_env_input_t sensor_input;


#endif /* BLINKER_ENV_H */
