#pragma once
#include "Plant.h"

class Wolfberry : public Plant {

public:
	Wolfberry(const int x, const int y, World* world);
	~Wolfberry();
	void collision(Organism* other) override;
};

