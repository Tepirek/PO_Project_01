#include "Wolfberry.h"
#include "World.h"
#include "Human.h"

Wolfberry::Wolfberry(const int x, const int y, World* world) : Plant("Wolfberry", '-', 99, x, y, world, 4) {
	
}

Wolfberry::~Wolfberry() = default;

void Wolfberry::collision(Organism* other) {
	this->getWorld()->getSpectator()->addComment(other->getFullname() + " ate " + this->getFullname() + " and died!");
	this->getWorld()->removeOrganism(other, other->getPosition());
	this->getWorld()->removeOrganism(this, this->getPosition());
}
