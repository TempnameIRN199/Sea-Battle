#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <iomanip>
#include <conio.h>
#include <string>
#include <string.h>
#include <ctype.h>
using namespace std;

int vistrel1(int matrix[][9], const int& rows, const int& elements, int x, int y, int& ships)
{
	if (matrix[x][y] == 0)
	{
		matrix[x][y] = 2;
	}
	else if (matrix[x][y] == 1)
	{
		matrix[x][y] = 3;
		ships--;
	}
	return matrix[rows][elements];
}

int vistrel2(int matrix[][9], const int& rows, const int& elements, int& ships) // функция выстрела для бота с проверкой на занятость поля
{
	int x, y;
	do
	{
		x = rand() % 9;
		y = rand() % 9;
	} while (matrix[x][y] == 2 || matrix[x][y] == 3);
	if (matrix[x][y] == 0)
	{
		matrix[x][y] = 2;
	}
	else if (matrix[x][y] == 1)
	{
		matrix[x][y] = 3;
		ships--;
	}
	return matrix[rows][elements];
}

char Proverka(char Matrix[][9], int matrix[][9], const int& rows, const int& elements)//сравнивает интовый и чаровский массив 
{                                                                                      // Если в интовом массиве прошли какието изменения, в чаровском массиве будут соответсвующие
	for (int i = 0; i < rows; i++)                                                      // 0 - неизвестно; 1 - стоит корабль; 2 - не попал; 3 - попал
	{
		for (int j = 0; j < elements; j++)
		{
			if (matrix[i][j] == 0) //изменений нету
			{
				continue;
			}
			else if (matrix[i][j] == 2) //в этой клетке был совершен ход, но тут не было корабля
			{
				Matrix[i][j] = ' ';
			}
			else if (matrix[i][j] == 3) //в эту клетку был совершен ход, и тут был корабль(часть корабля)
			{
				Matrix[i][j] = 'X';
			}
		}
	}
	return Matrix[rows][elements];//возвращает новый чаровский массив(измененный)
}

int Bot_set(int matrix[][9], const int& rows, const int& elements)// заполнение игрового поля кораблями для бота
{
	int x, y, k = 0;
	do
	{
		x = rand() % 9;
		y = rand() % 9;
		if (matrix[x][y] == 0)
		{
			matrix[x][y] = 1;
			k++;
		}
	} while (k < 10);
	return matrix[rows][elements];
}

void Print(char matrix[][9], const int& rows, const int& elements)//вывод 1-го поля
{
	cout << "y|x   0   1   2   3   4   5   6   7   8" << endl;
	for (int i = 0; i < rows; i++)
	{
		cout << i << "| ";
		for (int j = 0; j < elements; j++)
		{
			cout << " | " << matrix[i][j];
		}
		cout << " | ";
		cout << endl;
	}
}

void PrintAll(char  matrix1[][9], char matrix2[][9], const int& rows, const int& elements, int ships1, int ships2)//вывод игрового поля 
{
	cout << "=========================================" << "\nPlayer 1                   (" << ships1 << " ships left)" << endl;
	Print(matrix1, rows, elements);
	cout << "-----------------------------------------" << endl << "Player 2                   (" << ships2 << " ships left)\n";
	Print(matrix2, rows, elements);
	cout << "=========================================";
}

bool win(int ships, bool& WIN)
{
	if (ships == 0)
	{
		WIN = true;
	}
	return WIN;
}

void CheckShotOutside(int matrix[][9], const int& rows, const int& elements, int ships2) // implement a check for a shot outside the playing field for user
{
	int x, y;
	do
	{
		cout << "\nEnter the coordinates of the shot: ";
		cin >> x >> y;
	} while (x < 0 || x > 8 || y < 0 || y > 8 || matrix[x][y] == 2 || matrix[x][y] == 3);
	vistrel1(matrix, rows, elements, x, y, ships2);
}

int main()
{
	int x;
	int y;
	bool win1 = false;
	bool win2 = false;
	int ships1 = 9;
	int ships2 = 9;
	const int rows = 9;
	const int elements = 9;
	char Matrix1[rows][elements];//карта для отображения(игрок)
	char Matrix2[rows][elements]; //карта для отображения(бот)
	int matrix1[rows][elements];   //карта для подсчёта(игрок)
	int matrix2[rows][elements];    //карта для подсчёта(бот)
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			matrix1[i][j] = 0;
			matrix2[i][j] = 0;
			Matrix1[i][j] = '?';
			Matrix2[i][j] = '?';
		}
	}
	Bot_set(matrix2, rows, elements);
	Bot_set(matrix1, rows, elements);
	while (win1 == false || win2 == false)
	{
		system("cls");
		PrintAll(Matrix1, Matrix2, rows, elements, ships1, ships2);
		CheckShotOutside(matrix2, rows, elements, ships2);
		Proverka(Matrix2, matrix2, rows, elements);
		vistrel2(matrix1, rows, elements, ships1);
		Proverka(Matrix1, matrix1, rows, elements);
		win(ships1, win1);
		win(ships2, win2);
	}
	if (ships1 == 0)
	{
		cout << "\nbot wins";
	}
	else if (ships2 == 0)
	{
		cout << "\nplayer wins ";
	}

}
