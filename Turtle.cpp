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
		Animal* a = (Animal*)other;
		if (this->canCopulate() && a->canCopulate()) {
			this->copulate(other);
			this->preventFromCopulation();
			a->preventFromCopulation();
		}
		return;
	}
	else if (other->getStrength() < 5) {
		this->getWorld()->getSpectator()->addComment(this->getFullname() + " has blocked the attack from " + other->getFullname());
		return;
	}
	else {
		this->getWorld()->getSpectator()->addComment("collision: fight between " + this->getFullname() + " and " + other->getFullname() + " winner = " + other->getFullname());
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
		this->getWorld()->getSpectator()->addComment("Copulation between 2 " + this->getFullname() + "s succeeded!");
		Organism* newOrganism = new Turtle(ret[0], ret[1], this->getWorld());
		this->getWorld()->addOrganism(newOrganism);
		return ret;
	}
}

