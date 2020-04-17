#include "Harta.h"

Harta::Harta(const int rows, const int columns):nrRows(rows), nrColumns(columns){
	matrix = new char* [nrRows];
	for (int i = 0; i < nrRows; i++)
		matrix[i] = new char[nrColumns];
	for (int i = 0; i < nrRows; i++)
		for (int j = 0; j < nrColumns; j++)
			matrix[i][j] = '_';

	matrix[0][0] = 'R';      ///Robotul se afla initial in coltul din stanga sus

	srand(time(NULL));

	int ok = 0;
	//Generare pozitie FINISH (marcat cu F pe harta)
	do {
		int poz_final_x = rand() % nrRows;
		int poz_final_y = rand() % nrColumns;
		if (matrix[poz_final_x][poz_final_y] == '_') {
			matrix[poz_final_x][poz_final_y] = 'F';
			ok = 1;
		}
	} while (ok == 0);


	//Generare pozitii pentru capcane (marcate cu X pe harta)
	int nr_max_capcane = nrRows;
	while (nr_max_capcane) {
		int poz_x = rand() % (nrRows - 1) + 1;
		int poz_y = rand() % (nrColumns - 1) + 1;
		if (matrix[poz_x][poz_y] == '_') {
			nr_max_capcane--;
			matrix[poz_x][poz_y] = 'X';
		}
	}
}

Harta::~Harta() {

	for (int i = 0; i < nrRows; i++)
		delete[] matrix[i];
	delete[] matrix;
	nrRows = 0;
	nrColumns = 0;

}

pair <int, int> Harta::getLocatie() {
	pair <int, int> l;
	int ok = 1;
	int i = 0;
	while (i < nrRows && ok == 1)
	{
		int j = 0;
		while (j < nrColumns && ok == 1) {
			if (matrix[i][j] == 'F') {
				l = make_pair(i, j);
				ok = 0;
			}
			j++;
		}
		i++;
	}
	return l;
}


ostream& operator << (ostream& out, const Harta& H) {
	for (int i = 0; i < H.nrRows; i++) {
		for (int j = 0; j < H.nrColumns; j++)
			out << H.matrix[i][j]<<" ";
		out << endl;
	}
	return out;
}