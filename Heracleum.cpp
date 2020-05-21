#include "Heracleum.h"
#include "World.h"

Heracleum::Heracleum(const int x, const int y, World* world) : Plant("Heracleum", 'x', 10, x, y, world, 2) {
	
}

Heracleum::~Heracleum() = default;

void Heracleum::action() {
	Plant::action();
	vector<int> position = this->getPosition();
	if (position[0] >= 0 && position[0] < this->getWorld()->getWidth() && position[1] - 1 >= 0 && position[1] - 1 < this->getWorld()->getHeight()) {
		vector<int> newPosition = position;
		newPosition[0] += 0;
		newPosition[1] += -1;
		if (!this->getWorld()->validPosition(position[0], position[1] - 1) && !this->getWorld()->getOrganismAt(newPosition)->isPlant()) {
			this->getWorld()->getSpectator()->addComment(this->getFullname() + " has killed " + this->getWorld()->getOrganismAt(newPosition)->getFullname() + " around itself!");
			this->getWorld()->removeOrganism(this->getWorld()->getOrganismAt(newPosition), newPosition);
		}
	}
	if (position[0] - 1 >= 0 && position[0] - 1 < this->getWorld()->getWidth() && position[1] - 1 >= 0 && position[1] - 1 < this->getWorld()->getHeight()) {
		vector<int> newPosition = position;
		newPosition[0] += -1;
		newPosition[1] += 0;
		if (!this->getWorld()->validPosition(position[0] - 1, position[1]) && !this->getWorld()->getOrganismAt(newPosition)->isPlant()) {
			this->getWorld()->getSpectator()->addComment(this->getFullname() + " has killed " + this->getWorld()->getOrganismAt(newPosition)->getFullname() + " around itself!");
			this->getWorld()->removeOrganism(this->getWorld()->getOrganismAt(newPosition), newPosition);
		}
	}
	if (position[0] >= 0 && position[0] < this->getWorld()->getWidth() && position[1] + 1 >= 0 && position[1] + 1 < this->getWorld()->getHeight()) {
		vector<int> newPosition = position;
		newPosition[0] += 0;
		newPosition[1] += 1;
		if (!this->getWorld()->validPosition(position[0], position[1] + 1) && !this->getWorld()->getOrganismAt(newPosition)->isPlant()) {
			this->getWorld()->getSpectator()->addComment(this->getFullname() + " has killed " + this->getWorld()->getOrganismAt(newPosition)->getFullname() + " around itself!");
			this->getWorld()->removeOrganism(this->getWorld()->getOrganismAt(newPosition), newPosition);
		}
	}
	if (position[0] + 1 >= 0 && position[0] + 1 < this->getWorld()->getWidth() && position[1] >= 0 && position[1] < this->getWorld()->getHeight()) {
		vector<int> newPosition = position;
		newPosition[0] += 1;
		newPosition[1] += 0;
		if (!this->getWorld()->validPosition(position[0] + 1, position[1]) && !this->getWorld()->getOrganismAt(newPosition)->isPlant()) {
			this->getWorld()->getSpectator()->addComment(this->getFullname() + " has killed " + this->getWorld()->getOrganismAt(newPosition)->getFullname() + " around itself!");
			this->getWorld()->removeOrganism(this->getWorld()->getOrganismAt(newPosition), newPosition);
		}
	}
}

void Heracleum::collision(Organism* other) {
	this->getWorld()->getSpectator()->addComment(other->getFullname() + " ate " + this->getFullname() + " and died!");
	this->getWorld()->removeOrganism(other, other->getPosition());
	this->getWorld()->removeOrganism(this, this->getPosition());
}