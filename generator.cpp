#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <stdlib.h>

int Board[9][9];
int Try_List[9];

void swap(int &a, int &b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

int Random_Init(int Num[])				//随机生成1-9全排列
{
	for (int i = 0; i < 9; i++)			//顺序填入1~9
		Num[i] = i + 1;

	for (int i = 0; i < 20; i++)
	{
		int j = rand() % 9;				//随机生成0~8数字
		swap(Num[j], Num[8]);			//与最后一个数字交换
	}

	return 0;
}

bool Judge(int x,int y,int num)			//判断宫格是否合法
{
	for (int i = 0; i < 9; i++)
	{
		if (Board[x][i] == num)
			return 0;
		if (Board[i][y] == num)
			return 0;
	}

	int area_x = x - x % 3, area_y = y - y % 3;
	for (int i = area_x; i < area_x + 3; i++)
		for (int j = area_y; j < area_y + 3;j++)
			if (Board[i][j] == num)
				return 0;

	return 1;
}

int Fill_Sudoku(int x,int y)								//填充
{
	int ori = Board[x][y];
	int next_x = x + (y + 1) / 9;							//下一方格横坐标
	int	next_y = (y + 1) % 9;								//下一方格纵坐标

	if (x >= 9)												//若全部完成则返回
		return 1;

	if (Board[x][y])										//当前格已填充
	{
		if (Fill_Sudoku(next_x, next_y))
			return 1;
	}
	else
	{
		for (int i = 0; i < 9; i++)
		{
			int Try_Num = Try_List[i];						//当前尝试数字
			if (Judge(x, y, Try_Num))						//判断是否合法
			{
				Board[x][y] = Try_Num;
				if (Fill_Sudoku(next_x, next_y))
					return 1;
			}
		}
	}
	Board[x][y] = ori;										//回溯还原

	return 0;
}

int Creat_Sudoku(int Sodoku_Num)
{
	freopen("sudoku.txt", "w", stdout);
	srand((unsigned)time(NULL));							//时间种子
	while (Sodoku_Num--)
	{
		for (int i = 0; i < 9;i++)							//初始化所有宫格
			memset(Board[i], 0, sizeof(Board[i]));

		Random_Init(Board[0]);								//随机初始化第一行数字
		for (int i = 0; i < 9; i++)
			if (Board[0][i] == 8)
			{												//学号后两位97
				swap(Board[0][0], Board[0][i]);
				break;
			}

		Random_Init(Try_List);								//随机初始化数字尝试顺序

		Fill_Sudoku(1,0);									//求解残局
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				printf("%d%c", Board[i][j], j == 8 ? '\n' : ' ');
		putchar('\n');
	}
	fclose(stdout);

	return 0;
}

int Solve_Sudoku(char file[])
{
	freopen(file, "r", stdin);
	freopen("sudoku.txt", "w", stdout);
	int temp, i = 0, j = 0;
	srand((unsigned)time(NULL));					//时间种子
	Random_Init(Try_List);
	while (~scanf("%d", &temp))
	{
		Board[i][j] = temp;
		i += (j + 1) / 9;
		j = (j + 1) % 9;
		if (i == 9)									//求解数独
		{
			Fill_Sudoku(0, 0);
			i = j = 0;
			for (int i = 0; i < 9; i++)
				for (int j = 0; j < 9; j++)
					printf("%d%c", Board[i][j], j == 8 ? '\n' : ' ');
			putchar('\n');
		}
	}

	fclose(stdin);
	fclose(stdout);

	return 0;
}
