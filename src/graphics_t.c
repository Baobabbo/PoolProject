//--------------------------------------------------------
//  GRAPHICS_T_H - draw the movement of the balls
//--------------------------------------------------------

#include "init_t.h"
float d;                // temporary variable for intersected balls

// parameters used to compute dynamic ball collision
float norm_x;
float norm_y;
float n1;
float n2;
float m1;
float m2;

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

// compute a collision
// TODO da modificare (non sono sicuro sia cosi la collisione dinamica)
//lunghezza è la distanza tra due palle
/*void compute_collision(void) {
  norm_x = (ball[j].pos.x - ball[i].pos.x) / lunghezza;
  norm_y = (ball[j].pos.y - ball[i].pos.y) / lunghezza;
  
  n1 = ball[i].sp.vx * norm_x + ball[i].sp.vy * norm_y;
  n2 = ball[j].sp.vx * norm_x + ball[j].sp.vy * norm_y;
  
  m1 = (2.0 * n2) / 2;
  m2 = (2.0 * n1) / 2;

  ball[i].sp.vx = norm_x * m1;
  ball[i].sp.vy = norm_y * m1;
  ball[j].sp.vx = norm_x * m2;
  ball[j].sp.vy = norm_y * m2;
}*/

void handle_ball_collisions() {
  
}

// check collision whit the border of game table
void handle_table_collisions(void) {
    
}

// notify player the game is finished
void game_end(){
    rectfill(buf, 0, RESY / 2 - RESY/4, RESX, RESY/2 + RESY/4, 0);
    textout_centre_ex(buf, font, "GIOCO FINITO", RESX/2, RESY/2 - 100, 
makecol(255,255, 0), -1);
    char message[] = "per ricominciare premere R, per terminare premere ESC";
    textout_centre_ex(buf, font, message, RESX/2, RESY/2, 
makecol(255,255, 0), -1);
    if(key[KEY_R]){
        init_game();
    }
    
}

// Body of the graphics process

void graphics_task(void) {
	// Screen refresh at each execution
	
	while(1){
		handle_table_collisions();
		handle_ball_collisions();
		blit(bground, buf, 0, 0, RESX / 2 - bground->w / 2, RESY - bground->h,
			RESX, RESY);
		for (i = 0; i < NUM_BALLS; i++) {
			if (ball[i].visible) {
				draw_sprite(buf, balls[i], ball[i].pos.x - BALL_BMP_DIM / 2,
					ball[i].pos.y - BALL_BMP_DIM / 2);
			}
		}
		if(!ball[8].visible){
            // game has ended
            game_end();
        }
		else if (balls_stopped()) {
            ptask_activate(user_id);
            sem_wait(&semuser);
        }
		// Everything in the buffer is moved to the screen
		blit(buf, screen, 0, 0, RESX / 2 - bground->w / 2, RESY - bground->h, RESX,
			RESY);
        // PROBABILMENTE NON NECESSARIO E DA RIMUOVERE... Da modificare anche 
        // il task palla di conseguenza
        for (i = 0; i < NUM_BALLS; i++) {
            sem_post(&semball[i]);
        }
		check_deadline_g();
		ptask_wait_for_period();
	}
}
