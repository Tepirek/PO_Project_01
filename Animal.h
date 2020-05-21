#pragma once
#include "Organism.h"

class Animal : public Organism {
	int step;
	bool copulationCooldown;
public:
	Animal(const string fullname, const char name, const int strength, const int initiative, const int x, const int y, World* world, const int step);
	virtual ~Animal();
	int getStep() const;
	bool canCopulate() const;
	void preventFromCopulation();
	void updateCopulationStatus();
	void setStep(const int step);
	void action() override;
	void collision(Organism* other) override;
	virtual vector<int> copulate(Organism* other);
};