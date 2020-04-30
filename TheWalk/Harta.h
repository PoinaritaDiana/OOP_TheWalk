#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Robot.h"
using namespace std;

class Harta
{
	int nrRows;
	int nrColumns;
	char** matrix;
	pair<int, int> locatie;		//Destinatia robotului

public:
	Harta(const int rows, const int columns);
	~Harta();

	pair<int, int> getLocatie() const;						//Returnez pozitia destinatiei
	char getMatrix(int, int) const;							//Returnez ce se afla pe harta la coordonatele date
	int getRows() const;									//Returnez numarul de randuri 
	int getColumns() const;									//Returnez numarul de coloane

	void setMatrix(const int, const int, const char);		//Modific o valoare din matrice

	friend ostream& operator << (ostream&, const Harta&);	//Afisare harta
};

