#include "Antelope.h"
#include "World.h"

Antelope::Antelope(const int x, const int y, World* world) : Animal("Antelope", 'A', 4, 4, x, y, world, 2) {
	
}

Antelope::~Antelope() = default;

void Antelope::collision(Organism* other) {
	
}

vector<int> Antelope::copulate(Organism* other) {
	vector<int> ret = Animal::copulate(other);
	if (ret[0] == -1 && ret[1] == -1) {
		return ret;
	}
	else {
		Organism* newOrganism = new Antelope(ret[0], ret[1], this->getWorld());
		this->getWorld()->addOrganism(newOrganism);
		return ret;
	}
}
