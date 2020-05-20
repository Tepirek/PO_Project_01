#include "Wolfberry.h"
#include "World.h"
#include "Human.h"

Wolfberry::Wolfberry(const int x, const int y, World* world) : Plant("Wolfberry", '-', 99, x, y, world, 4) {
	
}

Wolfberry::~Wolfberry() = default;

void Wolfberry::collision(Organism* other) {
	Plant::collision(other);
	other->kill();
	this->getWorld()->removeOrganism(other, other->getPosition());
}

