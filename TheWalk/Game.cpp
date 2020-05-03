#include "Game.h"

Game::Game():runda(0), finish(0){
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

	//Se alege robotul
	cout << "\t You can choose your fighter:\n";
	cout << "\t Optiunea 1: TERMINATOR - strong and ambitious\n";
	cout << "\t Optiunea 2: QRIO - cute and smart\n";
	cout << "\t Optiunea 3: WALL.E - hardworking and adventurous\n\n";
	cout << "\tIntroduceti optiunea: ";
	int op;
	cin >> op;
	while (op < 1 || op>3) {
		cout << "\n Optiunea nu este valida. Introduceti una din cele de mai sus:";
		cin >> op;
	}

	cout << "\n\n\t Good luck, ";
	if (op == 1) {
		cout << "Terminator!\n\n";
		r = new RobotTerminator(1);
	}
	if (op == 2) {
		cout << "Qrio!\n\n";
		r = new RobotQrio(2);
	}
	if (op == 3) {
		cout << "Wall.E!\n\n";
		r = new RobotWalle(3);
	}
	
	r->description();
	cout << "\n\n";

}


//Destructor
Game::~Game() {
	delete H;
	delete r;
	runda = 0;	
	finish = 0;
}


//Simulare runda
void Game::runGame() {
	runda++;
	cout << "\nRunda " << runda << " :";

	pair<int, int> poz = r->getPosition();					//Pozitia pe care se afla robotul
	pair<int, int> newPoz = r->chooseNewPosition(*H);		//Noua pozitie pe care trebuie sa se mute robotul

	//Inseamna ca nu a gasit o alta pozitie, deci robotul s-a blocat
	if (newPoz == make_pair(-1, -1)) {
		cout << "\nOh nu, Robotul s-a blocat :(";
		cout << "\nGame Over\nYou didn't reach your destination. Good luck next time!" << endl;
		this->finish = 1;
	}
	else {
		//Mut robotul pe noua pozitie
		cout << "\nRobotul s-a mutat de pe pozitia (" << poz.first << "," << poz.second << ") pe pozitia (" << newPoz.first << "," << newPoz.second << ")";
		r->moveRobot(*H, newPoz.first, newPoz.second);

		//Daca robotul a ajuns la destinatie
		if (newPoz == H->getLocatie()) {
			cout << "\nWINNER!!! \nCongratulations! Ai ajuns la destinatie!" << endl;
			this->finish = 1;
		}

		//Daca robotul si-a pierdut toate vietile inainte sa ajunga la destinatie
		if (r->getNrVieti()==0) {
			cout << "\nGame Over\nYou didn't reach your destination. Good luck next time!" << endl;
			this->finish = 1;
		}
	}
	cout << endl;
}


//Returneaza pozitia de finish
int Game::getFinish () const {
	return this->finish;
}


//Afiseaza harta la stadiul curent
void Game::print() {
	cout << *H;
}

