//  main.c
//  blinker

#include "blinker_env.h"

#include "blech/blinker.c"

#include "blech.h"

#include <stdio.h>
#include <unistd.h>

int main(int argc, const char * argv[])
{
    blinker_env_h env = blinker_env_make();
    
    blinker_env_actuator_state_t actuator_state;
    actuator_state.blinker_left_on = 0;
    actuator_state.blinker_right_on = 0;
    actuator_state.blinker_lever_pos = blinker_env_lever_pos_center;
    
    blc_blech_blinker_init();
    
    while (1) {
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
            rotation = -1;
        }
        else if (sensor_state == blinker_env_sensor_state_rotate_clock) {
            rotation = 1;
        }
        
        blc_blech_blinker_tick(blinker_lever_move,
                               blinker_warning_pushed,
                               rotation,
                               &actuator_state.blinker_left_on,
                               &actuator_state.blinker_right_on,
                               (blc_int32*)(&actuator_state.blinker_lever_pos));
        
        blinker_env_actuate(env, &actuator_state);
        
        usleep(100000);
    }
    
    blinker_env_destroy(env);
    
    return 0;
}
