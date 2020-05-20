#include "Turtle.h"
#include "World.h"

Turtle::Turtle(const int x, const int y, World* world) :Animal("Turtle", 'T', 2, 1, x, y, world, 1) {
	
}

Turtle::~Turtle() = default;

void Turtle::action() {
	int chance = rand() % 100 + 1;
	if (chance <= 75) return;
	Animal::action();
}

void Turtle::collision(Organism* other) {
	// this		defending organism
	// other	attacking organism
	if (this->getName() == other->getName()) {
		this->copulate(other);
	}
	else if (this->getStrength() > other->getStrength()) {
		other->kill();
		this->getWorld()->removeOrganism(other, other->getPosition());
	}
	else if (this->getStrength() <= other->getStrength()) {
		vector<int> position = this->getPosition();
		this->kill();
		this->getWorld()->removeOrganism(this, position);
		this->getWorld()->updateOrganism(other, other->getPosition(), position);
		other->changePosition(position[0], position[1]);
	}
}

vector<int> Turtle::copulate(Organism* other) {
	vector<int> ret = Animal::copulate(other);
	if (ret[0] == -1 && ret[1] == -1) {
		return ret;
	}
	else {
		Organism* newOrganism = new Turtle(ret[0], ret[1], this->getWorld());
		this->getWorld()->addOrganism(newOrganism);
		return ret;
	}
}

