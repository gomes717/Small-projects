#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include "defs.h"
#include "structs.h"

extern u_int8_t g_entropy_mat[SIZE][SIZE];
extern u_int16_t g_possible_mat[SIZE][SIZE];
extern size_t finish_count;

void printer(const u_int8_t (*sudoku)[SIZE]);
void initSudoku(const char* filepath, u_int8_t (*sudoku)[SIZE]);
void initEntropyMat(const u_int8_t (*sudoku)[SIZE]);
void updatePossibleMat(const u_int8_t val, const u_int8_t row, const u_int8_t col);
void updateEntropyMat();
u_int8_t solver(u_int8_t (*sudoku)[SIZE]);

#endif