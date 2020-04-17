#pragma once
#include "Robot.h"
class RobotQrio: public Robot{
public:
	RobotQrio(const int id) : Robot(id) {};
	pair<int, int> chooseNewPosition(const Harta& h) const;
};

