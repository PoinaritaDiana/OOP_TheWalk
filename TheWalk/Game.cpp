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
	this-> locatie = H->getLocatie();
}

Game::~Game() {
	delete H;
	delete r;
	runda = 0;			
	locatie = make_pair(-1, -1);
}

void Game::setRobot(int id) {
	if (id == 1)
		r = new RobotTerminator(1);
	if(id==2)
		r = new RobotQrio(2);
	if(id==3)
		r = new RobotWalle(3);
}

void Game::runGame() {
	pair<int, int> poz, newPoz;
	runda++;
	cout << "Runda " << runda << " :" << endl;
	Robot* rb = this->r;
	newPoz = rb->chooseNewPosition(*H);
	poz = rb->getPosition();
	H->moveRobot(newPoz.first, newPoz.second);

	
}

void Game::print() {
	cout << *H;
}

/*
bool Game::finish() {
	return 0;
}
*/