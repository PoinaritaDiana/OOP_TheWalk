#pragma once
#include <iostream>
#include "Harta.h"
using namespace std;

class Harta;

class Robot
{
	static int nrVieti;
	int type;
	pair <int, int> position;

public:
	Robot(int);
	virtual ~Robot(){};

	pair<int,int> getPosition() const;				//Getter pentru pozitia curenta a robotului
	int getNrVieti() const;							//Getter pentru numarul de vieti ale robotului
	int getType() const;							//Getter pentru tipul robotului
	void setPosition(const pair<int, int>);			//Setez noua pozitie a robotului dupa fiecare runda
	void setNrVieti();								//Scad numarul de vieti daca este nevoie
	void addViata();

	virtual pair<int, int> chooseNewPosition(const Harta& h) const = 0;			//Noua pozitie de pe harta a robotului
	virtual void moveRobot(Harta&, const int, const int) = 0;					//Muta robotul pe noua pozitie aleasa
	virtual void itemEffect(char) = 0;											//Modeleaza cum se comporta robotul fata de un item
	virtual void description() = 0;
};

