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

// variabili utilizzate per il calcolo della traiettoria
position trj[3];
int found;
float m, q;
float inc_x;
int inc_y;

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

void op_mode(char *mode) {
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

float get_distance(position first, position second){
	return sqrt((first.x-second.x)*(first.x-second.x) + 
		(first.y-second.y)*(first.y-second.y));
}

void calc_factors(position first, position second){
	m = (first.y - second.y) / (first.x - second.x);
	q = first.y - m * first.x;
	return;
}

int trj_ball(position p){
	for(int i = 1; i < NUM_BALLS; i++){
		if(get_distance(p, ball[i].pos)<=BALL_RADIUS)
			return 1;
	}
	return 0;
}

void trj_table(position p){
	position aux;
	if(p.y <= TABLE_BORDER || p.y >= RESY - TABLE_BORDER){
		aux.y = trj[found].y;
		aux.x = p.x + (p.x - trj[found].x);
		calc_factors(p, aux);
		found++;
		trj[found] = p;
		return;
	}
	if(p.x <= TABLE_BORDER || p.x >= RESX - TABLE_BORDER){
		aux.x = trj[found].x;
		aux.y = p.y + (p.y - trj[found].y);
		calc_factors(p, aux);
		found++;
        inc_x = -inc_x;
		trj[found] = p;
		return;
	}
	return;
}

void find_trj(int operation){
	position cur = ball[0].pos;
    inc_x = 1; inc_y = 1;
	switch(operation){
		case 0:
			if(m_y < cur.y)
				inc_y = -1;
			for(int i = cur.y; i >= TABLE_BORDER && i <= RESY - 
                TABLE_BORDER; i += inc_y){
                cur.y = i;
				if(trj_ball(cur))
					break; 
			}
			trj[1] = cur;
			found = 1;
			break;
		case 1:
			if(m_x < cur.x)
				inc_x = -1;
			for(int i = cur.x; i >= TABLE_BORDER && i <= RESX - 
                TABLE_BORDER; i += inc_x){
                cur.x = i;
				if(trj_ball(cur))
					break;
			}
			trj[1] = cur;
			found = 1;
			break;
		case 2:
			if(m_x < cur.x)
				inc_x = -0.1;
            else
                inc_x = 0.1;
			while(1){
				if(found == 2) break;
				cur.x += inc_x;
				cur.y = m * cur.x + q;
				trj_table(cur);
				if(trj_ball(cur)){
					found++;
					trj[found] = cur;
				}
			}
			break;
            
	}
}

void compute_trajecotry(){
    position m_p;
    int op;
	trj[0] = ball[0].pos;
	found = 0;
    m_p.x = m_x;
    m_p.y = m_y;
    // y = mx + q
	if(trj[0].x == m_p.x){
		// caso trj verticale
		op = 0;
	}
	if(trj[0].y == m_p.y){
		// caso trj orizzontale
		op = 1;
	}
	else{
		// caso "obliquo"
		op = 2;
		calc_factors(trj[0], m_p);
	}
	find_trj(op);
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
	compute_trajecotry();
	for(int i = 0; i < found; i++){
        line(buf, trj[i].x, trj[i].y, trj[i+1].x, trj[i+1].y, color);
    }
    // draw the line and the cue whith new position
    pivot_scaled_sprite(buf, cue, ball[0].pos.x, ball[0].pos.y, power, 7,
                        angle_fixed, ftofix(1.5));
    sem_post(&semuser);
    // point out to the graphic task to have finished the execution
    ptask_wait_for_activation();
  }
}
