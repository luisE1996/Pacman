#include <fstream>
#include <Windows.h>
#include <iostream>
#include <conio.h>

using namespace std;

enum { UP = 1, RIGHT = 2, DOWN = -1, LEFT = -2 };

const int SIZE_FIELD_X = 15;
const int SIZE_FIELD_Y = 30;

ifstream input ("input.txt");

int ReadKey (int *dir)
{
	INPUT_RECORD InputRecord[MaxRecords];
	DWORD RecordsRead;
	HANDLE ConsoleHandle = GetStdHandle (STD_INPUT_HANDLE);
	PeekConsoleInput (ConsoleHandle, InputRecord, MaxRecords, &RecordsRead);

	if (RecordsRead > 0) // Если есть что проверять
	{
		ReadConsoleInput (ConsoleHandle, InputRecord, MaxRecords, &RecordsRead);
		for (int i = 0; i < RecordsRead; i++)
			if (InputRecord[i].EventType == KEY_EVENT && InputRecord[i].Event.KeyEvent.bKeyDown) // Если была нажата кнопка
				switch (InputRecord[i].Event.KeyEvent.wVirtualKeyCode) // Проверяем её виртуальный код
				{
					case 38: // Кнопка W
					case 87: // Стрелка вверх
						if (Direction != UP)
							return UP;
						break;
					case 39: // Кнопка D
					case 68: // Стрелка вправо
						if (Direction != RIGHT)
							return RIGHT;
						break;
					case 40: // Кнопка S
					case 83: // Стрелка вниз
						if (Direction != DOWN)
							return DOWN;
						break;
					case 37: // Кнопка A
					case 65: // Стрелка влево
						if (Direction != LEFT)
							return LEFT;
						break;
				}
	}
	return Direction;
}

class TGM 
{ };

struct coord
{
	int x, y;
};

void setcolor (int k)
{
	HANDLE hConsole; 
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
	SetConsoleTextAttribute(hConsole, k); 
};

void CreateField (const int x, const int y, char a[SIZE_FIELD_X][SIZE_FIELD_Y])
{
	for (int i = 0; i < x; i++)
		for (int j = 0; j < y; j++)
				input >> a[i][j];
};

void WriteField (const int x, const int y, char a[SIZE_FIELD_X][SIZE_FIELD_Y])
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
				switch (a[i][j]) 
				{
				case '#' :
						cout << char(219);
						break;
				case '0' :
						cout << ' ';
						break;
				case 'P' :
						setcolor (4);
						cout << char(219);
						setcolor (15);
						break;
				case 'E' :
						setcolor (6);
						cout << char(219);
						setcolor (15);
						break;
				}
		};				
		cout << endl;
	}
};


int main ()
{
	char a[SIZE_FIELD_X][SIZE_FIELD_Y];
	coord Enemy[3] = {(2,2), (2,3), (2,4)};
	int key;
	TGM state;

	coord Pac;
	Pac.x = 10;
	Pac.y = 15;

	setcolor (15); 
	CreateField (SIZE_FIELD_X, SIZE_FIELD_Y, a);

	int dir = LEFT;
	bool GameOver = TRUE;
	while (GameOver)
	{
		key = ReadKey (&dir);
		a[Pac.x][Pac.y] = '0';
	
		coord Cpy;
		Cpy.x = Pac.x;
		Cpy.y = Pac.y;
	
		switch (key)
		{
		case LEFT :
			Pac.y--;
			break;
		case RIGHT :
			Pac.y++;
			break;
		case UP :
			Pac.x--;
			break;
		case DOWN :
			Pac.x++;
			break;
		};
	
		if (a[Pac.x][Pac.y] == 'E')
			break;	

		if (!(a[Pac.x][Pac.y] == '#'))
			a[Pac.x][Pac.y] = 'P';
		else
		{
			Pac.x = Cpy.x;
			Pac.y = Cpy.y;
			a[Pac.x][Pac.y] = 'P';
		}

		WriteField (SIZE_FIELD_X, SIZE_FIELD_Y, a);

		Sleep (300);
		system("cls");
	}

	cout << "GAME OVER";
	getch ();

	return 0;
}
