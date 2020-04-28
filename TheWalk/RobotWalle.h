#pragma once
#include "Robot.h"

class RobotWalle: public Robot{
	int throwAndDestroy = 0;
	int otherItems = 0;

public:
	RobotWalle(const int id) : Robot(id) {};

	pair<int, int> chooseNewPosition(const Harta& h) const;
	void moveRobot(Harta&, const int, const int);
	void itemEffect(char);
};

