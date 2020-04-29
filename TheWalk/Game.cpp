#include "Game.h"

Game::Game():runda(0), finish(0), r(NULL) {
	//Construiesc harta
	cout << "Se creeaza jocul. Please wait...\n\n";
	cout << "Introduceti dimensiunile hartii:\n";
	int x, y;
	int flag = 0;
	while (flag == 0) {
		try {
			cout << "Latime:";
			cin >> x;
			if (x < 15)
				throw x;
			else
				flag = 1;
		}
		catch (int) {
			cout << "Valoarea introdusa trebuie sa fie cel putin 15. ";
		}
	}

	flag = 0;
	while (flag == 0) {
		try {
			cout << "Lungime:";
			cin >> y;
			if (y < 15)
				throw y;
			else
				flag = 1;
		}
		catch (int) {
			cout << "Valoarea introdusa trebuie sa fie cel putin 15. ";
		}
	}
	cout << endl;
	H = new Harta(x, y);
}

Game::~Game() {
	delete H;
	delete r;
	runda = 0;	
	finish = 0;
}

void Game::setRobot(int id) {
	/*
	if (id == 1)
		r = new RobotTerminator(1);
		*/
	if(id==2)
		r = new RobotQrio(2);
	if(id==3)
		r = new RobotWalle(3);
}


//Simulare runda
void Game::runGame() {
	pair<int, int> poz, newPoz;
	runda++;
	cout << "\nRunda " << runda << " :";

	poz = this->r->getPosition();						//Pozitia pe care se afla robotul
	newPoz = this->r->chooseNewPosition(*H);			//Noua pozitie pe care trebuie sa se mute robotul

	//Inseamna ca nu a gasit o alta pozitie, deci robotul s-a blocat
	if (newPoz == make_pair(-1, -1)) {
		cout << "\nOh nu, Robotul s-a blocat :(";
		cout << "\nGame Over\nYou didn't reach your destination. Good luck next time!" << endl;
		this->finish = 1;
	}
	else {
		//Mut robotul pe noua pozitie
		cout << "\nRobotul s-a mutat de pe pozitia (" << poz.first << "," << poz.second << ") pe pozitia (" << newPoz.first << "," << newPoz.second << ")";
		this->r->moveRobot(*H, newPoz.first, newPoz.second);

		//Daca robotul a ajuns la destinatie
		if (newPoz == H->getLocatie()) {
			cout << "\nWINNER!!! \nCongratulations! Ai ajuns la destinatie!" << endl;
			this->finish = 1;
		}

		//Daca robotul si-a pierdut toate vietile inainte sa ajunga la destinatie
		if (this->r->getNrVieti()==0) {
			cout << "\nRobotul nu mai poate continua jocul :(";
			cout << "\nGame Over\nYou didn't reach your destination. Good luck next time!" << endl;
			this->finish = 1;
		}
	}
	cout << endl;
}

int Game::getFinish() {
	return this->finish;
}

void Game::print() {
	cout << *H;
}

