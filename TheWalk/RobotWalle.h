#pragma once
#include "Robot.h"
class RobotWalle: public Robot{
public:
	RobotWalle(const int id) : Robot(id) {};
	pair<int, int> chooseNewPosition(const Harta& h) const;
};

