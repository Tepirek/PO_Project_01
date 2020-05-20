#pragma once
#include "Plant.h"

class Dandelion : public Plant {

public:
	Dandelion(const int x, const int y, World* world);
	~Dandelion();
	void action() override;
};