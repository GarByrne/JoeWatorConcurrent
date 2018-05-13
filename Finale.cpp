#include <iostream>
#include <omp.h>
#include "Animal.h"

using namespace std;

int const rows = 25;
int const columns = 25;
char map[rows][columns];
Animal ocean[rows][columns];
int fishLife = 25;
int sharkLife = 25;
int fishAlive = 0;
int sharkAlive = 0;
int moves = 0;

void ClearScreen()
	{
	int n;
	for (n = 0; n < 10; n++)
		printf( "\n\n\n\n\n\n\n\n\n\n" );
	}

void moveShark(int i, int j) {

	//pick a random adjacent square to move into-------------------------------
	int a = i - 1;
	int b = j - 1;
	int c = i + 1;
	int d = j + 1;
	if (a < 0)
		a = rows - 1;
	if (b < 0)
		b = columns - 1;
	if (a > rows - 1)
		a = 0;
	if (b > columns - 1)
		b = 0;
	Animal temp[8] = { ocean[i][d], ocean[c][d], ocean[c][j], ocean[c][b],
		ocean[i][b], ocean[a][b], ocean[a][j], ocean[a][d] };
	srand(time(NULL));
	int y;
	int x;
	int found = 0;
	int newLoc = rand() % 8;
	int foundFish = 0;
	int noFish = 0;
	int ate = 0;
	int dead = 0;

	for (int pos = newLoc; pos < 7; pos++) {
		x = temp[pos].x;
		y = temp[pos].y;
		if (ocean[y][x].type == 1) {
			foundFish = 1;
			ocean[y][x].makeAnimal(0, y, x);
			ate = 1;
			break;
		}
	}

	if (foundFish == 0) {
		for (int pos = newLoc; pos > 0; pos--) {
			x = temp[pos].x;
			y = temp[pos].y;
			if (ocean[y][x].type == 1) {
				foundFish = 1;
				ocean[y][x].makeAnimal(0, y, x);
				ate = 1;
				break;
			}
		}
	}

	if (foundFish == 0) {
		for (int pos = newLoc; pos < 7; pos++) {
			x = temp[pos].x;
			y = temp[pos].y;
			if (ocean[y][x].type == 0) {
				break;
			}
		}

		if (found == 0) {
			for (int pos = newLoc; pos > 0; pos--) {
				x = temp[pos].x;
				y = temp[pos].y;
				if (ocean[y][x].type == 0) {
					found = 1;
					break;
				}
			}
		}
	}

	if (found == 0) {
		y = i;
		x = j;
	}

	//------------------------------------------------------------------------------------------

	if (ocean[i][j].turn > 0 && ocean[i][j].turn % 4 == 0)
	{
		if (ate == 0) {
			dead = 1;
		}
		else {
			ate = 0;
		}
	}
	if (ocean[i][j].turn < sharkLife) {
		ocean[i][j].turn++;
		ocean[i][j].moved = 1;
		ocean[y][x] = ocean[i][j];
		if (y != i || j != x)
			ocean[i][j].makeAnimal(0, i, j);
	}
	else {
		dead = 1;
	}

	if (ocean[y][x].turn > 6 && ocean[y][x].spawned == 0) {
		ocean[y][x].spawned = 1;
		ocean[i][j].makeAnimal(2, i, j);
	}
	if (dead == 1) {
		ocean[i][j].makeAnimal(0, i, j);
	}
}

void moveFish(int i, int j) {

	//pick a random adjacent square to move into-------------------------------
	int a = i - 1;
	int b = j - 1;
	int c = i + 1;
	int d = j + 1;
	if (a < 0)
		a = rows - 1;
	if (b < 0)
		b = columns - 1;
	if (a > rows - 1)
		a = 0;
	if (b > columns - 1)
		b = 0;
	Animal temp[8] = { ocean[i][d], ocean[c][d], ocean[c][j], ocean[c][b],
		ocean[i][b], ocean[a][b], ocean[a][j], ocean[a][d] };
	srand(time(NULL));
	int y;
	int x;
	int found = 0;
	int newLoc = rand() % 8;
	for (int pos = newLoc; pos < 7; pos++) {
		x = temp[pos].x;
		y = temp[pos].y;
		if (ocean[y][x].type == 0) {
			found = 1;
			break;
		}
	}

	if (found == 0) {
		for (int pos = newLoc; pos > 0; pos--) {
			x = temp[pos].x;
			y = temp[pos].y;
			if (ocean[y][x].type == 0) {
				found = 1;
				break;
			}
		}
	}

	if (found == 0) {
		y = i;
		x = j;
	}

	//------------------------------------------------------------------------------------------

	if (ocean[i][j].turn < fishLife) {
		ocean[i][j].turn++;
		ocean[i][j].moved = 1;
		ocean[y][x] = ocean[i][j];
		if (y != i || j != x)
			ocean[i][j].makeAnimal(0, i, j);
	}
	else {
		ocean[i][j].makeAnimal(0, i, j);
	}

	if (ocean[y][x].turn > 2 && ocean[y][x].spawned == 0) {
		ocean[y][x].spawned = 1;
		ocean[i][j].makeAnimal(1, i, j);
	}
}

void populateMap() {
	printf("\033[44m\033[44m\n");
	#pragma omp parallel for
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			map[i][j] = 0;
			ocean[i][j].makeAnimal(0, i, j);
		}
	}
}

void displayMap() {

	ClearScreen();
	int fishCount = 0;
	int sharkCount = 0;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			cout << ocean[i][j].showAnimal() << " ";
			if (ocean[i][j].type == 1) {
				fishCount++;
			}
			if (ocean[i][j].type == 2) {
				sharkCount++;
			}
		}
		cout << endl;
	}
	fishAlive = fishCount;
	sharkAlive = sharkCount;

	cout << "Fish(F): " << fishCount << "        Sharks(S): " << sharkCount << "      Turns: " << moves << endl;
}

void checkOcean() {
	#pragma omp parallel for
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (ocean[i][j].type == 2 && ocean[i][j].moved == 0) {
				moveShark(i, j);
			}
			if (ocean[i][j].type == 1 && ocean[i][j].moved == 0) {
				moveFish(i, j);
			}
		}
	}
	moves++;
	
	#pragma omp parallel for
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (ocean[i][j].type == 2) {
				ocean[i][j].moved = 0;
			}
			if (ocean[i][j].type == 1) {
				ocean[i][j].moved = 0;
			}
		}
	}
}

int main()
{
	populateMap();

	for (int i = 15; i < 20; i++)
		for (int j = 10; j < 15; j++) {
			ocean[i][j].makeAnimal(2, i, j);
		}
	for (int i = 20; i < 25; i++)
		for (int j = 10; j < 15; j++) {
			ocean[i][j].makeAnimal(1, i, j);
		}

	for (int i = 5; i < 10; i++)
		for (int j = 5; j < 10; j++) {
			ocean[i][j].makeAnimal(1, i, j);
		}

	for (int i = 20; i < 25; i++)
		for (int j = 20; j < 25; j++) {
			ocean[i][j].makeAnimal(1, i, j);
		}

	//---------------------------------------------------------------------------

	displayMap();
	cin.get();
	while (fishAlive > 0 && sharkAlive > 0)
	{
		checkOcean();
		displayMap();
		cin.get();
	}

	displayMap();
	cout << "Fish life(n): " << fishLife << "    Shark life(m): " << sharkLife << "    Grid size: " << rows << 'x' << columns << endl;
	return 0;
}
