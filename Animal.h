class Animal
{

public:
	int type;
	int turn;
	int moved;
	int x;
	int y;
	int spawned;
	Animal();
	~Animal();
	char showAnimal();
	void makeAnimal(int t, int i, int j);

};