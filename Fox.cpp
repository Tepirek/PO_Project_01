#include "Fox.h"
#include "World.h"

Fox::Fox(const int x, const int y, World* world) : Animal("Fox", 'F', 3, 7, x, y, world, 1) {
	
}

Fox::~Fox() = default;

void Fox::action() {
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
		// collision
		Organism* other = this->getWorld()->getOrganismAt(newPosition);
		if (this->getName() == other->getName()) {
			other->collision(this);
			return;
		}
		if (this->getStrength() <= other->getStrength()) {
			this->getWorld()->getSpectator()->addComment(this->getFullname() + " did not move, because the enemy " + other->getFullname() + " was stronger!");
		}
		else other->collision(this);
	}
}

vector<int> Fox::copulate(Organism* other) {
	vector<int> ret = Animal::copulate(other);
	if (ret[0] == -1 && ret[1] == -1) {
		return ret;
	}
	else {
		this->getWorld()->getSpectator()->addComment("Copulation between 2 " + this->getFullname() + " succeeded!");
		Organism* newOrganism = new Fox(ret[0], ret[1], this->getWorld());
		this->getWorld()->addOrganism(newOrganism);
		return ret;
	}
}

