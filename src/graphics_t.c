//--------------------------------------------------------
//  GRAPHICS_T_H - draw the movement of the balls
//--------------------------------------------------------

#include "init_t.h"

//  Check if the deadline is missed

void check_deadline_g(void) {
  if (ptask_deadline_miss()) {
    sem_wait(&semmain);
    printf("Deadline miss of graphics task \n");
    sem_post(&semmain);
  }
}

// Body of the graphics process

void graphics_task(void) {
	// Screen refresh at each execution
	
	while(1){
		// Gestione delle collisioni TODO
		
		blit(bground, buf, 0, 0, RESX / 2 - bground->w / 2, RESY - bground->h,
			RESX, RESY);
		for (i = 0; i < NUM_BALLS; i++) {
			if (ball[i].visible) {
				draw_sprite(buf, balls[i], ball[i].pos.x - BALL_BMP_DIM / 2,
					ball[i].pos.y - BALL_BMP_DIM / 2);
			}
		}
		// Everything in the buffer is moved to the screen
		blit(buf, screen, 0, 0, RESX / 2 - bground->w / 2, RESY - bground->h, RESX,
			RESY);
		 
		check_deadline_g();
		ptask_wait_for_period();
	}
}
