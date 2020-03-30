//  main.c
//  blinker

/* Includes */

#include "blinker_env.h"
#include "blech/blinker.c"
#include "blech.h"
#include <stdio.h>
#include <unistd.h>

/* Constants */

static const blc_int32 rotation_increment = 1; /* 1 degree */
static const useconds_t update_frequency = 100000; /* 10 Hz */

/* Main */

int main(int argc, const char * argv[])
{
    /* Create and initialize environment. */
    blinker_env_h env = blinker_env_make();
    if (!env)
    {
        return -1;
    }
    
    blinker_env_actuator_state_t actuator_state;
    actuator_state.blinker_left_on = 0;
    actuator_state.blinker_right_on = 0;
    actuator_state.warning_indicator_on = 0;
    actuator_state.blinker_lever_pos = blinker_env_lever_pos_center;
    actuator_state.wheel_pos = 0;

    /* Initialize blech. */
    blc_blech_blinker_init();
     
    /* Sense, control, act loop */
    while (1) {

        /* Get and adapt sensor input from environment. */
        blinker_env_sensor_state_t sensor_state = blinker_env_sense(env);
        
        if (sensor_state == blinker_env_sensor_state_quit) {
            break;
        }
        
        blc_int32 blinker_lever_move = 0;
        if (sensor_state == blinker_env_sensor_state_blinker_lever_up) {
            blinker_lever_move = 1;
        }
        else if (sensor_state == blinker_env_sensor_state_blinker_lever_down) {
            blinker_lever_move = 2;
        }
        
        blc_bool blinker_warning_pushed = 0;
        if (sensor_state == blinker_env_sensor_state_warn_toggle) {
            blinker_warning_pushed = 1;
        }
        
        blc_int32 rotation = 0;
        if (sensor_state == blinker_env_sensor_state_rotate_counter_clock) {
            rotation = rotation_increment;
        }
        else if (sensor_state == blinker_env_sensor_state_rotate_clock) {
            rotation = -rotation_increment;
        }

        /* Run control reaction. */
        blc_int32 blinker_lever_pos = actuator_state.blinker_lever_pos;
        
        blc_blech_blinker_tick(blinker_lever_move,
                               blinker_warning_pushed,
                               rotation,
                               &actuator_state.blinker_left_on,
                               &actuator_state.blinker_right_on,
                               &actuator_state.warning_indicator_on,
                               &blinker_lever_pos);

        /* Act on environment. */
        actuator_state.blinker_lever_pos = blinker_lever_pos;
        actuator_state.wheel_pos += rotation;
        
        blinker_env_actuate(env, &actuator_state);

        /* Wait for next tick.*/
        usleep(update_frequency);
    }

    /* Destroy environment. */
    blinker_env_destroy(env);
    
    return 0;
}
