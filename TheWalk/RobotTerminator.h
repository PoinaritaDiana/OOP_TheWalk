#pragma once
#include "Robot.h"
class RobotTerminator :public Robot {
	//Robotul Terminator este puternic si poate avea o arma cu care sa distruga capcana sau o armura cu care sa se protejeze de ea
	int armor = 0;
public:
	RobotTerminator(const int id) : Robot(id) {};
	pair<int, int> chooseNewPosition(const Harta& h) const;
};

