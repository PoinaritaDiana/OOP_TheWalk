#include "RobotTerminator.h"
/*
pair<int, int> RobotTerminator::chooseNewPosition(const Harta& h) const {

}
*/

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
			this->setNrVieti();
			if (this->getNrVieti() == 0)
				cout << "\nTerminator si-a sacrificat ultima viata pentru a isi indeplini misiunea.";
			else {
				cout << "\nTerminator si-a sacrificat o viata pentru a isi indeplini misiunea.";
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
		cout << "\nRobotul tocmai a castigat o armura care il protejeaza de urmatoarele 3 capcane!";
		this->armor+=3;
		cout << "\nTerminator are " << this->armor << " armuri, deci este protejat de urmatoarele "<< this->armor*3 <<" capcane.";
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
		this->addViata();
		this->weapon = 0;
		cout << "\nUhuuu! Terminator a strans 3 arme si in schimbul lor a primit o viata!";
		cout << "\nRobotul are acum " << this->getNrVieti() << " vieti.";
	}
}