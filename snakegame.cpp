#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;



//initialize variable
bool snakeGame;
const int width = 25;
const int height = 25;
int fposX, fposY, sposX, sposY;
int x, y, spd=1;//user variable
int tailX[100], tailY[100], tailLength;
//tail coordinates
int targetX, targetY; // target variable
int score;//game variable
enum directions { STOP = 0, UP, DOWN, LEFT, RIGHT };
directions dir;

void game_Setup()
{
	snakeGame = true;
	dir = STOP;
	x = rand() % width;
	y = rand() % height;
	targetX = rand() % width;
	targetY = rand() % height;
	//error when target and player are on top
	while (x == targetX && y == targetY)
	{
		x = rand() % width;
		y = rand() % height;
		targetX = rand() % width;
		targetY = rand() % height;
	}
	score = 0;
}

void game_Window()
{
	system("cls");
	//Top border 
	for (int i = 0; i < width; i++)
	{
		cout << "*";
	}
	cout << endl;

	//body
	for (int i=0;i < height;i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
			{
			  cout << "*";

			}
			else if (i == y && j == x)
			{
				cout << "S";
			}

			else if (i == targetY && j == targetX)
			{
				cout << "O";
			}
			else {

				bool tail = false;
				for (int k = 0; k < tailLength; k++)
				{
					if (j == tailX[k] && i == tailY[k])
					{
						cout << "s";
					    tail = true;

					}
				}
				if (!tail)
				{
					cout << " ";
				}
				
			}
			
		}
			cout << endl;
	}
	//Bottom border
	for (int i = 0; i < width; i++)
	{

		cout << "*";
	}
	cout << endl;
	cout << "score="<<score;
}

void game_Input()
{
	//same work as the below code
	if ((GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')) && dir != RIGHT)
	{
		dir = LEFT;
	}else if ((GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')) && dir != LEFT)
	{
		dir = RIGHT;
	}else if ((GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W')) && dir != DOWN)
	{
		dir = UP;
	}else if ((GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')) && dir != UP)
	{
		dir = DOWN;
	}


	
}
void game_Program()
{
	//tail
	fposX = tailX[0];
	fposY = tailY[0];
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < tailLength; i++)
	{
		sposX = tailX[i];
		sposY = tailY[i];
		tailX[i] = fposX;
		tailY[i] = fposY;
		fposX = sposX;
		fposY = sposY;
	}

	switch (dir)
	{

	//move snake 
	case UP:
		y -= spd;//according to co-ordinates 
		break;
	case DOWN:
		y += spd;
		break;
	case LEFT:
		x -= spd;
		break;
	case RIGHT:
		x += spd;
		break;
	
	}
	//snake border hit
	if (x == 0 || x == width - 1 || y == -1 || y == height )
	{
		snakeGame = false;
	}
	//snake hit tail
	for (int i = 0; i < tailLength; i++)
	{
		if (x == tailX[i] && y == tailY[i])
		{
			snakeGame = false;
		}
	}
	//snake hit target
	if (x==targetX && y==targetY)
	{
		targetX = rand() % width;
		targetY = rand() % height;
		score++;
		tailLength++;
	}
}

int main()
{
	game_Setup();
	while (snakeGame == true)
	{
	  game_Window();
	  game_Input();
	  game_Program();
	  Sleep(30);
	}
}