#pragma once
#include "Animal.h"

class Human final : public Animal {
	int specialSkillCooldown;
	int specialSkillDuration;
	bool alive;
	bool skillActive;
	bool isSkillActive();

public:
	Human(const int x, const int y, World* world);
	~Human();
	int getCooldown() const;
	bool isAlive() const;
	bool specialSkillAvailable();
	void activateSkill();
	void updateSkill();
	void action() override;
};

