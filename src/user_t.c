//--------------------------------------------------------
//  USER_T.C - billiard cue management with shooting power
//--------------------------------------------------------

#include "init_t.h"

int m_x, m_y;         // mouse position
char mode;            // function in mode
char click;           // user command
float angle;          // angle of cue
int power;            // power of cue
int color;            // line color white
fixed angle_fixed;    // allegro expression for float variable
int step;             // power step
int delta_x, delta_y; // different of position

void init_user(void) {
  m_x = 0;
  m_y = 0;
  mode = 0;
  click = 0;
  
}

void op_mode(char *mode){
	// function to change the behaviour
	// of the usertask
}

// Body of the user process
// user chooses the angle and shooting power
void user_task(void) {
	// Inizializzazione del task TODO

	ptask_set_priority(ptask_get_index(), 90);
	init_user();
	ptask_wait_for_activation();
	while (1) {
    if (click) {
		if (!(mouse_b & 1))
			click = 0;
    }
    if (mouse_b & 1) {
		if (!click)
			mode++;
		click = 1;
    }
    if (mouse_b & 2) {
		mode = 0;
      
    }
	
	// draw the line and the cue whith new position
    line(buf, ball[0].pos.x, ball[0].pos.y, m_x, m_y, color);
    pivot_scaled_sprite(buf, cue, ball[0].pos.x, ball[0].pos.y, power, 7,
                        angle_fixed, ftofix(1.5));

    // point out to the graphic task to have finished the execution
	// SEMAPHORE?
	ptask_wait_for_activation();
	}
}