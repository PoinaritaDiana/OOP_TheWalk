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
			this->locatie = make_pair(poz_final_x, poz_final_y);
			ok = 1;
		}
	} while (ok == 0);

	//Generare pozitii pentru capcane (marcate cu X pe harta)
	int nr_max_capcane;
	if (nrRows > nrColumns)
		nr_max_capcane = 3*nrRows;
	else
		nr_max_capcane = 3*nrColumns;
	while (nr_max_capcane) {
		int poz_x = rand() % (nrRows - 1) + 1;
		int poz_y = rand() % (nrColumns - 1) + 1;
		if (matrix[poz_x][poz_y] == '_') {
			nr_max_capcane--;
			matrix[poz_x][poz_y] = 'X';
		}
	}
}
int Harta::getRows() const {
	return this->nrRows;
}
int Harta::getColumns() const {
	return this->nrColumns;
}

Harta::~Harta() {

	for (int i = 0; i < nrRows; i++)
		delete[] matrix[i];
	delete[] matrix;
	nrRows = 0;
	nrColumns = 0;

}

pair <int, int> Harta::getLocatie() const {
	return this->locatie;
}

char Harta::getMatrix(int i, int j) const{
	return this->matrix[i][j];
}

void Harta::moveRobot(Robot* const robot, const int linie, const int coloana) {
	//Trebuie sa pun pe noua pozitie R si sa sterg R ul vechi
	matrix[linie][coloana] = 'R';
	pair<int, int> p = robot->getPosition();
	matrix[p.first][p.second] = '/';
	robot->setPosition(make_pair(linie, coloana));
}


ostream& operator << (ostream& out, const Harta& H) {
	for (int i = 0; i < H.nrRows; i++) {
		for (int j = 0; j < H.nrColumns; j++)
			out << H.matrix[i][j]<<" ";
		out << endl;
	}
	return out;
}