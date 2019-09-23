//--------------------------------------------------------
//  BALL_T.C - update the ball movement
//--------------------------------------------------------

#include "init_t.h"

// Ball pasition and movement update function

void update_ball(void){
	// stuff
}

// Body of ball processes

void ball_task(void){
	// Task initialization
	int task_index;
	sem_wait(&semmain);
	task_index = inde;
	inde++;
	sem_post(&semmain);
	
	// Continuous update of task position
	
	while(1){
		// aggiornamenti sicuri!
		// ...
		ptask_wait_for_period();
	}
}
