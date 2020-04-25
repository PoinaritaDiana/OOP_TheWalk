#pragma once
#include <iostream>
#include "Harta.h"
using namespace std;

class Harta;

class Robot
{
	int nrVieti = 2;
	int type;
	pair <int, int> position = { 0,0 };

protected:
	void setPosition(const pair<int, int>);			//Setez noua pozitie a robotului dupa fiecare runda
													//Este protected pentru a nu putea fi modificata pozitia decat prin clasa "Harta"
public:
	Robot(int);
	virtual ~Robot(){};

	pair<int,int> getPosition() const;				//Getter pentru pozitia curenta a robotului
	int getNrVieti() const;							//Getter pentru numarul de vieti ale robotului
	int getType() const;							//Getter pentru tipul robotului


	virtual pair<int, int> chooseNewPosition(const Harta& h) const = 0;			//Functie care returneaza noua pozitie de pe harta a robotului
	virtual void itemEffect(char) = 0;											//Functie care modeleaza cum se comporta robotul fata de un item

	friend Harta;
};

