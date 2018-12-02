#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <cstdlib>
using namespace std;

extern int Creat_Sudoku(int Sodoku_Num);

int Sudoku_Num;

int main(int argc,char *argv[])
{
	if (strcmp(argv[1], "-c") == 0)
    {
		Sudoku_Num = argv[2][0] - '0';
		Creat_Sudoku(Sudoku_Num);
	}
}