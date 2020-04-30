#include "RobotTerminator.h"

/*
	Robotul Terminator se misca pe verticala.
	Are vizibilitate 2 (dar nu conteaza decat daca vede finish)

	Daca finish-ul se afla in aria sa de viziblitate:

	- daca finish-ul este in partea de sus, are doua variante:
	1. sus pana ajunge pe aceeasi linie si apoi dreapta pana ajunge pe aceeasi coloana
	2. dreapta pana ajunge pe aceeasi coloana si apoi sus pana ajunge pe aceeasi linie
	Pentru fiecare varianta, numara capcanele si numarul de item-uri
	Alege drumul cu cele mai putine capcane;
	in caz de egalitate, alege drumul cu cele mai multe item-uri

	Analog pentru cazul in care finish-ul este in partea de jos:
	1. jos, apoi dreapta
	2. dreapta, apoi jos

*/


pair<int, int> RobotTerminator::chooseNewPosition(const Harta& h) const {
	pair <int, int> p = make_pair(-1, -1);

	//Pozitia curenta
	int i = this->getPosition().first;
	int j = this->getPosition().second;

	//Destinatia
	pair <int, int> loc = h.getLocatie();

	//Daca finish-ul se afla in aria de vizibilitate
	if (abs(loc.first - i) <= 2 && abs(loc.second - j) <= 2) {
		int l = i, c = j;
		if (loc.first == i) {
			if (loc.second > j) {
				c++;
				p = make_pair(l, c);
			}
		}
		else {
			if (loc.second == j) {
				if (loc.first < i) l--;
				if (loc.first > i) l++;
				p = make_pair(l, c);
			}
			else {
				int c1 = 0, c2 = 0, nrItems1 = 0, nrItems2 = 0;
				int copyi1 = i, copyj1 = j;
				int copyi2 = i, copyj2 = j;
				if (loc.first < i) {
					//Sus si apoi dreapta
					while (copyi1 > loc.first) {
						copyi1--;
						if (h.getMatrix(copyi1, j) == 'X') c1++;
						if (h.getMatrix(copyi1, j) == 'T' || h.getMatrix(copyi1, j) == 'W' || h.getMatrix(copyi1, j) == 'Q') nrItems1++;
					}
					while (copyj1 < loc.second) {
						copyj1++;
						if (h.getMatrix(copyi1, copyj1) == 'X') c1++;
						if (h.getMatrix(copyi1, copyj1) == 'T' || h.getMatrix(copyi1, copyj1) == 'W' || h.getMatrix(copyi1, copyj1) == 'Q') nrItems1++;
					}

					//Dreapta si apoi sus
					while (copyj2 < loc.second) {
						copyj2++;
						if (h.getMatrix(i, copyj2) == 'X') c2++;
						if (h.getMatrix(i, copyj2) == 'T' || h.getMatrix(i, copyj2) == 'W' || h.getMatrix(i, copyj2) == 'Q') nrItems2++;
					}
					while (copyi2 > loc.first) {
						copyi2--;
						if (h.getMatrix(copyi2, copyj2) == 'X') c2++;
						if (h.getMatrix(copyi2, copyj2) == 'T' || h.getMatrix(copyi2, copyj2) == 'W' || h.getMatrix(copyi2, copyj2) == 'Q') nrItems2++;
					}

					if (c1 < c2) p = make_pair(i-1,j);
					else {
						if(c1>c2) p = make_pair(i,j+1);
						else {
							if(nrItems1>nrItems2) p = make_pair(i - 1, j);
							else p = make_pair(i , j+1);
						}
					}
				}
				if (loc.first > i) {
					//Jos si apoi dreapta
					while (copyi1 < loc.first) {
						copyi1++;
						if (h.getMatrix(copyi1, j) == 'X') c1++;
						if (h.getMatrix(copyi1, j) == 'T' || h.getMatrix(copyi1, j) == 'W' || h.getMatrix(copyi1, j) == 'Q') nrItems1++;
					}
					while (copyj1 < loc.second) {
						copyj1++;
						if (h.getMatrix(copyi1, copyj1) == 'X') c1++;
						if (h.getMatrix(copyi1, copyj1) == 'T' || h.getMatrix(copyi1, copyj1) == 'W' || h.getMatrix(copyi1, copyj1) == 'Q') nrItems1++;
					}

					//Dreapta si apoi jos
					while (copyj2 < loc.second) {
						copyj2++;
						if (h.getMatrix(i, copyj2) == 'X') c2++;
						if (h.getMatrix(i, copyj2) == 'T' || h.getMatrix(i, copyj2) == 'W' || h.getMatrix(i, copyj2) == 'Q') nrItems2++;
					}
					while (copyi2 < loc.first) {
						copyi2++;
						if (h.getMatrix(copyi2, copyj2) == 'X') c2++;
						if (h.getMatrix(copyi2, copyj2) == 'T' || h.getMatrix(copyi2, copyj2) == 'W' || h.getMatrix(copyi2, copyj2) == 'Q') nrItems2++;
					}

					if (c1 < c2) p = make_pair(i + 1, j);
					else {
						if (c1 > c2) p = make_pair(i, j + 1);
						else {
							if (nrItems1 > nrItems2) p = make_pair(i + 1, j);
							else p = make_pair(i, j + 1);
						}
					}
				}
			}
		}
	}
	else {
		if (j % 2 == 0) {
			if (i + 1 < h.getRows())
				p = make_pair(i + 1, j);
			else {
				if (i + 1 == h.getRows() && j + 1 < h.getColumns())
						p = make_pair(i, j + 1);
			}
		}
		else {
			if (i - 1 >= 0)
				p = make_pair(i - 1, j);
			else
				if (j + 1 < h.getColumns())
					p = make_pair(i, j + 1);
		}
	}
	
	return p;
}


void RobotTerminator::moveRobot(Harta& h, const int linie, const int coloana) {
	/*
		Daca pe noua pozitie se afla o capcana,
		inseamna ca isi foloseste armura (daca are) sau renunta la o viata
		Daca are armura, mai intai foloseste acest avantaj.
		Altfel, trebuie sa renunte la o viata
	*/

	if (h.getMatrix(linie, coloana) == 'X') {
		if (this->armor != 0) {
			cout << "\nWOW! Terminator tocmai a distrus o capcana!";
			this->armor--;
			if (this->armor == 0)
				cout << "\nDin pacate, Terminator nu mai are armura, deci si-a pierdut imunitatea.";
			else
				cout << "\nTerminator mai poate folosi armura pentru inca "<< this->armor<<" capcane.";
		}
		else {
			this->decreaseLife();
			if (this->getNrVieti() == 0)
				cout << "\nTerminator si-a sacrificat ultima viata pentru a-si indeplini misiunea.";
			else {
				cout << "\nTerminator si-a sacrificat o viata pentru a-si indeplini misiunea.";
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

void RobotTerminator::itemEffect(char i) {
	/*
		Daca intalneste un item corespunzator tipului sau,
		robotul castiga o armura = imunitate pentru 3 capcane.
		Daca intalneste un item care nu ii corespunde,
		robotul castiga o arma.
		3 arme = 1 viata in plus
	*/

	if (i == 'T') {
		cout << "\nAi gasit un item pentru Terminator";
		cout << "\nRobotul tocmai a castigat o armura care il protejeaza de urmatoarele 5 capcane!";
		this->armor+=5;
		cout << "\nTerminator este protejat de urmatoarele "<< this->armor <<" capcane.";
	}
	if (i == 'W') {
		cout << "\nAi gasit un item pentru Wall-E";
		cout << "\nRobotul tocmai a castigat o arma!";
		this->weapon++;
		cout << "\nTerminator are " << this->weapon << " arme.";
	}
	if (i == 'Q') {
		cout << "\nAi gasit un item pentru Qrio";
		cout << "\nRobotul tocmai a castigat o arma!";
		this->weapon++;
		cout << "\nTerminator are " << this->weapon << " arme.";
	}

	//Daca a adunat suficiente arme(adica 3), poate distruge o capcana cu ele
	//Este echivalentul unei vieti
	if (this->weapon == 3) {
		this->addLife();
		this->weapon = 0;
		cout << "\nUhuuu! Terminator a strans 3 arme si in schimbul lor a primit o viata!";
		cout << "\nRobotul are acum " << this->getNrVieti() << " vieti.";
	}
}

void RobotTerminator::description() {
	cout << "\nRobotul Terminator nu se teme de nimic si se misca vertical pe harta.";
	cout << "\Daca intalneste pe harta un item corespunzator lui, Terminator castiga o armura.";
	cout << "\nAceasta armura il protejeaza pentru urmatoarele 3 capcane.";
	cout << "\nDaca intalneste un item care nu ii corespunde, atunci Terminator transforma acest item intr-o arma";
	cout << "\nAtunci cand strange 3 arme, le poate da la schimb pentru o viata.";
}