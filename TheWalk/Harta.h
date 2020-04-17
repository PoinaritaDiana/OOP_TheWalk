#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;

class Harta
{
	int nrRows;
	int nrColumns;
	char** matrix;
public:
	Harta(const int rows, const int columns);
	~Harta();
	pair<int, int> getLocatie();							//Returnez pozitia locatiei unde trebuie sa ajunga robotul
	void moveRobot(int, int);								//Functie pentru a muta robotul pe noua pozitie
	friend ostream& operator << (ostream&, const Harta&);
};

