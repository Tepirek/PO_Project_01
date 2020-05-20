#pragma once
#include "Animal.h"

class Turtle final : public Animal {

public:
	Turtle(const int x, const int y, World* world);
	~Turtle();
	void action() override;
	void collision(Organism* other) override;
	vector<int> copulate(Organism* other) override;
};

