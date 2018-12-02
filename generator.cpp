#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <cstdlib>
using namespace std;

int Board[9][9];
int Try_List[9];

int Random_Init(int Num[])
{    //随机生成1-9全排列
 	srand((unsigned)time(NULL));    //时间种子
	for (int i = 0; i < 10; i++)
		printf(" %d/n", rand());

 	for (int i = 0; i < 9; i++)    //顺序填入1~9
		Num[i] = i + 1;

	for (int i = 0; i < 9; i++){
		int j = rand() % 9;    //随机生成0~8数字
		swap(Num[j], Num[8]);    //与最后一个数字交换
	}
 	return 0;
}

bool Judge(int x,int y,int num)
{
 	for (int i = 0; i < 9; i++)
     {    //当前行、列合法判断
		if (Board[x][i] == num)
			return 0;
		if (Board[i][y] == num)
			return 0;
	}

	int area_x = x - x % 3, area_y = y - y % 3;    //计算所处宫格左上角坐标
	for (int i = area_x; i < 3; i++)    //当前宫格合法判断
		for (int j = area_y; j < 3;j++)
			if (Board[i][j] == num)
				return 0;
 	return 1;
}

 int Solve_Sudoku(int x,int y)
 {
	int next_x = x + (y + 1) / 9, next_y = (y + 1) % 9;    //下一方格坐标
 	if (x >= 9)    //全部完成
		return 1;
	if (Board[x][y]){    //当前格已填充
		if (Solve_Sudoku(next_x, next_y))
			return 1;
	}
	else
    {    //当前为空格
		for (int i = 0; i < 9; i++)
        {
			int Try_Num = Try_List[i];    //当前尝试数字
			if (Judge(x, y, Try_Num))
            {    //判断是否合法
				Board[x][y] = Try_Num;
				if (Solve_Sudoku(next_x, next_y))
					return 1;
			}
		}
	}
 	return 0;
}

int Creat_Sudoku(int Sodoku_Num)
 {
 	freopen("sudoku.txt", "w", stdout);
	while (Sodoku_Num--)
    {
		for (int i = 0; i < 9;i++)
			memset(Board[i], 0, sizeof(Board[i]));

		Random_Init(Board[0]);    //随机初始化第一行数字
		for (int i = 0; i < 9; i++)
			if (Board[0][i] == 8)
            {    //学号后两位97 (9+7)%9+1=8
				swap(Board[0][0], Board[0][i]);
				break;
			}
            
		Random_Init(Try_List);    //随机初始化数字尝试顺序
		Solve_Sudoku(1,0);    //求解残局
		for (int i = 0; i < 9; i++)    //打印
			for (int j = 0; j < 9; j++)
				printf("%d%c", Board[i][j], j == 8 ? '\n' : ' ');
		putchar('\n');
	}
 	return 0;
} 