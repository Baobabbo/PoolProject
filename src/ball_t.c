//--------------------------------------------------------
//  BALL_T.C - update the ball movement
//--------------------------------------------------------

#include "init_t.h"

// Ball pasition and movement update function

void update_ball(int num) {
  if (!ball[num].visible)
    return;
  if (abs(ball[num].sp.vx) < 0.00001)
    ball[num].sp.vx = 0.0;
  if (abs(ball[num].sp.vy) < 0.00001)
    ball[num].sp.vy = 0.0;
  if (ball[num].sp.vx == 0.0 && ball[num].sp.vy == 0.0)
    return;
  ball[num].pos.x += ball[num].sp.vx * STR_SCALER;
  ball[num].pos.y += ball[num].sp.vy * STR_SCALER;
  ball[num].sp.vx *= SP_LOSS;
  ball[num].sp.vy *= SP_LOSS;
  return;
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
		sem_wait(&semball[task_index]);
		update_ball(task_index);
		check_deadline_b(task_index);
		ptask_wait_for_period();
	}
}
