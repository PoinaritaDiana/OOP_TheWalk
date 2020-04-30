#include "Robot.h"

int Robot::nrVieti = 3;

Robot::Robot(int id): type(id), position({0,0}) {}

pair<int, int> Robot::getPosition() const {
	return this->position;
}

void Robot::setPosition(const pair<int,int> p) {
	this->position = p;
}

int Robot::getNrVieti() const {
	return this->nrVieti;
}

int Robot::getType() const {
	return this->type;
}


void Robot::decreaseLife() {
	this->nrVieti--;
}

void Robot::addLife() {
	this->nrVieti++;
}

