#include "Sheep.h"
#include "World.h"

Sheep::Sheep(const int x, const int y, World* world) : Animal("Sheep", 'S', 4, 4, x, y, world, 1) {
	
}

Sheep::~Sheep() = default;

vector<int> Sheep::copulate(Organism * other) {
	vector<int> ret = Animal::copulate(other);
	if (ret[0] == -1 && ret[1] == -1) {
		return ret;
	}
	else {
		Organism* newOrganism = new Sheep(ret[0], ret[1], this->getWorld());
		this->getWorld()->addOrganism(newOrganism);
		return ret;
	}
}


