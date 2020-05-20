#pragma once
#include "Animal.h"

class Sheep final : public Animal {

public:
	Sheep(const int x, const int y, World* world);
	~Sheep();
	vector<int> copulate(Organism* other) override;
};

