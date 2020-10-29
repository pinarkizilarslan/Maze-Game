#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<ctime>
#include<fstream>
#include<Windows.h>
using namespace std;

void maze_map(int);
void letxy(int, int);
void move(int[][100], int);
int maze[100][100];
char yon;
int i, j;
ofstream dosyalama;


int main()
{
	int n;

	srand(time(NULL));
	cout << "Enter maze size: ";
	cin >> n;

	cout << endl;
	maze_map(n);

	cout << endl << char(190) << " is monster," << endl << "* is gold" << endl << endl;
	cout << "Please Play With The Arrow Keys. " << endl << endl;

	move(maze, n);

	cout << endl << endl;
	system("pause");
}


void maze_map(int n) //0=boşluk, 1=duvar
{
	int i, j;

	//çeper ve giriş-çıkış
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (i == 0 || j == 0 || i == n - 1 || j == n - 1) //çeper
			{
				if ((i == 0 && j == 1) || (i == n - 1 && j == n - 2)) //giriş çıkış için
					maze[i][j] = 0; //boşluk koy
				else
					maze[i][j] = 1; //duvar koy
			}
		}
	}


	//diagonal yol ve random duvar ve boşluk
	int temp;
	for (i = 1; i < n - 1; i++)
	{
		for (j = 1; j < n - 1; j++) //çeperin iç kısmı
		{
			if (i == j || i == j + 1) //diagonal yol
				maze[i][j] == 5;
			else
			{
				temp = rand() % 2;

				if (temp == 0)
					maze[i][j] = 1; //içte random duvar
				if (temp == 1)
					maze[i][j] = 2; //içte random boşluk
			}
		}
	}


	//random altın ve canavar
	for (i = 1; i < n - 1; i++)
	{
		for (j = 1; j < n - 1; j++)
		{
			if (maze[i][j] == 2) //labirentin içi
			{
				temp = rand() % 3; //ya boşluk ya altın ya da canavar

				if (temp == 0)
					maze[i][j] = 0; //boşluk koy
				else if (temp == 1)
					maze[i][j] = 3; //altın koy
				else if (temp == 2)
					maze[i][j] = 4; //canavar koy
			}

			if (maze[i][j] == 5) //diagonal yol
			{
				int temp = rand() % 2; //ya boşluk ya da altın

				if (temp == 0)
					maze[i][j] = 0; //boşluk koy
				else if (temp == 1)
					maze[i][j] = 3; //altın koy

				//diagonal yolda canavar olmaz
			}
		}
	}
	maze[n - 1][n - 2] = 9; //çıkış ise hiç bişey koyma	 
	for (i = 1; i < n - 1; i++) //yola altın koymadığı için ek for
	{
		temp = rand() % 2;
		for (j = 1; j < n - 1; j++)
		{
			if (i == j)
			{
				if (temp == 0)
					maze[i][j] = 3;
			}
		}
	}


	//yazdırma
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (maze[i][j] == 0) //boşluk
				cout << " ";
			else if (maze[i][j] == 1) //duvar
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //gri duvar
				cout << char(219);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //kapatmak için
			}
			else if (maze[i][j] == 2) //boşluk
				cout << " ";
			else if (maze[i][j] == 3) //altın
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); //sarı altın
				cout << "*";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //kapatmak için
			}
			else if (maze[i][j] == 4) //canavar
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 27); //mavi canavar
				cout << char(190);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //kapatmak için
			}
			else if (maze[i][j] == 5) //diagonal
				cout << " ";
			else if (maze[i][j] == 9) //çıkış
				cout << " ";
		}
		cout << endl;
	}
	temp = 0;
}


void letxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y + 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void move(int maze[][100], int n)
{
	int x = 1, y = 0;
	int xcln = 1, ycln = 0;
	int gold_counter = 0;

	dosyalama.open("hareket.txt", ios_base::app);

	while (true)
	{
		letxy(xcln, ycln);
		cout << " ";
		letxy(x, y);
		cout << char(22480);
		yon = _getch();
		xcln = x;
		ycln = y;
		
		if (yon == char(72)) //yukarı ↑
			y = y - 1;
		else if (yon == char(80)) //asağı ↓
			y = y + 1;
		else if (yon == char(77)) //sağ →
			x = x + 1;
		else if (yon == char(75)) //sol ←
			x = x - 1;

		dosyalama << x << "," << y << "\n";

		if (maze[y][x] == 3)
		{
			maze[y][x] = 0;
			gold_counter++;
		}
		if (maze[y][x] == 1)
		{
			x = xcln;
			y = ycln;
		}
		if (maze[y][x] == 4)
		{
			x = 1;
			y = 0;
			gold_counter = 0;

		}
		if (maze[y][x] == 9)
		{
			cout << endl << endl << endl << "CONGRATULATIONS, YOU WON!" << endl;
			cout << "Your Score: " << gold_counter;
			system("color E");
			break;
		}
	}
}