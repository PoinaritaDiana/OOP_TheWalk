#pragma once
#include "Robot.h"

class RobotWalle: public Robot{
	int throwAndDestroy;
	int otherItems;

public:
	RobotWalle(const int id);

	pair<int, int> chooseNewPosition(const Harta& h) const;
	void moveRobot(Harta&, const int, const int);
	void itemEffect(char);
	void description();
	~RobotWalle() {};
};

