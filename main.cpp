#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <stdlib.h>

extern int Solve_Sudoku(char file[]);
extern int Creat_Sudoku(int Sodoku_Num);

int read(char str[])						//��ȡ����
{
	int Num = 0,len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		if (str[i]>'9' || str[i] < '0')    //�ԷǷ����������ж�
			return 0;
		Num *= 10;
		Num += str[i] - '0';
		if (Num > 1000000)
			return 0;
	}
	return Num;								//���ز���
}

int main(int argc,char *argv[])
{
	if (strcmp(argv[1], "-c") == 0)			//�����վ�����
	{
		if (int Sudoku_Num = read(argv[2]))
			Creat_Sudoku(Sudoku_Num);		//�����վ�
		else
			printf("�������ֵķ�Χ��1-1000000\n");    //�쳣����
	}
	else if (strcmp(argv[1], "-s") == 0)
	{
		Solve_Sudoku(argv[2]);
	}

	return 0;
}
