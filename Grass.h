#pragma once
#include "Plant.h"

class Grass final : public Plant {

public:
	Grass(const int x, const int y, World* world);
	~Grass();
};

