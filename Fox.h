#pragma once
#include "Animal.h"

class Fox final : public Animal {

public:
	Fox(const int x, const int y, World* world);
	~Fox();
	void action() override;
	vector<int> copulate(Organism* other) override;
};

