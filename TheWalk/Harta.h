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
	pair<int, int> locatie;
public:
	Harta(const int rows, const int columns);
	~Harta();

	pair<int, int> getLocatie() const;							//Returnez pozitia locatiei unde trebuie sa ajunga robotul
	char getMatrix(int, int) const;								//Returnez ce se afla pe harta la coordonatele date
	int getRows() const;										//Returnez numarul de randuri 
	int getColumns() const;										//Returnez numarul de coloane

	friend ostream& operator << (ostream&, const Harta&);

	friend class RobotQrio;
	friend class RobotTerminator;
	friend class RobotWalle;

	//void moveRobot(Robot* const robot, const int linie, const int coloana);
};

