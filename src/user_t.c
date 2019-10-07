//--------------------------------------------------------
//  USER_T.C - billiard cue management with shooting power
//--------------------------------------------------------

#include "init_t.h"

int m_x, m_y;         // mouse position
char mode;            // function in mode
char click;           // user command

void init_user(void) {
  m_x = 0;
  m_y = 0;
  mode = 0;
  click = 0;
  
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
	
	// Gestione Input TODO
}
