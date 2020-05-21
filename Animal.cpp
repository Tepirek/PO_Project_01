#include "Animal.h"
#include "World.h"
#include <typeinfo>
#include "Spectator.h"
#include <iostream>

Animal::Animal(const string fullname, const char name, const int strength, const int initiative, const int x, const int y, World* world, const int step) : Organism(fullname, name, strength, initiative, x, y, world) {
	this->step = step;
	this->copulationCooldown = 0;
}

Animal::~Animal() = default;

int Animal::getStep() const {
	return this->step;
}

void Animal::setStep(const int step) {
	this->step = step;
}

bool Animal::canCopulate() const {
	return (this->copulationCooldown == 0);
}

void Animal::updateCopulationStatus() {
	if (this->copulationCooldown > 0) {
		this->copulationCooldown += -1;
	}
}

void Animal::action() {
	this->updateCopulationStatus();
	int movement = rand() % 4;
	vector<int> lastPosition = this->getPosition();
	vector<int> newPosition;
	switch (movement) {
	case 0:
		newPosition = { lastPosition[0], lastPosition[1] - this->getStep() };
		break;
	case 1:
		newPosition = { lastPosition[0] - this->getStep(), lastPosition[1] };
		break;
	case 2:
		newPosition = { lastPosition[0], lastPosition[1] + this->getStep() };
		break;
	case 3:
		newPosition = { lastPosition[0] + this->getStep(), lastPosition[1] };
		break;
	default:
		break;
	}
	if (!(newPosition[1] >= 0 && newPosition[1] < this->getWorld()->getHeight() && newPosition[0] >= 0 && newPosition[0] < this->getWorld()->getWidth())) return;
	if (this->getWorld()->validPosition(newPosition[0], newPosition[1])) {
		this->getWorld()->updateOrganism(this, lastPosition, newPosition);
		this->changePosition(newPosition[0], newPosition[1]);
	}
	else {
		this->getWorld()->getOrganismAt(newPosition)->collision(this);
	}
}

void Animal::collision(Organism* other) {
	// this		defending organism
	// other	attacking organism
	if (this->getName() == other->getName()) {
		Animal* a = (Animal*) other;
		if(this->canCopulate() && a->canCopulate())
			this->copulate(other);
	}
	else if (this->getStrength() > other->getStrength()) {
		this->getWorld()->getSpectator()->addComment("Collision: fight between " + this->getFullname() + "(" + to_string(this->getStrength()) + ") and " + other->getFullname() + "(" + to_string(other->getStrength()) + ") winner = " + this->getFullname());
		other->kill();
		this->getWorld()->removeOrganism(other, other->getPosition());
	}
	else if (this->getStrength() <= other->getStrength()) {
		this->getWorld()->getSpectator()->addComment("Collision: fight between " + other->getFullname() + "(" + to_string(other->getStrength()) + ") and " + this->getFullname() + "(" + to_string(this->getStrength()) + ") winner = " + other->getFullname());
		vector<int> position = this->getPosition();
		this->kill();
		this->getWorld()->removeOrganism(this, position);
		this->getWorld()->updateOrganism(other, other->getPosition(), position);
		other->changePosition(position[0], position[1]);
	}
}

void Animal::preventFromCopulation() {
	this->copulationCooldown = 5;
}

vector<int> Animal::copulate(Organism* other) {
	vector<int> empty = vector<int>(2);
	empty = { -1, -1 };
	Animal* a = (Animal*) other;
	if (!(this->canCopulate() && a->canCopulate())) return empty;
	this->preventFromCopulation();
	a->preventFromCopulation();
	vector<int> spawnSpots;
	int counter = 0, spot;
	while (counter < 4) {
		spot = rand() % 4 + 1;
		if (count(spawnSpots.begin(), spawnSpots.end(), spot) == 0) {
			spawnSpots.push_back(spot);
			counter++;
		}
	}
	for (auto i = 0; i < spawnSpots.size(); i++) {
		vector<int> spotThis;
		vector<int> spotOther;
		vector<int> currentPositionThis = this->getPosition();
		vector<int> currentPositionOther = other->getPosition();
		switch (spawnSpots[i]) {
		case 1:
			spotThis = { currentPositionThis[0], currentPositionThis[1] - 1 };
			spotOther = { currentPositionOther[0], currentPositionOther[1] - 1 };
			break;
		case 2:
			spotThis = { currentPositionThis[0] - 1, currentPositionThis[1] };
			spotOther = { currentPositionOther[0] - 1, currentPositionOther[1] };
			break;
		case 3:
			spotThis = { currentPositionThis[0], currentPositionThis[1] + 1 };
			spotOther = { currentPositionOther[0], currentPositionOther[1] + 1 };
			break;
		case 4:
			spotThis = { currentPositionThis[0] + 1, currentPositionThis[1] };
			spotOther = { currentPositionOther[0] + 1, currentPositionOther[1] };
			break;
		default:
			break;
		}
		if (!(spotThis[1] >= 0 && spotThis[1] < this->getWorld()->getHeight() && spotThis[0] >= 0 && spotThis[0] < this->getWorld()->getWidth())) {
			if (!(spotOther[1] >= 0 && spotOther[1] < this->getWorld()->getHeight() && spotOther[0] >= 0 && spotOther[0] < this->getWorld()->getWidth())) {
				continue;
			}
			else {
				if (this->getWorld()->validPosition(spotOther[0], spotOther[1])) {
					return spotOther;
				}
				else {
					continue;
				}
			}
		}
		else {
			if (this->getWorld()->validPosition(spotThis[0], spotThis[1])) {
				return spotThis;
			}
			else {
				continue;
			}
		}
	}
	this->getWorld()->getSpectator()->addComment("Copulation between 2 " + this->getFullname() + " failed");
	return empty;
}