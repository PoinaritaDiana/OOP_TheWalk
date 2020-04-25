#pragma once
#include "Robot.h"
class RobotQrio: public Robot{
	//Robotul Qrio este destept si poate afla cum sa dezamorseze o bomba
	int detonateBomb = 0; 
public:
	RobotQrio(const int id) : Robot(id) {};

	pair<int, int> chooseNewPosition(const Harta& h) const;
	void itemEffect(char);											

};

