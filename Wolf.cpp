#include "Wolf.h"
#include "World.h"

Wolf::Wolf(const int x, const int y, World* world) : Animal("Wolf", 'W', 9, 5, x, y, world, 1) {
	
}

Wolf::~Wolf() = default;

vector<int> Wolf::copulate(Organism* other) {
	vector<int> ret = Animal::copulate(other);
	if (ret[0] == -1 && ret[1] == -1) {
		return ret;
	}
	else {
		Organism* newOrganism = new Wolf(ret[0], ret[1], this->getWorld());
		this->getWorld()->addOrganism(newOrganism);
		return ret;
	}
}