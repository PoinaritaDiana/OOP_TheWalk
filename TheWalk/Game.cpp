#include "Game.h"

Game::Game() {
	//Construiesc harta
	cout << "Se creaza jocul. Va rugam asteptati...\n\n";
	int x, y;
	cout << "Introduceti dimensiunile hartii:\nLatime:";
	cin >> x;
	while (x < 15) {
		cout << "Valoarea introdusa trebuie sa fie cel putin 15. Introduceti o noua dimensiune:";
		cin >> x;
	}
	cout << "Lungime:";
	cin >> y;
	while (y < 15) {
		cout << "Valoarea introdusa trebuie sa fie cel putin 15. Introduceti o noua dimensiune:";
		cin >> y;
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

	Robot* rb = this->r;
	poz = rb->getPosition();						//Pozitia pe care se afla robotul
	newPoz = rb->chooseNewPosition(*H);				//Noua pozitie pe care trebuie sa se mute robotul

	//Inseamna ca nu a gasit o alta pozitie pe care sa se duca, deci robotul s-a blocat
	if (newPoz == make_pair(-1, -1)) {
		cout << "Oh nu, Robotul s-a blocat :(" << endl;
		cout << "Game Over\nYou didn't reach your destination. Good luck next time!" << endl;
		this->finish = 1;
	}
	else {
		//Mut robotul pe noua pozitie
		cout << "\nRobotul s-a mutat de pe pozitia (" << poz.first << "," << poz.second << ") pe pozitia (" << newPoz.first << "," << newPoz.second << ")";
		rb->moveRobot(*H, newPoz.first, newPoz.second);

		//Daca robotul a ajuns la destinatie
		if (newPoz == H->getLocatie()) {
			cout << "\nWINNER!!! \nCongratulations! Ai ajuns la destinatie!" << endl;
			this->finish = 1;
		}

		//Daca robotul si-a pierdut toate vietile inainte sa ajunga la destinatie
		if (rb->getNrVieti()==0) {
			cout << "\nOh nu, Robotul nu mai poate continua jocul :(";
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

