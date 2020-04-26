#pragma once
#include "Robot.h"
class RobotWalle: public Robot{
	//Robotul Wall-E aduna gunoi în cuburi mici, pe care le poate folosi pentru a construi blocuri gigantice cu care sa distruga capcanele
	//Daca intalneste un item corespunzator tipului sau, primeste un bloc gigantic: throwAndDestroy++
	//Daca intalneste alt item, corespunzator altui robot, primeste un cub mic: otherItems++
	//Atunci cand are 3 cuburi (otherItems=3), poate construi un alt bloc gigantic: throwAndDestroy++ (si otherItems devine, bineinteles, 0)
	int throwAndDestroy = 0;
	int otherItems = 0;
public:
	RobotWalle(const int id) : Robot(id) {};

	pair<int, int> chooseNewPosition(const Harta& h) const;
	void moveRobot(Harta&, const int, const int);
	void itemEffect(char);
};

