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
  delta_x = 0;
  delta_y = 0;
  m_x = 0;
  m_y = 0;
  mode = 0;
  click = 0;
  step = 10;
  mode = 0;
  click = 0;
  angle_fixed = itofix(0);
  angle = 0.0;
  power = STICK_MIN;
  color = makecol(255, 255, 255);
  
}

void op_mode(char *mode){
  switch (*mode) {
  case 0: // follow white ball
    m_x = mouse_x;
    m_y = mouse_y;
    delta_x = m_x - ball[0].pos.x;
    delta_y = m_y - ball[0].pos.y;
    angle = atan2(delta_y, delta_x);
    angle_fixed = fixmul(ftofix(angle), radtofix_r);
    break;
  case 1: // power choice
    power = power + step;
    if (power == STICK_MAX || power == STICK_MIN)
      step = -step;
    break;
  case 2: // shooting choice
    ball[0].sp.vx = (float)(power - STICK_MIN) / 5;
    ball[0].sp.vy = (float)(power - STICK_MIN) / 5;
	ball[0].sp.vx *= cos(angle);
    ball[0].sp.vy *= sin(angle);
    *mode = 0;
    power = STICK_MIN;
    step = abs(step);
    break;
  }

}

// Prototipo calcolo traiettoria
void trajectory(){
    double m = ((float)m_y - ball[0].pos.y) / ((float)m_x - ball[0].pos.x);
    double q = ball[0].pos.y;
    float delta_x = (float)m_x - ball[0].pos.x;
    float delta_y = m_y - ball[0].pos.y;
    float p_y= ball[0].pos.x, p_x, distance;
    for(p_x = ball[0].pos.x; ;){
        if(abs(p_x) >= 3000 || abs(p_y) >= 3000){
            printf("Uscito 1\n");
            break;
        }
        
        for(int i = 1; i < NUM_BALLS; i++){
            distance = sqrt((p_x - ball[i].pos.x)*(p_x - ball[i].pos.x) + (p_y 
- ball[i].pos.y)*(p_y - ball[i].pos.y));
            if(distance <= BALL_RADIUS){
                printf("Uscito 2\n");
                break;
            }
        }
        if(distance <= BALL_RADIUS){
            printf("Uscito 3\n");
            break;
        }
        
        if(signbit(delta_x))
            p_x--;
        else
            p_x++;
        p_y = (m*p_x) + q;
    }
    // draw the line and the cue whit new position
    line(buf, ball[0].pos.x, ball[0].pos.y, p_x, p_y, makecol(255,0,0));
    pivot_scaled_sprite(buf, cue, ball[0].pos.x, ball[0].pos.y, power, 7,
                        angle_fixed, ftofix(1.5));
}

// Body of the user process
// user chooses the angle and shooting power
void user_task(void) {
	

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
	power = STICK_MIN;
      
    }

    op_mode(&mode);	

    // draw the line and the cue whith new position
    line(buf, ball[0].pos.x, ball[0].pos.y, m_x, m_y, color);
    pivot_scaled_sprite(buf, cue, ball[0].pos.x, ball[0].pos.y, power, 7,
                        angle_fixed, ftofix(1.5));

    sem_post(&semuser);
	
    // point out to the graphic task to have finished the execution
    ptask_wait_for_activation();
  }
}
