#include "Animal.h"


Animal::Animal()
{

}

Animal::~Animal()
{

}

void Animal::makeAnimal(int t, int i, int j) {
	type = t;
	x = j;
	y = i;
	turn = 0;
	moved = 0;
	spawned = 0;

}

char Animal::showAnimal()
{
	if (type == 0)
		return ' ';
	if (type == 1)
		return 'F';
	if (type == 2)
		return 'S';
}
