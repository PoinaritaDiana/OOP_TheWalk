#include "RobotQrio.h"
#include <vector>
#include <map>
#include <cmath>

pair<int, int> RobotQrio::chooseNewPosition(const Harta& h) const {
	/*
		Robotul Qrio este foarte inteligent, dar nu poate vedea decat o pozitie in jurul sau (are vizibilitate 1).
		El se poate deplasa in orice directie si incearca pe cat posibil sa evite capcanele, 
		alegand mereu pozitia disponibila de pe harta care este cat mai aproape de destinatie.
		Daca nu are de ales si este inconjurat de capcane, ori va dezamorsa bomba (daca stie cum sa faca acest lucru),
		ori isi va sacrifica una din vieti pentru a ajunge la destinatie (alegand, desigur, pozitia care este cat mai aproape de destinatie).
		Daca intalneste un item corespunzator tipului sau, robotul Qrio va invata cum sa dezamorseze o bomba.
		Daca intalneste un item care nu ii corespunde, robotul Qrio nu are voie sa il ia.
	*/

	pair <int, int> p = make_pair(-1, -1);
	pair <int, int> loc = h.getLocatie();
	double dmin, d;
	dmin = -1;									//dmin este distanta minima pana la destinatie

	int i = this->getPosition().first;
	int j = this->getPosition().second;
	for (int l = i - 1; l <= i + 1; l++)
		for (int c = j - 1; c <= j + 1; c++) {
			if (l >= 0 && l < h.getRows() && c >= 0 && c < h.getColumns()) {
				if ((l != i || c != j) && h.getMatrix(l, c) != 'X' && h.getMatrix(l, c) != '/') {
					d = sqrt((loc.first - l) * (loc.first - l) + (loc.second - c) * (loc.second - c));
					if (dmin == -1) {
						dmin = d;
						p = { l,c };
					}
					else
						if (d < dmin) {
							dmin = d;
							p = { l,c };
						}
				}
			}
		}
	return p;
}

void RobotQrio::itemEffect(char i) {
	if (i == 'T') {
		cout << "\nAi gasit un item pentru Terminator";
		cout << "\nDin pacate, Qrio nu poate lua acest item pentru ca nu ii apartine :(";
	}
	if (i == 'W') {
		cout << "\nAi gasit un item pentru Wall-E";
		cout << "\nDin pacate, Qrio nu poate lua acest item pentru ca nu ii apartine :(";
	}
	if (i == 'Q') {
		cout << "\nYou're lucky! Ai gasit un item pentru Qrio!";
		this->detonateBomb++;
		if (this->detonateBomb == 1)
			cout << "\nQrio a invatat cum sa dezamorseze o bomba!";
		else 
			cout << "\nQrio stie sa dezamorseze " << detonateBomb << "bombe.";
	}
}
