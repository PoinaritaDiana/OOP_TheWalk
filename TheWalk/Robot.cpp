#include "Robot.h"

Robot::Robot(int id) {
	this->type = id;
}

void Robot::setPosition(const pair<int,int> p) {
	this->position = p;
}

pair<int, int> Robot::getPosition() const {
	return this->position;
}