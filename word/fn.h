#ifndef __fn__H
#define __fn__H

#include <stdlib.h>
#include <string.h>
#include <curses.h>

#define MISS 0
#define OPEN 1
#define SAVE 2
#define EXIT 3

#define ROW 22
#define COL 78

int RUN = 1;
char path[256] = {};
FILE *fd;

#endif