//------------------------------------------------
//  INIT_T.C - load images and initialization of tasks
//------------------------------------------------
#include "init_t.h"

BITMAP *bground;
BITMAP *cue;
BITMAP *balls[NUM_BALLS];
BITMAP *buf;

int graphics_id, user_id;
sem_t semball[NUM_BALLS];
sem_t semmain;
sem_t semuser;
position hole[HOLE];

// position of holes
void init_hole() {
  hole[0].x = 70.0;
  hole[0].y = 70.0;
  hole[1].x = 641.0;
  hole[1].y = 60.0;
  hole[2].x = 1210.0;
  hole[2].y = 70.0;
  hole[3].x = 1210.0;
  hole[3].y = 650.0;
  hole[4].x = 641.0;
  hole[4].y = 660.0;
  hole[5].x = 70.0;
  hole[5].y = 650.0;
}

// position of balls and biliard cue in the game table
void init_game() {
	//posizionamento delle palle sul bialiardo
}

// initialization of balls
void init_balls(void) {
  int i;
  char percorso[] = "img/balls/";
  char ext[] = ".bmp";
  char tmp[255];
  char value_as_string[3];

  // dim ball images 200X200
  for (i = 0; i < NUM_BALLS; i++) {
    reset(tmp);
    itoa(i, value_as_string, 10);
    strcat(tmp, percorso);
    strcat(tmp, value_as_string);
    strcat(tmp, ext);
    balls[i] = load_bitmap(tmp, NULL);

    if (balls[i] == NULL) {
      printf("ERROR : BALL not found\n");
      exit(1);
    }
  }
}

// initialization biliard cue
void init_cue(void) {
  cue = load_bitmap("img/stick_ok.bmp", NULL);
  if (cue == NULL) {
    printf("ERROR: CUE not found\n");
    exit(1);
  }
}

// initialization game table
void init_bground(void) {
  BITMAP *tmp;
  tmp = load_bitmap("img/pool_table.bmp", NULL);
  if (tmp == NULL) {
    printf("ERROR: BACKGROUND not found\n");
    exit(1);
  }

  bground = create_bitmap(RESX, RESY);
  buf = create_bitmap(RESX, RESY);
  stretch_sprite(bground, tmp, 0, 0, RESX, RESY);
}

// initialization of allegro parameters,semaphore and game
void init() {

  allegro_init();
  set_color_depth(desktop_color_depth());
  set_gfx_mode(GFX_AUTODETECT_WINDOWED, RESX, RESY, 0, 0);
  install_keyboard();
  install_mouse();
  show_mouse(screen);
  init_hole();
  init_balls();
  init_cue();
  init_bground();
  init_game();
  

  //  initialization of tasks with deadline
  ptask_init(SCHED_OTHER, GLOBAL, PRIO_INHERITANCE);
  
  inde = 0;

  //  semaphore initialization
  for (int i = 0; i < NUM_BALLS; ++i) {
    sem_init(&semball[i], 0, 1);
  }
  sem_init(&semmain, 0, 1);
  sem_init(&semuser, 0, 0);
}