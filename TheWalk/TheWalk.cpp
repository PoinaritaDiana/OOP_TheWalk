#include <iostream>
#include "Game.h"
#include "Harta.h"
#include "Robot.h"
#include "RobotTerminator.h"
#include "RobotQrio.h"
#include "RobotWalle.h"
using namespace std;

int welcome_user() {
	system("MODE 100");
	cout << "\n\n\t\t\t THE WALK GAME \n\n";
	cout << "\t Welcome, user! \n";
	cout << "\t Avem o harta pe care se afla un robot, jucatorul tau, in coltul din stanga sus.\n";
	cout << "\t Pe harta exista o locatie unde robotul tau trebuie sa ajunga, marcata cu F.\n";
	cout << "\t De asemenea, pe harta sunt distribuite diferite capcane care il pot incurca pe robotul tau sau item-uri care sa il ajute in calatoria lui.\n\n";
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
	switch (op) {
		case 1: cout << "Terminator!\n\n"; break;
		case 2: cout << "Qrio!\n\n"; break;
		case 3: cout << "Wall.E!\n\n"; break;
	}
	system("pause");
	system("cls");
	return op;
}

int main() {

	int tip_robot=welcome_user();   //Se afiseaza un mesaj de inceput si optiunile dintre care utilizatorul alege robotul cu care doreste sa joace
	Game G;
	G.setRobot(tip_robot);

	cout << "The Force will be with you. Always.\n";
	G.print();
	int cont;
	int runda = 0;
	cout << endl;

	cout << "Cum doriti sa se desfasoare jocul?" << endl;
	cout << "Optiunea 1 : Oprirea simularii la stadiul curent, cu afisarea configuratiei hartii la sfarsitul unei runde simulate" << endl;
	cout << "Optiunea 2 : Simulare succesiva a rundelor " << endl;
	cout << "\n Optiunea dumneavoastra: ";
	int op;
	cin >> op;
	while (op!=1 && op!=2) {
		cout << "\n Optiunea nu este valida. Introduceti una din cele de mai sus:";
		cin >> op;
	}
	cout << endl;
	system("pause");
	cout << endl;

	
	if (op == 1) {
		bool f = 0;
		int cont = 1;
		do {
			G.runGame();
			G.print();
			f = G.getFinish();
			if (f == 0) {
				cout << "\nDoriti sa continuati jocul?\nIntroduceti 1 pentru DA sau 0 pentru NU:";
				cin >> cont;
				cout << endl;
			}
		} while (cont==1 && f==0);
		if (cont == 0)
			cout << endl << "Game Over\nYou didn't reach your destination. Good luck next time!" << endl;
	}
	/*
	else {
		while (G.finish()==1) {
			G.runGame();
		}
		G.print();
	}
	*/
	return 0;
}