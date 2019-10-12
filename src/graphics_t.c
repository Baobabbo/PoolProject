//--------------------------------------------------------
//  GRAPHICS_T_H - draw the movement of the balls
//--------------------------------------------------------

#include "init_t.h"
float d;                // temporary variable for intersected balls

//  Check if the deadline is missed

void check_deadline_g(void) {
  if (ptask_deadline_miss()) {
    sem_wait(&semmain);
    printf("Deadline miss of graphics task \n");
    sem_post(&semmain);
  }
}

char is_stopped(ball_attr ball) {
  if (!(ball.sp.vx == 0.0 && ball.sp.vy == 0.0))
    return 0;
  return 1;
}
// check if the balls are still
char balls_stopped() {
  for (int i = 0; i < NUM_BALLS; i++) {
    if (!is_stopped(ball[i]))
      return 0;
  }
  return 1;
}

// check intersected ofballs
float intersected_balls(ball_attr a, ball_attr b) {
  d = sqrt((a.pos.x - b.pos.x) * (a.pos.x - b.pos.x) +
           (a.pos.y - b.pos.y) * (a.pos.y - b.pos.y));
  if (d <= 2 * BALL_RADIUS)
    return d;
  else
    return 0;
}

void handle_ball_collisions() {
  
}

// Body of the graphics process

void graphics_task(void) {
	// Screen refresh at each execution
	
	while(1){
		// Gestione delle collisioni TODO
		//handle_ball_collisions();
		blit(bground, buf, 0, 0, RESX / 2 - bground->w / 2, RESY - bground->h,
			RESX, RESY);
		for (i = 0; i < NUM_BALLS; i++) {
			if (ball[i].visible) {
				draw_sprite(buf, balls[i], ball[i].pos.x - BALL_BMP_DIM / 2,
					ball[i].pos.y - BALL_BMP_DIM / 2);
			}
		}
		
		// syncro btw user and graphics TODO
		ptask_activate(user_id);
		sem_wait(&semuser);
		
		// Everything in the buffer is moved to the screen
		blit(buf, screen, 0, 0, RESX / 2 - bground->w / 2, RESY - bground->h, RESX,
			RESY);
		 
		check_deadline_g();
		ptask_wait_for_period();
	}
}
