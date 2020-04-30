#pragma once
#include "Robot.h"

class RobotQrio: public Robot{
	int detonateBomb; 
public:
	RobotQrio(const int id) : Robot(id), detonateBomb(0) {};

	pair<int, int> chooseNewPosition(const Harta& h) const;
	void moveRobot(Harta&, const int, const int);
	void itemEffect(char);
	void description();
};

