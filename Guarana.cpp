#include "Guarana.h"
#include "World.h"
#include <iostream>

Guarana::Guarana(const int x, const int y, World* world) : Plant("Guarana", '+', 0, x, y, world, 6) {
	
}

Guarana::~Guarana() = default;

void Guarana::collision(Organism* other) {
	string oS = std::to_string(other->getStrength());
	string nS = std::to_string(other->getStrength() + 3);
	this->getWorld()->getSpectator()->addComment(other->getFullname() + " ate " + this->getFullname() + " and gained 3 strength (" + oS + " -> "+ nS + ")");
	int newStrength = other->getStrength() + 3; 
	other->setStrength(newStrength);
	Plant::collision(other);
}
