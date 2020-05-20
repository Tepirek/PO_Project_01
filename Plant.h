#pragma once
#include "Organism.h"

class Plant : public Organism {
	int spawnRate;
public:
	Plant(const string fullname, const char name, const int strength, const int x, const int y, World* world, const int spawnRate);
	~Plant();
	int getSpawnRate() const;
	void action() override;
	void collision(Organism* other) override;
};

