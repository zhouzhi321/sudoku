#include "stdio.h"
#include "string.h"
#include "time.h"
#include "iostream"
#include "stdlib.h"

int Board[25][9][9];
int Try_List[9];

int Read(char str[])							//判断读取的参数的合法性
{   
	int Num = 0, i;
	int len = strlen(str);

	for (i = 0; i < len; i++) 
	{
		if (str[i] > '9' || str[i] < '0')
			return 0;
		Num *= 10;
		Num += str[i] - '0';
		if (Num > 1000000 || Num == 0)
			return 0;
	}

	return Num;
}

void Swap(int &a, int &b)							//交换两个数
{    
	int temp;
	temp = a;
	a = b;
	b = temp;
}

int Random_Init(int Num[])							//随机生成1-9全排列
{
	int i, j;
	for (i = 0; i < 9; i++)	
		Num[i] = i + 1;
	for (i = 0; i < 20; i++) 
	{
		j = rand() % 9;								//随机生成0-8数字
		Swap(Num[j], Num[8]);
	}

	return 0;
}

int Judge_Sudoku(int s, int x, int y, int num)		//判断填充的合法性
{
	int i;
	for (i = 0; i < 9; i++)							//当前行、列合法判断
	{    
		if (Board[s][x][i] == num)
			return 0;
		if (Board[s][i][y] == num)
			return 0;
	}

	int area_x = x - x % 3;							//定义宫格横坐标
	int	area_y = y - y % 3;							//定义宫格纵坐标

	for (i = area_x; i < area_x + 3; i++)			//当前宫格合法判断
		for (int j = area_y; j < area_y + 3; j++)
			if (Board[s][i][j] == num)
				return 0;

	return 1;
}

int Fill_Sudoku(int s, int x, int y)				//填充函数
{    
	int Trace_back = Board[s][x][y];
	int next_x = x + (y + 1) / 9;					//定义下一方格横坐标
	int	next_y = (y + 1) % 9;						//定义下一方格坐标

	if (x > 8)
		return 1;

	if (Board[s][x][y]) 
	{
		if (Fill_Sudoku(s, next_x, next_y))
			return 1;
	}
	else 
	{	
		int i;
		for (i = 0; i < 9; i++)						//判断合法性
		{
			int Try_Num = Try_List[i];
			if (Judge_Sudoku(s, x, y, Try_Num))
			{
				Board[s][x][y] = Try_Num;
				if (Fill_Sudoku(s, next_x, next_y))
					return 1;
			}
		}
	}

	Board[s][x][y] = Trace_back;

	return 0;
}

void Swap_Y(int s, int beg, int end)				//列随机交换
{
	int i, j, k;
	for (i = 0; i < 5; i++) 
	{
		j = rand() % (end - beg + 1) + beg;
		for (k = 0; k < 9; k++)
			Swap(Board[s][k][j], Board[s][k][end]);
	}
}

void Swap_X(int s, int beg, int end)				//行随机交换
{    
	int i, j, k;
	for (i = 0; i < 5; i++) 
	{
		j = rand() % (end - beg + 1) + beg;
		for (k = 0; k < 9; k++)
			Swap(Board[s][j][k], Board[s][end][k]);
	}

}

int Creat_Sudoku(int Sodoku_Num)					//生成终局
{    
	int i, j, extend = 1000;
	freopen("sudoku.txt", "w", stdout);
	srand(unsigned(time(0)));						//生成伪随机数
	while (Sodoku_Num > 0) 
	{
		memset(Board, 0, sizeof(Board));
		for (i = 0; i < 20; i++)					//每轮生成20个种子矩阵
		{    
			Random_Init(Board[i][0]);				//随机初始化第一行数字
			for (j = 0; j < 9; j++)
				if (Board[i][0][j] == 8)			//学号后两位为97
				{ 
					Swap(Board[i][0][0], Board[i][0][j]);
					break;
				}
			Random_Init(Try_List);					//随机初始化数字尝试顺序
			Fill_Sudoku(i, 1, 0);    
		}

		while (extend--)							//扩展1000个终局
		{    
			if (Sodoku_Num-- == 0)
				break;
			int sand = rand() % 20;
			int i, j;
			Swap_Y(sand, 1, 2), Swap_X(sand, 1, 2);
			Swap_Y(sand, 3, 5), Swap_X(sand, 3, 5);
			Swap_Y(sand, 6, 8), Swap_X(sand, 6, 8);

			for (i = 0; i < 9; i++)
				for (j = 0; j < 9; j++)
					printf("%d%c", Board[sand][i][j], j == 8 ? '\n' : ' ');
			putchar('\n');
		}
	}
	fclose(stdout);

	return 0;
}

int Solve_Sudoku(char File[])						//求解残局命令
{    
	freopen(File, "r", stdin);
	freopen("sudoku_answer.txt", "w", stdout);
	srand(unsigned(time(0)));						//时间种子
	Random_Init(Try_List);
	int i = 0, j = 0;
	while (~scanf_s("%d", &Board[0][i][j])) 
	{
		i += (j + 1) / 9;							//下一数字坐标
		j = (j + 1) % 9;
		if (i == 9) 
		{
			Fill_Sudoku(0, 0, 0);
			i = j = 0;
			for (int i = 0; i < 9; i++)				//打印
				for (int j = 0; j < 9; j++)
					printf("%d%c", Board[0][i][j], j == 8 ? '\n' : ' ');
			putchar('\n');
		}
	}

	fclose(stdin);
	fclose(stdout);

	return 0;
}