#include "RobotTerminator.h"
/*
pair<int, int> RobotTerminator::chooseNewPosition(const Harta& h) const {

}
*/

void RobotTerminator::moveRobot(Harta&, const int, const int) {

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
		this->armor++;
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