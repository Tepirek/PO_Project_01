#include "Antelope.h"
#include "World.h"

Antelope::Antelope(const int x, const int y, World* world) : Animal("Antelope", 'A', 4, 4, x, y, world, 2) {
	
}

Antelope::~Antelope() = default;

void Antelope::collision(Organism* other) {
	if (this->getName() == other->getName()) {
		Animal* a = (Animal*)other;
		if (this->canCopulate() && a->canCopulate()) {
			this->copulate(other);
			this->preventFromCopulation();
			a->preventFromCopulation();
		}
		return;
	}
	int chance = rand() % 2;
	if (chance) {
		this->getWorld()->getSpectator()->addComment(this->getFullname() + " has escaped the fight with " + other->getFullname());
		this->action();
		return;
	}
	else {
		Animal::collision(other);
	}
}

vector<int> Antelope::copulate(Organism* other) {
	vector<int> ret = Animal::copulate(other);
	if (ret[0] == -1 && ret[1] == -1) {
		return ret;
	}
	else {
		this->getWorld()->getSpectator()->addComment("Copulation between 2 " + this->getFullname() + " succeeded!");
		Organism* newOrganism = new Antelope(ret[0], ret[1], this->getWorld());
		this->getWorld()->addOrganism(newOrganism);
		return ret;
	}
}
