#include "Harta.h"


// Constructor harta (functia primeste numarul de randuri si de coloane)
Harta::Harta(const int rows, const int columns):nrRows(rows), nrColumns(columns){
	matrix = new char* [nrRows];
	for (int i = 0; i < nrRows; i++)
		matrix[i] = new char[nrColumns];
	for (int i = 0; i < nrRows; i++)
		for (int j = 0; j < nrColumns; j++)
			matrix[i][j] = '_';

	//Robotul se afla initial in coltul din stanga sus (marcat pe harta cu R)
	matrix[0][0] = 'R';      

	srand(time(NULL));

	//Generare random pozitie destinatie (marcat cu F pe harta)
	int ok = 0;
	do {
		int poz_final_x = rand() % nrRows;
		int poz_final_y = rand() % nrColumns;
		if (matrix[poz_final_x][poz_final_y] == '_') {
			matrix[poz_final_x][poz_final_y] = 'F';
			this->locatie = make_pair(poz_final_x, poz_final_y);
			ok = 1;
		}
	} while (ok == 0);

	//Generare random pozitii pentru capcane (marcat cu X pe harta) si pentru items (marcat cu I pe harta)
	int nrCapcane, nrItems;
	if (nrRows < nrColumns) {
		nrItems = nrRows;
		nrCapcane = 2 * nrColumns;
	}
	else {
		nrItems = nrColumns;
		nrCapcane = 2 * nrRows;
	}

	while (nrCapcane) {
		int poz_x = rand() % (nrRows - 1) + 1;
		int poz_y = rand() % (nrColumns - 1) + 1;
		if (matrix[poz_x][poz_y] == '_') {
			nrCapcane--;
			matrix[poz_x][poz_y] = 'X';
		}
	}
	while (nrItems) {
		int type = rand() % 3 + 1;					//Am items de 3 tipuri (fiecare este compatibil cu un tip de robot) - marcate cu T, Q, W
		int poz_x = rand() % (nrRows - 1) + 1;
		int poz_y = rand() % (nrColumns - 1) + 1;
		if (matrix[poz_x][poz_y] == '_') {
			nrItems--;
			switch (type) {
				case 1: matrix[poz_x][poz_y] = 'T'; break;
				case 2: matrix[poz_x][poz_y] = 'Q'; break;
				case 3: matrix[poz_x][poz_y] = 'W'; break;
			}
		}
	}
}

//Destructor
Harta::~Harta() {
	for (int i = 0; i < nrRows; i++)
		delete[] matrix[i];
	delete[] matrix;
	nrRows = 0;
	nrColumns = 0;
	locatie = make_pair(-1, -1);
}

int Harta::getRows() const {
	return this->nrRows;
}

int Harta::getColumns() const {
	return this->nrColumns;
}

pair <int, int> Harta::getLocatie() const {
	return this->locatie;
}

char Harta::getMatrix(int i, int j) const{
	return this->matrix[i][j];
}

void Harta::setMatrix(const int i, const int j, const char c) {
	this->matrix[i][j] = c;
}

//Afisare harta
ostream& operator << (ostream& out, const Harta& H) {
	for (int i = 0; i < H.nrRows; i++) {
		for (int j = 0; j < H.nrColumns; j++)
			out << H.matrix[i][j]<<" ";
		out << endl;
	}
	return out;
}