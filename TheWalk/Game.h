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
	int idRobot;
	int runda = 0;				//Numarul rundei la care s-a ajuns
	int finish = 0;
public:
	Game();
	~Game();
	void print();
	void runGame();
	void setRobot(int);
	int getFinish();

};
	