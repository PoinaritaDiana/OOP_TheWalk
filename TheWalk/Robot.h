#pragma once
#include <iostream>
#include "Harta.h"
using namespace std;

class Harta;

class Robot
{
public:
	struct position {
		int row;
		int column;
	};
private:
	int nr_lives = 3;
	int type;
	pair <int, int> position = { 0,0 };

protected:
	void setPosition(const pair<int, int>);			//Setez noua pozitie a robotului dupa fiecare runda
public:
	Robot(int);
	virtual ~Robot(){};

	pair<int,int> getPosition() const;				//Getter pentru pozitia curenta a robotului


	virtual pair<int, int> chooseNewPosition(const Harta& h) const = 0;			//Functie care returneaza noua pozitie pe care se va afla robotul

	friend Harta;
};

