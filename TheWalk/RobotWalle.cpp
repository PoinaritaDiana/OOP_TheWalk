#include "RobotWalle.h"
#include <vector>
#include <map>
#include <cmath>

/* 
	Are vizibilitate 2
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
			if (loc.second < j) 
				c--;
			if (loc.second > j) 
				c++;
		}
		else {
			if (loc.second == j) {
				if (loc.first < i) 
					l--;
				if (loc.first > i) 
					l++;
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

		//Se deplaseaza sus, dreapta, jos, stanga
		//Coordonatele vecinilor 
		vector <pair<int, int>> prim;
		prim.push_back(make_pair(i - 1, j));
		prim.push_back(make_pair(i, j + 1));
		prim.push_back(make_pair(i + 1, j));
		prim.push_back(make_pair(i, j - 1));

		//Coordonatele pozitiilor la distanta 2
		vector <pair<int, int>> second;
		second.push_back(make_pair(i - 2, j));
		second.push_back(make_pair(i, j + 2));
		second.push_back(make_pair(i + 2, j));
		second.push_back(make_pair(i, j - 2));

		for (int d = 0; d < 4; d++) {
			int l = prim[d].first;
			int c = prim[d].second;

			if (l >= 0 && l < h.getRows() && c >= 0 && c < h.getColumns() && h.getMatrix(l, c) != '/') {
				//Prima casuta = vecin
				if (h.getMatrix(l, c) == 'X') 
					sum = 1;
				else {
					if (h.getMatrix(l,c) == '_') 
						sum = 2;
					else 
						sum = 3;
				}

				int ls = second[d].first;
				int cs = second[d].second;
				//A doua casuta (distanta 2)
				if (ls >= 0 && ls < h.getRows() && cs >= 0 && cs < h.getColumns() && h.getMatrix(ls, cs) != '/') {
					if (h.getMatrix(ls,cs) == 'X') 
						sum += 1;
					else {
						if (h.getMatrix(ls,cs) == '_') 
							sum += 2;
						else 
							sum += 3;
					}
				}

				//Daca suma curenta > suma maxima de pana acum
				if (sum > sumMax) {
					sumMax = sum;
					pMax = make_pair(l, c);
					double d = sqrt((loc.first - l) * (loc.first - l) + (loc.second - c) * (loc.second - c));
					dMin = d;
				}
				else
					//Daca sunt egale, compar distanta prima pozitie-finish
					if (sum == sumMax) {
						double d = sqrt((loc.first - l) * (loc.first - l) + (loc.second - c) * (loc.second - c));
						if (d < dMin) {
							sumMax = sum;
							pMax = make_pair(l, c);
							dMin = d;
						}
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
				cout << "\nDin pacate, Wall-E nu mai are niciun bloc.";
			else
				cout << "\nWall-E mai are " << this->throwAndDestroy << " blocuri gigantice.";
		}
		else {
			this->decreaseLife();
			if (this->getNrVieti() == 0)
				cout << "\nWall-E is dead!!\nWall-E si-a sacrificat ultima viata pentru a-si indeplini misiunea.";
			else {
				cout << "\nWall-E si-a sacrificat o viata pentru a-si indeplini misiunea.";
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
		Robotul aduna gunoi în cuburi mici, pe care le poate folosi
		pentru a construi blocuri gigantice cu care sa distruga capcanele
		Daca intalneste un item corespunzator tipului sau,
		primeste un bloc gigantic: throwAndDestroy++
		Daca intalneste alt item, primeste un cub mic: otherItems++
		Atunci cand are 3 cuburi (otherItems=3),
		poate construi un alt bloc gigantic: throwAndDestroy++ (si otherItems devine 0)
	*/

	if (i == 'T') {
		cout << "\nAi gasit un item pentru Terminator.";
		cout << "\nWall-E a transformat acest item intr-un cub.";
		this->otherItems++;
	}
	if (i == 'Q') {
		cout << "\nAi gasit un item pentru Qrio.";
		cout << "\nWall-E a transformat acest item intr-un cub.";
		this->otherItems++;
	}
	if (i == 'W') {
		cout << "\nYou're lucky! Ai gasit un item pentru Wall-E!";
		this->throwAndDestroy++;
		cout << "\nWall-E are " << this->throwAndDestroy << " blocuri gigantice cu care poate distruge capcane!";
	}

	//Daca a adunat suficiente cuburi(adica 3), 
	//le poate transforma intr-un bloc gigantic
	if (this->otherItems == 3){
		this->throwAndDestroy++;
		this->otherItems = 0;
		cout << "\nUhuuu! Wall-E a strans 3 cuburi si a reusit sa le transforme intr-un bloc gigantic!";
		cout << "\nWall-E are acum " << this->throwAndDestroy << " blocuri gigantice.";
	}
	else {
		cout << "\nWall-E are " << this->otherItems << " cuburi";
	}
}


void RobotWalle::description() {
	cout << "\nRobotul Wall.E are vizibilitate 2.";
	cout << "\nNu poate trece printr - un loc prin care a mai trecut.";
	cout << "\nStategia lui este sa stranga cat mai multe item-uri.";
	cout << "\nDaca vede finish - ul, se va indrepta catre el cu orice pret.";
	cout << "\nDaca intalneste un item corespunzator tipului sau, primeste un bloc gigantic cu care poate distruge o capcana.";
	cout << "\nDaca intalneste alt item, primeste un cub mic.";
	cout << "\nAtunci cand are 3 cuburi, poate construi din ele un bloc gigantic.";
}