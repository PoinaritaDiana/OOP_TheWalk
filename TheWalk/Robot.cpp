#include "Robot.h"

int Robot::nrVieti = 3;

Robot::Robot(int id): type(id), position({0,0}) {}

void Robot::setPosition(const pair<int,int> p) {
	this->position = p;
}

void Robot::setNrVieti() {
	this->nrVieti--;
}

void Robot::addViata() {
	this->nrVieti++;
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