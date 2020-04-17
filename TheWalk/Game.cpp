#include "Game.h"

Game::Game() {
	cout << "Se creaza jocul. Va rugam asteptati...\n\n";
	int x, y;
	cout << "Introduceti dimensiunile hartii:\nLatime:";
	cin >> x;
	while (x < 15) {
		cout << "Valoarea introdusa trebuie sa fie cel putin 15.\nIntroduceti o noua dimensiune:";
		cin >> x;
	}
	cout << "Lungime:";
	cin >> y;
	while (y < 15) {
		cout << "Valoarea introdusa trebuie sa fie cel putin 15.\nIntroduceti o noua dimensiune:";
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
	idRobot = id;
	/*
	if (id == 1)
		r = new RobotTerminator(1);
	if(id==2)
		r = new RobotQrio(2);
		*/
	if(id==3)
		r = new RobotWalle(3);
}


void Game::runGame() {
	pair<int, int> poz, newPoz;
	runda++;
	cout << "Runda " << runda << " :" << endl;
	Robot* rb = this->r;
	newPoz = rb->chooseNewPosition(*H);				//Pozitia pe care trebuie sa se mute robotul
	poz = rb->getPosition();						//Pozitia pe care era inainte

	
	cout << "Robotul s-a mutat de pe pozitia (" << poz.first << "," << poz.second << ") pe pozitia (" << newPoz.first << "," << newPoz.second << ")" << endl;
	H->moveRobot(rb, newPoz.first, newPoz.second);
	if (newPoz == H->getLocatie()) {
		cout << "Felicitari!Ai ajuns la destinatie" << endl;
		this->finish = 1;
		}
	
}

int Game::getFinish() {
	return this->finish;
}
void Game::print() {
	cout << *H;
}

