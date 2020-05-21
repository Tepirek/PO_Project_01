#include "Human.h"
#include "World.h"
#include "Guarana.h"
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 77
#define KEY_LEFT 75
#define KEY_RIGHT 80

bool Human::isSkillActive() {
	return this->skillActive;
}


Human::Human(const int x, const int y, World* world) : Animal("Human", '@', 5, 4, x, y, world, 1) {
	this->specialSkillCooldown = 0;
	this->specialSkillDuration = 0;
	this->alive = true;
	this->skillActive = false;
}

Human::~Human() = default;

int Human::getCooldown() const {
	return this->specialSkillCooldown;
}

bool Human::isAlive() const {
	return this->alive;
}

bool Human::specialSkillAvailable() {
	if (this->specialSkillCooldown == 0) return true;
	return false;
}

void Human::activateSkill() {
	if (this->specialSkillAvailable() && !this->isSkillActive()) {
		this->specialSkillDuration = 5;
		this->skillActive = true;
		this->getWorld()->getSpectator()->addComment(this->getFullname() + " has activated the special ability!");
	} 
	else
		this->getWorld()->getSpectator()->addComment(this->getFullname() + " could not activated the special ability!");
}

void Human::updateSkill() {
	if (this->specialSkillDuration > 2) {
		this->setStep(2);
		this->specialSkillDuration--;
	}
	else if (this->specialSkillDuration > 0) {
		int chance = rand() % 2;
		if (chance) this->setStep(2);
		else this->setStep(1);
		this->specialSkillDuration--;
		if (this->specialSkillDuration == 1) {
			this->specialSkillCooldown == 5;
		}
	}
	else if (this->specialSkillDuration == 0) {
		if (this->specialSkillCooldown > 0) {
			this->specialSkillCooldown--;
		}
		else if (this->specialSkillCooldown == 0 && this->skillActive) {
			this->specialSkillCooldown = 5;
		}
		this->skillActive = false;
		this->setStep(1);
	}
}

void Human::action() {
	vector<int> lastPosition = this->getPosition();
	vector<int> newPosition;
	bool wrongKey = true;
	while (wrongKey) {
		if (_getch() == 224) {
			switch (_getch()) {
			case KEY_UP:
				newPosition = { lastPosition[0], lastPosition[1] - this->getStep() };
				wrongKey = false;
				break;
			case KEY_LEFT:
				newPosition = { lastPosition[0] - this->getStep(), lastPosition[1] };
				wrongKey = false;
				break;
			case KEY_DOWN:
				newPosition = { lastPosition[0] + this->getStep(), lastPosition[1] };
				wrongKey = false;
				break;
			case KEY_RIGHT:
				newPosition = { lastPosition[0], lastPosition[1] + this->getStep() };
				wrongKey = false;
				break;
			default:
				continue;
				break;
			}
		}
		else if (_getch() == 'r') {
			this->activateSkill();
			return;
		}
		else continue;
	}
	updateSkill();
	if (!(newPosition[1] >= 0 && newPosition[1] < this->getWorld()->getHeight() && newPosition[0] >= 0 && newPosition[0] < this->getWorld()->getWidth())) return;
	if (this->getWorld()->validPosition(newPosition[0], newPosition[1])) {
		this->getWorld()->updateOrganism(this, lastPosition, newPosition);
		this->changePosition(newPosition[0], newPosition[1]);
	}
	else {
		this->getWorld()->getOrganismAt(newPosition)->collision(this);
	}
}


