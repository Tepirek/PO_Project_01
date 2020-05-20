#include "Guarana.h"
#include "World.h"

Guarana::Guarana(const int x, const int y, World* world) : Plant("Guarana", '+', 0, x, y, world, 6) {
	
}

Guarana::~Guarana() = default;

void Guarana::collision(Organism* other) {
	int newStrength = other->getStrength() + 3;
	other->setStrength(newStrength);
	Plant::collision(other);
}
