#include "Heracleum.h"
#include "World.h"

Heracleum::Heracleum(const int x, const int y, World* world) : Plant("Heracleum", 'x', 10, x, y, world, 2) {
	
}

Heracleum::~Heracleum() = default;

void Heracleum::action() {
	int chance = rand() % 100 + 1;
	if (chance >= this->getSpawnRate()) return;
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
				this->getWorld()->addOrganism(this->getWorld()->createOrganism('x', spot[0], spot[1], this->getWorld()));
				break;
		}
	}
}

void Heracleum::collision(Organism* other) {
	
}


