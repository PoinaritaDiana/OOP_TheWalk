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
	static int runda;			//Numarul rundei 
	static int finish;			//Marchez finish cu 1 daca jocul s-a terminat

public:
	Game();
	~Game();

	void print();				//Afisez harta pentru runda curenta
	void runGame();				//Simulare runda
	void setRobot(int);			//Setez tipul de robot 
	int getFinish();			//Returnez finish
};

int Game::runda = 0;
int Game::finish = 0;