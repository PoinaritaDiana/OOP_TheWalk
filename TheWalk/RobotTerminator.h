#pragma once
#include "Robot.h"

class RobotTerminator :public Robot {
	int armor;

public:
	RobotTerminator(const int id) : Robot(id),armor(0) {};

	pair<int, int> chooseNewPosition(const Harta& h) const;
	void moveRobot(Harta&, const int, const int);
	void itemEffect(char);
};

