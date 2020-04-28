#include "RobotQrio.h"
#include <vector>
#include <map>
#include <cmath>

/*
	Nu poate vedea decat o pozitie in jurul sau (are vizibilitate 1)
	Se poate deplasa in orice directie
	Nu poate trece printr-un loc prin care a mai trecut
	Incearca sa evite capcanele
	Alege pozitia libera de pe harta care este cat mai aproape de destinatie
	Daca nu are de ales si este inconjurat de capcane, ori va dezamorsa bomba
	(daca stie cum sa faca acest lucru),
	ori isi va sacrifica o viata
	(alegand pozitia care este cat mai aproape de destinatie)
*/


pair<int, int> RobotQrio::chooseNewPosition(const Harta& h) const {
	/*
		p -> pozitia pentru care distanta este minima (daca acolo nu este capcana)
		pc -> pozitia pentru care distanta este minima (daca acolo este capcana)
		loc -> coordonatele destinatiei
		dmin -> distanta minima pana la destinatie (pentru pozitiile pe care nu sunt capcane)
		dminc -> distanta minima pana la destinatie (pentru pozitiile pe care sunt capcane)
	*/
	pair <int, int> p = make_pair(-1, -1);
	pair <int, int> pc = make_pair(-1, -1);
	pair <int, int> loc = h.getLocatie();
	double d, dmin, dminc;
	dmin = -1;								
	dminc = -1;

	//Pozitia curenta
	int i = this->getPosition().first;
	int j = this->getPosition().second;

	//Verific vecinatatea
	for (int l = i - 1; l <= i + 1; l++)
		for (int c = j - 1; c <= j + 1; c++) {
			if (l >= 0 && l < h.getRows() && c >= 0 && c < h.getColumns() && (l != i || c != j)) {
				if (h.getMatrix(l, c) != 'X' && h.getMatrix(l, c) != '/') {
					d = sqrt((loc.first - l) * (loc.first - l) + (loc.second - c) * (loc.second - c));
					if (dmin == -1) {
						dmin = d;
						p = make_pair(l, c);
					}
					else
						if (d < dmin) {
							dmin = d;
							p = make_pair(l, c);
						}
				}
				else {
					if (h.getMatrix(l, c) == 'X') {
						d = sqrt((loc.first - l) * (loc.first - l) + (loc.second - c) * (loc.second - c));
						if (dminc == -1) {
							dminc = d;
							pc = make_pair(l, c);
						}
						else
							if (d < dminc) {
								dminc = d;
								pc = make_pair(l, c);
							}
					}
				}
			}
		}
	//Daca am gasit o pozitie libera, atunci o aleg
	//Daca nu, aleg pozitia-capcana cea mai apropiata de destinatie
	//Altfel, robotul s-a blocat
	if (p != make_pair(-1, -1))
		return p;
	else
		return pc;
}



void RobotQrio::moveRobot(Harta& h, const int linie, const int coloana) {
	/*
		Daca pe noua pozitie se afla o capcana, 
		inseamna ca trebuie sa dezamorseze bomba sau sa renunte la o viata
		Daca stie sa dezamorseze bomba, 
		mai intai foloseste acest avantaj. 
		Altfel, trebuie sa renunte la o viata
	*/

	if (h.getMatrix(linie, coloana) == 'X') {
		if (this->detonateBomb != 0) {
			cout << "\nBOOOM! Qrio tocmai a dezamorsat bomba si este cu un pas mai aproape de destinatia lui!";
			this->detonateBomb--;
			if (this->detonateBomb == 0)
				cout << "\nDin pacate, Qrio nu mai stie acum sa dezamorseze nicio bomba :(";
			else
				cout << "\nQrio mai stie cum sa dezamorseze " << this->detonateBomb << " bombe.";
		}
		else {
			this->setNrVieti();
			if (this->getNrVieti() == 0)
				cout << "\nQrio is dead!!\nEl si-a sacrificat ultima viata pentru a-si indeplini misiunea.";
			else {
				cout << "\nQrio si-a sacrificat o viata pentru a-si indeplini misiunea.";
				cout << "\nRobotul mai are " << this->getNrVieti() << " vieti ramase.";
			}
		}
	}

	//Daca pe noua pozitie se afla un item
	if (h.getMatrix(linie, coloana) == 'T' || h.getMatrix(linie, coloana) == 'W' || h.getMatrix(linie, coloana) == 'Q') {
		this->itemEffect(h.getMatrix(linie, coloana));
	}

	//Trebuie sa marchez noua pozitie cu 'R'
	h.setMatrix(linie, coloana, 'R');
	pair<int, int> p = this->getPosition();
	h.setMatrix(p.first, p.second, '/');

	//Setez noua pozitie a robotului
	this->setPosition(make_pair(linie, coloana));
}



void RobotQrio::itemEffect(char i) {
	/*
		Daca intalneste un item corespunzator tipului sau, 
		robotul Qrio va invata cum sa dezamorseze o bomba.
		Daca intalneste un item care nu ii corespunde, 
		robotul Qrio nu are voie sa il ia.
	*/

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
