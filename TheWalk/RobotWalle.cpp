#include "RobotWalle.h"
#include <vector>
#include <map>
#include <cmath>

/* 
	Are vizibilitate 2 (poate ”vedea” la maxim 4 pozitii fata de pozitia lui curenta)
	Nu poate trece printr-un loc prin care a mai trecut
	Daca vede finish-ul: se poate misca in orice directie
	si se va indrepta catre el cu orice pret
	(daca exista capcana: ori va arunca un bloc gigantic de deseuri
	pentru a distruge capcana, ori isi va sacrifica o vieta)
	Daca nu vede finish-ul:
	impart in 4 directii (sus,jos,stanga, dreapta) si el va alege directia de suma maxima,
	iar in caz de egalitate, cea mai apropiata de finish:
		item = 3, liber = 2, capcana = 1, margine / vizitat = 0
	Sume posibile:
		item item = 6, item liber = 5, 
		item capcana = 4, item margine / vizitat = 3

		liber item  = 5, liber liber = 4,
		liber capcana  = 3, liber margine / vizitat = 2

		capcana item = 4, capcana liber = 3
		capcana capcana = 2, capcana margine / vizitat = 1

			 -
			 -
		- -  R  - -
			 -
			 -
*/

pair<int, int> RobotWalle::chooseNewPosition(const Harta& h) const {
	pair <int, int> p = make_pair(-1, -1);

	//Pozitia curenta
	int i = this->getPosition().first;
	int j = this->getPosition().second;

	//Destinatia
	pair <int, int> loc = h.getLocatie();
	
	//Daca finish-ul se afla in aria de vizibilitate
	if (abs(loc.first - i) <= 2 && abs(loc.second - j) <= 2) {
		int l=i, c=j;
		if (loc.first == i) {
			if (loc.second < j) c--;
			if (loc.second > j) c++;
		}
		else {
			if (loc.second == j) {
				if (loc.first < i) l--;
				if (loc.first > i) l++;
			}
			else {
				if (loc.first < i && loc.second < j) {
					l --;
					c --;
				}
				if (loc.first < i && loc.second > j) {
					l --;
					c ++;
				}
				if (loc.first > i && loc.second > j) {
					l ++;
					c ++;
				}
				if (loc.first > i && loc.second < j) {
					l ++;
					c --;
				}
			}
		}
		p = make_pair(l, c);
	}
	else {
		int sumMax = 0;			//Suma maxima
		int sum;				//Suma curenta
		double dMin = -1;		//Distanta minima
		pair <int, int> pMax = make_pair(-1, -1);

		//Directia 1(sus)
		if (i - 1 >= 0 && h.getMatrix(i - 1, j) != '/') {
			//Prima casuta
			if (h.getMatrix(i - 1, j) == 'X') sum = 1;
			else {
				if (h.getMatrix(i - 1, j) == '_') sum = 2;
				else sum = 3;
			}
			//A doua casuta
			if (i - 2 >= 0 && h.getMatrix(i - 2, j) != '/') {
				if (h.getMatrix(i - 2, j) == 'X') sum += 1;
				else {
					if (h.getMatrix(i - 2, j) == '_') sum += 2;
					else sum += 3;
				}
			}
			//Daca suma curenta > suma maxima de pana acum
			if (sum > sumMax) {
				sumMax = sum;
				pMax = make_pair(i - 1, j);
				double d = sqrt((loc.first - (i - 1)) * (loc.first - (i - 1)) + (loc.second - j) * (loc.second - j));
				dMin = d;
			}
			else
				//Daca sunt egale, compar distanta de la prima pozitie pana la finish
				if (sum == sumMax) {
					double d = sqrt((loc.first - (i - 1)) * (loc.first - (i - 1)) + (loc.second - j) * (loc.second - j));
					if (d < dMin) {
						sumMax = sum;
						pMax = make_pair(i - 1, j);
						dMin = d;
					}
				}
		}

		//Directia 2(dreapta)
		if (j + 1 < h.getColumns() && h.getMatrix(i,j + 1) != '/') {
			if (h.getMatrix(i, j + 1) == 'X') sum = 1;
			else {
				if (h.getMatrix(i, j + 1) == '_') sum = 2;
				else sum = 3;
			}

			if (j + 2 < h.getColumns() && h.getMatrix(i, j + 2) != '/') {
				if (h.getMatrix(i, j + 2) == 'X') sum += 1;
				else {
					if (h.getMatrix(i, j + 2) == '_') sum += 2;
					else sum += 3;
				}
			}

			if (sum > sumMax) {
				sumMax = sum;
				pMax = make_pair(i, j + 1);
				double d = sqrt((loc.first - i) * (loc.first - i) + (loc.second - (j + 1)) * (loc.second - (j + 1)));
				dMin = d;
			}
			else
				if (sum == sumMax) {
					double d = sqrt((loc.first - i) * (loc.first - i) + (loc.second - (j + 1)) * (loc.second - (j + 1)));
					if (d < dMin) {
						sumMax = sum;
						pMax = make_pair(i, j + 1);
						dMin = d;
					}
				}
		}

		//Directia 3(jos)
		if (i + 1 < h.getRows() && h.getMatrix(i + 1, j) != '/') {
			if (h.getMatrix(i + 1, j) == 'X') sum = 1;
			else {
				if (h.getMatrix(i + 1, j) == '_') sum = 2;
				else sum = 3;
			}

			if (i + 2 < h.getRows() && h.getMatrix(i + 2, j) != '/') {
				if (h.getMatrix(i + 2, j) == 'X') sum += 1;
				else {
					if (h.getMatrix(i + 2, j) == '_') sum += 2;
					else sum += 3;
				}
			}

			if (sum > sumMax) {
				sumMax = sum;
				pMax = make_pair(i + 1, j);
				double d = sqrt((loc.first - (i + 1)) * (loc.first - (i + 1)) + (loc.second - j) * (loc.second - j));
				dMin = d;
			}
			else
				if (sum == sumMax) {
					double d = sqrt((loc.first - (i + 1)) * (loc.first - (i + 1)) + (loc.second - j) * (loc.second - j));
					if (d < dMin) {
						sumMax = sum;
						pMax = make_pair(i + 1, j);
						dMin = d;
					}
				}
		}

		//Directia 4(stanga)
		if (j - 1 >= 0 && h.getMatrix(i,j - 1) != '/') {
			if (h.getMatrix(i, j - 1) == 'X') sum = 1;
			else {
				if (h.getMatrix(i, j - 1) == '_') sum = 2;
				else sum = 3;
			}

			if (j - 2 >= 0 && h.getMatrix(i, j - 2) != '/') {
				if (h.getMatrix(i, j - 2) == 'X') sum += 1;
				else {
					if (h.getMatrix(i, j - 2) == '_') sum += 2;
					else sum += 3;
				}
			}

			if (sum > sumMax) {
				sumMax = sum;
				pMax = make_pair(i, j - 1);
				double d = sqrt((loc.first - i) * (loc.first - i) + (loc.second - (j - 1)) * (loc.second - (j - 1)));
				dMin = d;
			}
			else
				if (sum == sumMax) {
					double d = sqrt((loc.first - i) * (loc.first - i) + (loc.second - (j - 1)) * (loc.second - (j - 1)));
					if (d < dMin) {
						sumMax = sum;
						pMax = make_pair(i, j - 1);
						dMin = d;
					}
				}
		}

		p = pMax;
	}

	return p;
}


void RobotWalle::moveRobot(Harta& h, const int linie, const int coloana) {
	/*
		Daca pe noua pozitie se afla o capcana, 
		inseamna ca trebuie sa arunce un bloc sau sa renunte la o viata
		Daca are blocuri, mai intai foloseste acest avantaj. 
		Altfel, trebuie sa renunte la o viata
	*/

	if (h.getMatrix(linie, coloana) == 'X') {
		if (this->throwAndDestroy != 0) {
			cout << "\nWOW! Wall-E tocmai a distrus o capcana si este cu un pas mai aproape de destinatia lui!";
			this->throwAndDestroy--;
			if (this->throwAndDestroy == 0)
				cout << "\nDin pacate, Wall-E nu are niciun bloc.";
			else
				cout << "\nWall-E mai are " << this->throwAndDestroy << " blocuri gigantice.";
		}
		else {
			this->setNrVieti();
			if (this->getNrVieti() == 0)
				cout << "\nWall-E si-a sacrificat ultima viata pentru a isi indeplini misiunea.";
			else {
				cout << "\nWall-E si-a sacrificat o viata pentru a isi indeplini misiunea.";
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


void RobotWalle::itemEffect(char i) {
	/*
		Robotul Wall-E aduna gunoi în cuburi mici, pe care le poate folosi
		pentru a construi blocuri gigantice cu care sa distruga capcanele
		Daca intalneste un item corespunzator tipului sau,
		primeste un bloc gigantic: throwAndDestroy++
		Daca intalneste alt item, primeste un cub mic: otherItems++
		Atunci cand are 3 cuburi (otherItems=3),
		poate construi un alt bloc gigantic: throwAndDestroy++ (si otherItems devine 0)
	*/

	if (i == 'T') {
		cout << "\nAi gasit un item pentru Terminator";
		cout << "\nWall-E a transformat acest item intr-un cub.";
		this->otherItems++;
	}
	if (i == 'Q') {
		cout << "\nAi gasit un item pentru Qrio";
		cout << "\nWall-E a transformat acest item intr-un cub.";
		this->otherItems++;
	}
	if (i == 'W') {
		cout << "\nYou're lucky! Ai gasit un item pentru Wall-E!";
		this->throwAndDestroy++;
		if (this->throwAndDestroy == 1)
			cout << "\nWall-E a primit primul sau bloc gigantic cu care poate distruge capcane!";
		else
			cout << "\nWall-E are acum " << this->throwAndDestroy << " blocuri gigantice.";
	}

	//Daca a adunat suficiente cuburi(adica 3), 
	//le poate transforma intr-un bloc gigantic
	if (this->otherItems == 3){
		this->throwAndDestroy++;
		this->otherItems = 0;
		cout << "\nUhuuu! Wall-E a strans 3 cuburi si a reusit sa le transforme intr-un bloc gigantic!";
		cout << "\nWall-E are acum " << this->throwAndDestroy << " blocuri gigantice.";
	}
}