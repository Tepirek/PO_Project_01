#include "Grass.h"

Grass::Grass(const int x, const int y, World* world) : Plant("Grass", '~', 0, x, y, world, 6) {
	
}

Grass::~Grass() = default;
