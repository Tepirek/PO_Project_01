#include "Dandelion.h"

Dandelion::Dandelion(const int x, const int y, World* world) : Plant("Dandelion", '*', 0, x, y, world, 4) {
	
}

Dandelion::~Dandelion() = default;

void Dandelion::action() {
	for (auto i = 0; i < 3; i++) {
		Plant::action();
	}
}
