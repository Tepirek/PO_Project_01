#pragma once
#include "Animal.h"

class Antelope final : public Animal {

public:
	Antelope(const int x, const int y, World* world);
	~Antelope();
	void collision(Organism* other) override;
	vector<int> copulate(Organism* other) override;
};

