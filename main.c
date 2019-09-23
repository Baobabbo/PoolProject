//------------------------------------------------
// POOL GAME
// Created by Stefano Rossi and Riccardo Piccolo
//------------------------------------------------

#include "init_t.h"
#include "ptask.h"
#include <allegro.h>
#include <pthread.h>

int main(void) {
  int i; // temporary variable


  // balls task creation
  for (i = 0; i < NUM_BALLS; i++) {
    ptask_create_edf(ball_task, MS, B_EX_T, B_DL, NOW);
  }
  // user task creation
  user_id = ptask_create_edf(user_task, MS, U_EX_T, U_DL, NOW);

  // graphic task creation
  graphics_id = ptask_create_edf(graphics_task, MS, G_EX_T, MS, NOW);
	
  

  while (!key[KEY_ESC]){
  }
    ;
  allegro_exit();

  return 0;
}
