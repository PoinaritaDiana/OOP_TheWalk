#pragma once
#include "Harta.h"
#include "Robot.h"
#include "RobotTerminator.h"
#include "RobotQrio.h"
#include "RobotWalle.h"
#include <iostream>

using namespace std;

class Game
{
	Harta* H;					//Harta pe care se joaca 
	Robot* r;					//Robotul ales de utilizator pentru acest joc
	int runda = 0;				//Numarul rundei la care s-a ajuns
	int finish = 0;				//Marchez finish cu 1 daca jocul s-a terminat
public:
	Game();
	~Game();
	void print();				//Afisez harta pentru runda curenta
	void runGame();				//Simulare runda
	void setRobot(int);			//Setez tipul de robot 
	int getFinish();			//Returnez finish

};
	