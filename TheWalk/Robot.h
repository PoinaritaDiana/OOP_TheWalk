#pragma once
#include <iostream>
#include "Harta.h"
using namespace std;

class Harta;

class Robot
{
	int nrVieti;				//Numar vieti
	int type;						//Tipul robotului
	pair <int, int> position;		//Pozitia curenta a robotului

public:
	Robot(int);
	virtual ~Robot(){};

	pair<int,int> getPosition() const;				//Getter pentru pozitia curenta a robotului
	void setPosition(const pair<int, int>);			//Setez noua pozitie a robotului dupa fiecare runda

	int getNrVieti() const;							//Getter pentru numarul de vieti ale robotului
	int getType() const;							//Getter pentru tipul robotului

	void decreaseLife();							//Scad numarul de vieti
	void addLife();									//Adaug o viata

	virtual pair<int, int> chooseNewPosition(const Harta& h) const = 0;			//Alege noua pozitie a robotului
	virtual void moveRobot(Harta&, const int, const int) = 0;					//Muta robotul pe noua pozitie
	virtual void itemEffect(char) = 0;											//Modeleaza cum se comporta robotul fata de un item
	virtual void description() = 0;												//Scurta descriere a robotului
};

