#include <iostream>
#include "Game.h"
#include "Harta.h"
#include "Robot.h"
#include "RobotTerminator.h"
#include "RobotQrio.h"
#include "RobotWalle.h"
using namespace std;

void welcome_user() {
	cout << "\n\n\t\t\t THE WALK GAME \n\n";
	cout << "\t Welcome, user! \n";
	cout << "\t Avem o harta pe care se afla un robot, jucatorul tau, in coltul din stanga sus.\n";
	cout << "\t Pe harta exista o locatie unde robotul tau trebuie sa ajunga.\n";
	cout << "\t De asemenea, pe harta sunt distribuite diferite capcane care il pot incurca pe robotul sau item-uri care sa il ajute in calatoria lui.\n\n";
}

int main() {
	welcome_user();   
	Game G;
	cout << "\n\nThe Force will be with you. Always.\n\n";
	G.print();
	cout << endl;

	cout << "Cum doriti sa se desfasoare jocul?" << endl;
	cout << "\nOptiunea 1 : Oprirea simularii la stadiul curent,\ncu afisarea configuratiei hartii la sfarsitul unei runde simulate" << endl;
	cout << "\nOptiunea 2 : Simulare succesiva a rundelor " << endl;
	cout << "\n  Optiunea dumneavoastra: ";
	int op;
	cin >> op;
	while (op!=1 && op!=2) {
		cout << "\n Optiunea nu este valida. Introduceti una din cele de mai sus:";
		cin >> op;
	}
	cout << endl;
	cout << endl;

	if (op == 1) {
		int f = 0;
		int cont = 1;
		do {
			G.runGame();
			G.print();
			f = G.getFinish();
			if (f == 0) {
				cout << "\nDoriti sa continuati jocul?\nIntroduceti 1 pentru DA sau 0 pentru NU:";
				cin >> cont;
				while (cont != 1 && cont != 0) {
					cout << "\n Optiunea nu este valida. Introduceti una din cele de mai sus:";
					cin >> cont;
				}
				cout << endl;
			}
		} while (cont==1 && f==0);
		if (cont == 0)
			cout << endl << "Game Over\nYou didn't reach your destination. Good luck next time!" << endl;
	}
	else {
		while (G.getFinish()==0) {
			G.runGame();
		}
		G.print();
	}

	return 0;
}