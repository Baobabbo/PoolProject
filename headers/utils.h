//------------------------------------------------
//  UTILS_H - header file of utils.c
//------------------------------------------------
#if !defined UTILS_H
#define UTILS_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// support functions
extern char *itoa(int num, char *str, int base);
extern void reset(char *tmp);
extern void sleeping();

#endif // UTILS_H
