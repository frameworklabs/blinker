//  blinker_env.c
//  blinker

#include "blinker_env.h"

#include <stdlib.h>
#include <assert.h>
#include <curses.h>

struct blinker_env_s {
    WINDOW *win;
};

blinker_env_h blinker_env_make()
{
    WINDOW *win = initscr();

    if (!has_colors()) {
        puts("This only works on color terminals!");
        endwin();
        return NULL;
    }

    blinker_env_h env = malloc(sizeof(struct blinker_env_s));

    env->win = win;

    cbreak();
    noecho();
    curs_set(0);
    keypad(env->win, true);
    nodelay(env->win, true);

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_YELLOW);
    
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
    attron(COLOR_PAIR(1));
    for (int j = 0; j < numRows; ++j) {
        mvhline(row + j, col, ' ', numCols);
    }
    attroff(COLOR_PAIR(1));
}

void blinker_env_actuate(blinker_env_h self, blinker_env_actuator_state_t *state)
{
    assert(self);

    /* Get latest window dimensions. */
    int rows, cols;
    getmaxyx(self->win, rows, cols);
    int halveRows = rows / 2;
    int halveCols = cols / 2;

    /* Start blank. */
    clear();
    
    /* Draw blinker lights. */
    if (state->blinker_left_on) {
        fill(0, 0, halveCols - 1, halveRows);
    }
    if (state->blinker_right_on) {
        fill(halveCols + 1, 0, halveCols - 1, halveRows);
    }

    /* Draw lever. */
    switch (state->blinker_lever_pos) {
        case blinker_env_lever_pos_up:
            mvhline(halveRows + 2, 0, '^', halveCols);
            break;

        case blinker_env_lever_pos_center:
            mvhline(halveRows + 4, 0, '-', halveCols);
            break;

        case blinker_env_lever_pos_down:
            mvhline(halveRows + 6, 0, 'v', halveCols);
            break;
    }

    /* Draw wheel. */
    mvaddch(halveRows + 8, halveCols + state->wheel_pos, 'O');
    
    /* Draw help. */
    mvaddstr(rows - 4, 0, "Move blinker lever up or down by arrow keys");
    mvaddstr(rows - 3, 0, "Turn wheel left or right by arrow keys");
    mvaddstr(rows - 2, 0, "Toggle warning blinker by pressing 'w'");
    mvaddstr(rows - 1, 0, "Quit demo by pressing 'q'");

    /* Display all. */
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

