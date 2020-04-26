#include "RobotQrio.h"
#include <vector>
#include <map>
#include <cmath>

pair<int, int> RobotQrio::chooseNewPosition(const Harta& h) const {
	/*
		Robotul Qrio este foarte inteligent, dar nu poate vedea decat o pozitie in jurul sau (are vizibilitate 1).
		El se poate deplasa in orice directie (dar nu poate trece printr-un loc prin care a mai trecut)
		si incearca pe cat posibil sa evite capcanele, alegand mereu pozitia disponibila de pe harta care este cat mai aproape de destinatie.
		Daca nu are de ales si este inconjurat de capcane, ori va dezamorsa bomba (daca stie cum sa faca acest lucru),
		ori isi va sacrifica una din vieti pentru a ajunge la destinatie (alegand, desigur, pozitia care este cat mai aproape de destinatie).
	*/

	/*
		p -> retine coordonatele pozitiei pentru care distanta este minima (daca acolo nu este capcana)
		pc -> retine coordonatele pozitiei pentru care distanta este minima (daca acolo este capcana)
		loc -> coordonatele destinatiei (unde trebuie sa ajunga robotul)
		dmin -> este distanta minima pana la destinatie (pentru pozitiile pe care nu sunt capcane)
		dminc -> este distanta minima pana la destinatie (pentru pozitiile pe care sunt capcane)
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
			//Daca este pozitie valida 
			if (l >= 0 && l < h.getRows() && c >= 0 && c < h.getColumns() && (l != i || c != j)) {
				//Daca nu e nici capcana si nici nu a mai trecut pe acolo
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
					//Daca mai are vieti sau stie sa dezamorseze bombe, inseamna ca poate alege si o pozitie pe care se afla capcana
					if (this->detonateBomb != 0 || this->getNrVieti() != 0) {
						//Daca e capcana
						if (h.getMatrix(l, c) != 'X') {
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
		}
	//Daca am gasit o pozitie pe care nu se afla capcana, atunci o aleg
	//Daca nu, aleg pozitia pe care se afla capcana dar este cat mai aproape de destinatie
	//Daca ambele sunt (-1,-1) inseamna ca robotul nu mai poate avansa sub nicio forma, deci s-a blocat
	if (p != make_pair(-1, -1))
		return p;
	else
		return pc;
}



void RobotQrio::moveRobot(Harta& h, const int linie, const int coloana) {
	/*
		Daca pe noua pozitie se afla o capcana, inseamna ca trebuie sa dezamorseze bomba sau sa renunte la o viata
		Daca stie sa dezamorseze bomba, mai intai foloseste acest avantaj. Altfel, trebuie sa renunte la o viata
	*/
	if (h.matrix[linie][coloana] == 'X') {
		if (this->detonateBomb != 0) {
			cout << "\n BOOOM! Qrio tocmai a dezamorsat bomba si este cu un pas mai aproape de destinatia lui!";
			this->detonateBomb--;
			if (this->detonateBomb == 0)
				cout << "\nDin pacate, Qrio nu mai stie acum sa dezamorseze nicio bomba";
			else
				cout << "\nQrio mai stie cum sa dezamorseze " << this->detonateBomb << " bombe";
		}
		else {
			this->setNrVieti();
			if (this->getNrVieti() == 0)
				cout << "\nQrio si-a sacrificat ultima viata pentru a isi indeplini misiunea.";
			else {
				cout << "\nQrio si-a sacrificat o viata pentru a isi indeplini misiunea.";
				cout << "\nRobotul mai are " << this->getNrVieti() << " vieti ramase.";
			}
		}
	}

	//Daca pe noua pozitie se afla un item
	if (h.matrix[linie][coloana] == 'T' || h.matrix[linie][coloana] == 'W' || h.matrix[linie][coloana] == 'Q') {
		this->itemEffect(h.matrix[linie][coloana]);
	}

	//Trebuie sa marchez noua pozitie cu 'R' si sa sterg 'R'-ul vechi
	h.matrix[linie][coloana] = 'R';
	pair<int, int> p = this->getPosition();
	h.matrix[p.first][p.second] = '/';

	//Setez noua pozitie a robotului
	this->setPosition(make_pair(linie, coloana));
}



void RobotQrio::itemEffect(char i) {
	//Daca intalneste un item corespunzator tipului sau, robotul Qrio va invata cum sa dezamorseze o bomba.
	//Daca intalneste un item care nu ii corespunde, robotul Qrio nu are voie sa il ia.

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
