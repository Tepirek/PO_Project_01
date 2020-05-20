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
	this->alive = true;
	this->skillActive = false;
}

Human::~Human() = default;

bool Human::isAlive() {
	return this->alive;
}

bool Human::specialSkillAvailable() {
	if (this->specialSkillCooldown == 0) return true;
	return false;
}

void Human::specialSkill() {
	if (this->specialSkillAvailable()) {
		this->setStep(2);
		this->specialSkillCooldown = 5;
		this->skillActive = true;
	}
}

void Human::updateSkill() {

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
		else if (getchar() == 'r') {
			if (this->specialSkillAvailable) {
				this->specialSkill();
			}
		}
		else continue;
		if (!(newPosition[1] >= 0 && newPosition[1] < this->getWorld()->getHeight() && newPosition[0] >= 0 && newPosition[0] < this->getWorld()->getWidth())) return;
		if (this->getWorld()->validPosition(newPosition[0], newPosition[1])) {
			this->getWorld()->updateOrganism(this, lastPosition, newPosition);
			this->changePosition(newPosition[0], newPosition[1]);
		}
		else {
			this->getWorld()->getOrganismAt(newPosition)->collision(this);
		}
	}
}


