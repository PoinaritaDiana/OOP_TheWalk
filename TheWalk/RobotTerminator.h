#pragma once
#include "Robot.h"
class RobotTerminator :public Robot {
public:
	RobotTerminator(const int id) : Robot(id) {};
	pair<int, int> chooseNewPosition(const Harta& h) const;
};

