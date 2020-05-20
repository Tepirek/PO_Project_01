#pragma once
#include "Animal.h"

class Human final : public Animal {
	int specialSkillCooldown;
	bool alive;
	bool skillActive;
	bool isSkillActive();

public:
	Human(const int x, const int y, World* world);
	~Human();
	bool isAlive();
	bool specialSkillAvailable();
	void specialSkill();
	void updateSkill();
	void action() override;
};

