#pragma once
#include "stdio.h"
#include "string.h"
#include "time.h"
#include "iostream"
#include "stdlib.h"

extern int Board[25][9][9];
extern int Try_List[9];
extern int Read(char str[]);
extern int Random_Init(int Num[]);
extern int Judge_Sudoku(int s, int x, int y, int num);
extern int Fill_Sudoku(int s, int x, int y);
extern int Creat_Sudoku(int Sodoku_Num);
extern int Solve_Sudoku(char File[]);