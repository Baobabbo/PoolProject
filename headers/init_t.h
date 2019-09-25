//------------------------------------------------
//  INIT_T_H - header file of init_t.c
//------------------------------------------------

#if !defined INIT_T_H
#define INIT_T_H

// all libs that are used
#include "ptask.h"
#include "utils.h"
#include <allegro.h>
#include <pthread.h>
#include <sched.h>
#include <semaphore.h>

//--- Constants
#define NUM_BALLS 16    // number of biliard balls
#define RESX 1280       // game resolution X
#define RESY 720        // game resolution Y

#define MS 34     // time between frames
#define B_EX_T 15 // ball execution time
#define B_DL 16   // ball deadline
#define U_EX_T 4  // user execution time
#define U_DL 21   // user deadline
#define G_EX_T 18 // graphic execution

//--- Structure definitions

typedef struct{
	float x, y;
}position;

typedef struct{
	float vx, vy;
}speed;

typedef struct{
	position pos;
	speed sp;
	int visible;
}ball_attr;

//--- Goblas variables

extern sem_t semball[]; // semaphore for balls
extern sem_t semuser;   // semaphore for user
extern sem_t semmain;   // main semaphore


extern int user_id, graphics_id; // ids for user and graphic tasks
extern int inde;	// index variable for ball task initialization


//--- Bitmaps for game elements
extern BITMAP *bground;
extern BITMAP *cue;
extern BITMAP *balls[NUM_BALLS];
extern BITMAP *buf;

//--- Tasks
extern void ball_task(void);
extern void graphics_task(void);
extern void user_task(void);

extern void init();
extern void init_game();
extern position hole[];

#endif // INIT_T_H
