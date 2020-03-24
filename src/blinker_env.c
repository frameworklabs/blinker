//
//  blinker_env.c
//  blinker
//
//  Created by Marc Schlichte on 21.03.20.
//  Copyright © 2020 Framework Labs. All rights reserved.
//

#include "blinker_env.h"

#include <stdlib.h>
#include <assert.h>
#include <curses.h>

struct blinker_env_s {
	WINDOW *win;
};

blinker_env_h blinker_env_make()
{
	blinker_env_h env = malloc(sizeof(struct blinker_env_s));
	
	env->win = initscr();
	
	cbreak();
	noecho();
	keypad(env->win, true);
	nodelay(env->win, true);
	
	return env;
}

void blinker_env_destroy(blinker_env_h self)
{
	assert(self);

	endwin();

	free(self);
}

/* Main API */

static void fill(int col, int row, int numCols, int numRows)
{
	for (int j = 0; j < numRows; ++j) {
		for (int i = 0; i < numCols; ++i) {
			mvaddch(row + j, col + i, 'X');
		}
	}
}

void blinker_env_actuate(blinker_env_h self, blinker_env_actuator_state_t *state)
{
	assert(self);
		
	int rows, cols;
	getmaxyx(self->win, rows, cols);
	int halveRows = rows / 2;
	int halveCols = cols / 2;
	
	clear();
	
	if (state->blinker_left_on) {
		fill(0, 0, halveCols - 1, halveRows);
	}
	if (state->blinker_right_on) {
		fill(halveCols + 1, 0, halveCols - 1, halveRows);
	}
	
	move(rows - 2, 0);
	switch (state->blinker_lever_pos) {
		case blinker_env_lever_pos_up:
			addch('^');
			break;
			
		case blinker_env_lever_pos_down:
			addch('v');
			break;
			
		case blinker_env_lever_pos_center:
			addch('o');
			break;
			
		default:
			addstr("oh no");
	}

	refresh();
}

blinker_env_sensor_state_t blinker_env_sense(blinker_env_h self)
{
	int c = getch();
	
	switch (c) {
		case 'q':
			return blinker_env_sensor_state_quit;
			
		case 'w':
			return blinker_env_sensor_state_warn_toggle;

		case KEY_UP:
			return blinker_env_sensor_state_blinker_lever_up;
			
		case KEY_DOWN:
			return blinker_env_sensor_state_blinker_lever_down;
			
		case KEY_LEFT:
			return blinker_env_sensor_state_rotate_counter_clock;
			
		case KEY_RIGHT:
			return blinker_env_sensor_state_rotate_clock;

		default:
			return blinker_env_sensor_state_nothing;
	}
}
