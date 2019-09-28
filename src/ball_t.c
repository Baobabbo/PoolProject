//--------------------------------------------------------
//  BALL_T.C - update the ball movement
//--------------------------------------------------------

#include "init_t.h"

// Ball pasition and movement update function

void update_ball(void){
	// stuff
}

// Check if the deadline is missed

void check_deadline_b(int num){
	if(ptask_deadline_miss()){
		sem_wait(&semmain);
		printf("Ball Task num. %d has missed its deadline\n", num);
		sem_post(&semmain);
	}
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
		check_deadline_b(task_index);
		ptask_wait_for_period();
	}
}
