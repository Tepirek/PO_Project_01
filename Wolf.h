#pragma once
#include "Animal.h"

class Wolf final : public Animal {

public:
	Wolf(const int x, const int y, World* world);
	~Wolf();
	vector<int> copulate(Organism* other) override;
};

