#include "Plant.h"
#include "World.h"
#include "Grass.h"
#include "Wolfberry.h"
#include "Heracleum.h"
#include "Dandelion.h"
#include "Guarana.h"

Plant::Plant(const string fullname, const char name, const int strength, const int x, const int y, World* world, const int spawnRate) : Organism(fullname, name, strength, 0, x, y, world) {
	this->spawnRate = spawnRate;
}

Plant::~Plant() = default;

int Plant::getSpawnRate() const {
	return this->spawnRate;
}

void Plant::action() {
	int chance = rand() % 100 + 1;
	if (chance >= this->spawnRate) return;
	vector<int> spawnSpots;
	int counter = 0, spot;
	while (counter < 4) {
		spot = rand() % 4 + 1;
		if (count(spawnSpots.begin(), spawnSpots.end(), spot) == 0) {
			spawnSpots.push_back(spot);
			counter++;
		}
	}
	for (auto i = 0; i < spawnSpots.size(); i++) {
		vector<int> spot;
		vector<int> currentPosition = this->getPosition();
		switch (spawnSpots[i]) {
		case 1:
			spot = { currentPosition[0], currentPosition[1] - 1 };
			break;
		case 2:
			spot = { currentPosition[0] - 1, currentPosition[1] };
			break;
		case 3:
			spot = { currentPosition[0], currentPosition[1] + 1 };
			break;
		case 4:
			spot = { currentPosition[0] + 1, currentPosition[1] };
			break;
		default:
			break;
		}
		if (!(spot[1] >= 0 && spot[1] < this->getWorld()->getHeight() && spot[0] >= 0 && spot[0] < this->getWorld()->getWidth())) continue;
		if (this->getWorld()->validPosition(spot[0], spot[1])) {
			if (dynamic_cast<Grass*>(this) != nullptr) {
				this->getWorld()->addOrganism(this->getWorld()->createOrganism('~', spot[0], spot[1], this->getWorld()));
				break;
			}
			else if (dynamic_cast<Dandelion*>(this) != nullptr) {
				this->getWorld()->addOrganism(this->getWorld()->createOrganism('*', spot[0], spot[1], this->getWorld()));
				break;
			}
			else if (dynamic_cast<Guarana*>(this) != nullptr) {
				this->getWorld()->addOrganism(
					this->getWorld()->createOrganism('+', spot[0], spot[1], this->getWorld()));
				break;
			}
			else if (dynamic_cast<Wolfberry*>(this) != nullptr) {
				this->getWorld()->addOrganism(this->getWorld()->createOrganism('-', spot[0], spot[1], this->getWorld()));
				break;
			}
		}
	}
}

void Plant::collision(Organism* other) {
	vector<int> position = this->getPosition();
	this->getWorld()->removeOrganism(this, position);
	this->getWorld()->updateOrganism(other, other->getPosition(), position);
	other->changePosition(position[0], position[1]);
}

