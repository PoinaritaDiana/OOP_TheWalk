#include "Robot.h"

Robot::Robot(int id): type(id), nrVieti(3), position({0,0}) {}

void Robot::setPosition(const pair<int,int> p) {
	this->position = p;
}

void Robot::setNrVieti() {
	this->nrVieti--;
}

pair<int, int> Robot::getPosition() const {
	return this->position;
}

int Robot::getNrVieti() const {
	return this->nrVieti;
}

int Robot::getType() const {
	return this->type;
}