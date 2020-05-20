#pragma once
#include "Plant.h"
class Guarana : public Plant {

public:
	Guarana(const int x, const int y, World* world);
	~Guarana();
	void collision(Organism* other) override;
};

