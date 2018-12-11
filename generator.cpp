#include "stdio.h"
#include "string.h"
#include "time.h"
#include "iostream"
#include "stdlib.h"

int Board[25][9][9];
int Try_List[9];

int Read(char str[])							//�ж϶�ȡ�Ĳ����ĺϷ���
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

void Swap(int &a, int &b)							//����������
{    
	int temp;
	temp = a;
	a = b;
	b = temp;
}

int Random_Init(int Num[])							//�������1-9ȫ����
{
	int i, j;
	for (i = 0; i < 9; i++)	
		Num[i] = i + 1;
	for (i = 0; i < 20; i++) 
	{
		j = rand() % 9;								//�������0-8����
		Swap(Num[j], Num[8]);
	}

	return 0;
}

int Judge_Sudoku(int s, int x, int y, int num)		//�ж����ĺϷ���
{
	int i;
	for (i = 0; i < 9; i++)							//��ǰ�С��кϷ��ж�
	{    
		if (Board[s][x][i] == num)
			return 0;
		if (Board[s][i][y] == num)
			return 0;
	}

	int area_x = x - x % 3;							//���幬�������
	int	area_y = y - y % 3;							//���幬��������

	for (i = area_x; i < area_x + 3; i++)			//��ǰ����Ϸ��ж�
		for (int j = area_y; j < area_y + 3; j++)
			if (Board[s][i][j] == num)
				return 0;

	return 1;
}

int Fill_Sudoku(int s, int x, int y)				//��亯��
{    
	int Trace_back = Board[s][x][y];
	int next_x = x + (y + 1) / 9;					//������һ���������
	int	next_y = (y + 1) % 9;						//������һ��������

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
		for (i = 0; i < 9; i++)						//�жϺϷ���
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

void Swap_Y(int s, int beg, int end)				//���������
{
	int i, j, k;
	for (i = 0; i < 5; i++) 
	{
		j = rand() % (end - beg + 1) + beg;
		for (k = 0; k < 9; k++)
			Swap(Board[s][k][j], Board[s][k][end]);
	}
}

void Swap_X(int s, int beg, int end)				//���������
{    
	int i, j, k;
	for (i = 0; i < 5; i++) 
	{
		j = rand() % (end - beg + 1) + beg;
		for (k = 0; k < 9; k++)
			Swap(Board[s][j][k], Board[s][end][k]);
	}

}

int Creat_Sudoku(int Sodoku_Num)					//�����վ�
{    
	int i, j, extend = 1000;
	freopen("sudoku.txt", "w", stdout);
	srand(unsigned(time(0)));						//����α�����
	while (Sodoku_Num > 0) 
	{
		memset(Board, 0, sizeof(Board));
		for (i = 0; i < 20; i++)					//ÿ������20�����Ӿ���
		{    
			Random_Init(Board[i][0]);				//�����ʼ����һ������
			for (j = 0; j < 9; j++)
				if (Board[i][0][j] == 8)			//ѧ�ź���λΪ97
				{ 
					Swap(Board[i][0][0], Board[i][0][j]);
					break;
				}
			Random_Init(Try_List);					//�����ʼ�����ֳ���˳��
			Fill_Sudoku(i, 1, 0);    
		}

		while (extend--)							//��չ1000���վ�
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

int Solve_Sudoku(char File[])						//���о�����
{    
	freopen(File, "r", stdin);
	freopen("sudoku_answer.txt", "w", stdout);
	srand(unsigned(time(0)));						//ʱ������
	Random_Init(Try_List);
	int i = 0, j = 0;
	while (~scanf_s("%d", &Board[0][i][j])) 
	{
		i += (j + 1) / 9;							//��һ��������
		j = (j + 1) % 9;
		if (i == 9) 
		{
			Fill_Sudoku(0, 0, 0);
			i = j = 0;
			for (int i = 0; i < 9; i++)				//��ӡ
				for (int j = 0; j < 9; j++)
					printf("%d%c", Board[0][i][j], j == 8 ? '\n' : ' ');
			putchar('\n');
		}
	}

	fclose(stdin);
	fclose(stdout);

	return 0;
}