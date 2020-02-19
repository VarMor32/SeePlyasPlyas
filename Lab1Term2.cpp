//Вычисление даты рождения по Идентификационному коду
#include "stdafx.h"
#include <conio.h> // нужна для _getch()
#include <iostream> // поток ввод-вывода
#include <string> // для работы со строками
#include <cmath>
using namespace std;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

int flag = 0;

void GoToXY(short x, short y)
{
	SetConsoleCursorPosition(hStdOut, { x, y });
}

void ConsoleCursorVisible(bool show, short size)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show;
	structCursorInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

char Buf[256];
char *Rus(char *Text)
{
	CharToOemA(Text, Buf);
	return Buf;
}

void Warn(int flag)
{
	system("CLS");
	string StringWarn[] = { Rus("Сначала введите код."), Rus("Сначала проведите расчёты.") };
	cout << StringWarn[flag];
	_getch();
	system("CLS");
}

void OutputDate(int dateY, int dateM, int dateD)
{
		cout << Rus("\nДата рождения: ");
		if (dateD < 10)
			cout << "0" << dateD << ".";
		else
			cout << dateD << ".";
		if (dateM < 10)
			cout << "0" << dateM << ".";
		else
			cout << dateM << ".";
		cout << dateY;
		_getch();
		system("CLS");
}

int MonthCalc(int daysleft, int &dateY, int &dateM, int &dateD, bool leapyear)
{
	int i = 0;
	if (leapyear == true)
	{
		int Month[13] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		for (i = 1; daysleft>Month[i]; i++)
			daysleft -= Month[i];
	}
	else
	{
		int Month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		for (i = 1; daysleft>Month[i]; i++)
			daysleft -= Month[i];
	}
	dateM = i;
	dateD = daysleft;
	cout << Rus("Производятся расчёты") << endl;
	unsigned char symb = 219;
	Sleep(1000);
	for (int i = 0; i < 10; i++)
	{
		cout << symb << " ";
		Sleep(100);
	}
	Sleep(500);
	cout << Rus("\nРасчёты окончены.");
	OutputDate(dateY, dateM, dateD);
	return 1;

}

void YearCalc(long long int &idcode, int &dateY, int &dateM, int &dateD)
{
	int NumOfDays;
	int fullyears;
	bool leapyear = false;

		NumOfDays = idcode / pow(10, 5);
		fullyears = NumOfDays / 365;
		dateY = 1900 + fullyears;
		int daysleft = NumOfDays - (fullyears * 365) - (fullyears / 4);
		if ((dateY % 4 == 0) && (dateY % 100 != 0))
			leapyear = true;
		MonthCalc(daysleft, dateY, dateM, dateD, leapyear);
}

void InputNum(long long int &idcode, int &dateY, int &dateM, int &dateD)
{
	long long int icmin = 1000000000;
	long long int icmax = 9999999999;
	flag = 0;
	while (flag == 0)
	{
		cout << Rus("Введите идентификационный код из десяти цифр: ");
		cin >> idcode;
		if (!cin)
		{
			cout << Rus("ERROR! Введено некоректные данные!") << endl;
			_getch();
			exit(0);
		}
		if ((idcode < icmin) || (idcode > icmax))
		{
			cout << Rus("Введённое чилсо некорректно, повторите ввод.");
			_getch();
			idcode = 0;
			system("CLS");
		}
		else
		{
			system("CLS");
			flag = 1;
		}
	}
	YearCalc(idcode, dateY, dateM, dateD);

}



void MenuActive(int active_menu, string  Menu[], long long int &idcode, int &dateY, int &dateM, int &dateD)
{
	switch (active_menu)
	{
	case 0:
		system("CLS");
		InputNum(idcode, dateY, dateM, dateD);
		break;
	case 1:
		break;
	case 2:
		break;
	case 3: exit(0);
	}
}

void main()
{
	
	ConsoleCursorVisible(false, 100);
	
	string Menu[] = { Rus("Задание 1"), Rus("Задание 2"), Rus("1. Ввод фактического числа элементов массива"), Rus("2. Ручной ввод элементов массива"), 
					  Rus("3. Генерация элементов массива"), Rus("4. Обработка массива"), Rus("5. Вывод результующего массива") };
	char ch;
	const char ESCAPE = 27;
	const char ENTER = 13;
	const char UP = 72;
	const char DOWN = 80;
	int active_menu = 0;
	long long int idcode = 0;
	int dateY = 0;
	int dateM = 0;
	int dateD = 0;

	while (true)
	{
		int x = 40, y = 12;
		for (int i = 0; i < 2; i++)
		{
			if (i == active_menu)
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			
			else
				SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			GoToXY(x, y++);
			cout << Menu[i] << endl;
		}
		ch = _getch();
		switch (ch)
		{
		case ENTER:
			if(active_menu==0)
				MenuActive(active_menu, Menu, idcode, dateY, dateM, dateD);
			else
			{
				system("cls");
				active_menu = 2;
				while (true)
				{
					system("cls");
					for (int i = 2; i < 7; i++)
					{
						if (i == active_menu)

							SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

						else
							SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
						GoToXY(x, y++);
						cout << Menu[i] << endl;
					}
					ch = _getch();
					switch (ch)
					{
					case ENTER:
						MenuActive(active_menu, Menu, idcode, dateY, dateM, dateD);
						break;
					case ESCAPE:
						exit(0);
					case UP:
						active_menu--;
						if (active_menu < 2) active_menu = 6;
						break;
					case DOWN:
						active_menu++;
						if (active_menu > 6) active_menu = 2;
						break;
					}
				}
			}
		
			
			break;
		case ESCAPE:
			exit(0);
		case UP:
			active_menu--;
			if (active_menu < 0) active_menu = 1;
			break;
		case DOWN:
			active_menu++;
			if (active_menu > 1) active_menu = 0;
			break;
		}
	}
	_getch();
}
