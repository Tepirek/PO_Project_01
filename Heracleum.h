#pragma once
#include "Plant.h"
class Heracleum : public Plant {

public:
	Heracleum(const int x, const int y, World* world);
	~Heracleum();
	void action() override;
	void collision(Organism* other) override;
};

