#pragma once
#include "Robot.h"
class RobotWalle: public Robot{
	//Robotul Wall-E aduna gunoi în cuburi mici, pe care le poate folosi pentru a construi blocuri gigantice cu care sa distruga capcanele
	//Daca intalneste un item corespunzator tipului sau, primeste un bloc gigantic: throwaAndDestroy++
	//Daca intalneste alt item, corespunzator altui robot, primeste un cub mic: otheItems++
	//Atunci cand are 3 cuburi (otheItems=3), poate construi un alt bloc gigantic: throwaAndDestroy++ (si otheItems devine, bineinteles, 0)
	int throwaAndDestroy = 0;
	int otheItems = 0;
public:
	RobotWalle(const int id) : Robot(id) {};

	pair<int, int> chooseNewPosition(const Harta& h) const;
	void itemEffect(char);
};

