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

// constants
#define NUM_BALLS 16    // number of biliard balls
#define RESX 1280       // game resolution X
#define RESY 720        // game resolution Y

// tasks
extern void ball_task(void);
extern void graphics_task(void);
extern void user_task(void);

#endif // INIT_T_H
