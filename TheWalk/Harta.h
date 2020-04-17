#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Robot.h"
using namespace std;

class Robot;

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
	char getMatrix(int, int) const;
	int getRows() const;
	int getColumns() const;
	friend ostream& operator << (ostream&, const Harta&);

	void moveRobot(Robot* const robot, const int linie, const int coloana);
};

