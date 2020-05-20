#include "World.h"
#include "Dandelion.h"
#include "Grass.h"
#include "Human.h"
#include "random"
#include "time.h"
#include "Guarana.h"
#include "Wolfberry.h"
#include "Heracleum.h"
#include "Fox.h"
#include "Antelope.h"
#include "Turtle.h"
#include "Wolf.h"
#include "Sheep.h"

void World::insertNewOrganism(Organism* newOrganism) {
	for (auto i = 0; i < this->organisms.size(); i++) {
		if (this->organisms[i]->getInitiative() <= newOrganism->getInitiative()) {
			this->organisms.insert(this->organisms.begin() + i, newOrganism);
			return;
		}
	}
	this->organisms.push_back(newOrganism);
}

World::World(const int height, const int width) {
	this->day = 0;
	this->height = height;
	this->width = width;
	this->player = nullptr;
	this->map = vector<vector<Organism*>>(this->height);
	for(auto i = 0; i < this->height; i++) {
		this->map[i] = vector<Organism*>(this->width);
	}
}

World::~World() = default;

int World::getWidth() {
	return this->width;
}

int World::getHeight() {
	return this->height;
}

void World::game() {
	this->init();
	this->drawMap();
	while (this->player->isAlive()) {
		this->nextTurn();
		this->drawMap();
		this->printInfo();
	}
}

void World::init() {
	auto posX = this->width / 2;
	auto posY = this->height / 2;
	this->player = new Human(posX, posY, this);
	this->organisms.push_back(this->player);
	this->map[posY][posX] = this->player;
	this->spawnOrganisms(this->amountOfPlants, this->plantNames, true);
	this->spawnOrganisms(this->amountOfAnimals, this->animalNames, false);
}

void World::nextTurn() {
	for (auto i = 0; i < this->organisms.size(); i++) {
		this->organisms[i]->action();
		this->organisms[i]->incrementAge();
	}
	this->day++;
}

void World::updateOrganism(Organism* organism, vector<int> lastPosition, vector<int> newPosition) {
	this->map[lastPosition[1]][lastPosition[0]] = nullptr;
	this->map[newPosition[1]][newPosition[0]] = organism;
}

void World::drawMap() {
	system("cls");
	for(auto i = -1; i < this->height + 1; i++) {
		for(auto j = -1; j < this->width + 1; j++) {
			if (i == -1 || j == -1 || i == this->height || j == this->width) printf("# ");
			else if (this->map[i][j] == nullptr) printf("  ");
			else this->map[i][j]->draw();
		}
		printf("\n");
	}
}

void World::printInfo() {
	printf("Day: %d\n", this->day);
	printf("Organisms: %d\n", this->organisms.size());
}

bool World::validPosition(const int x, const int y) {
	if (this->map[y][x] == nullptr) return true;
	return false;
}

Organism* World::createOrganism(const char name, const int x, const int y, World* world) {
	Organism* newOrganism = nullptr;
	switch (name) {
		case '~':
			newOrganism = new Grass(x, y, world);
			break;
		case '*':
			newOrganism = new Dandelion(x, y, world);
			break;
		case '+':
			newOrganism = new Guarana(x, y, world);
			break;
		case '-':
			newOrganism = new Wolfberry(x, y, world);
			break;
		case 'x':
			newOrganism = new Heracleum(x, y, world);
			break;
		case 'W':
			newOrganism = new Wolf(x, y, world);
			break;
		case 'S':
			newOrganism = new Sheep(x, y, world);
			break;
		case 'F':
			newOrganism = new Fox(x, y, world);
			break;
		case 'T':
			newOrganism = new Turtle(x, y, world);
			break;
		case 'A':
			newOrganism = new Antelope(x, y, world);
			break;
		default:
			break;
	}
	return newOrganism;
}

void World::spawnOrganisms(const int amount, const char* organismNames, bool plants) {
	int posX, posY, initSpawnAmount;
	if (plants) initSpawnAmount = 4;
	else initSpawnAmount = 4;
	for (auto i = 0; i < amount; i++) {
		int counter = 0;
		while (counter < initSpawnAmount) {
			posX = rand() % (this->width);
			posY = rand() % (this->height); 
			if (this->validPosition(posX, posY)) {
				Organism* newOrganism = this->createOrganism(organismNames[i], posX, posY, this);;
				this->map[posY][posX] = newOrganism;
				this->insertNewOrganism(newOrganism);
				counter++;
			}
		}
	}
}

void World::addOrganism(Organism* organism) {
	vector<int> position = organism->getPosition();
	this->map[position[1]][position[0]] = organism;
	this->insertNewOrganism(organism);
}

void World::removeOrganism(Organism* organism, vector<int> position) {
	this->map[position[1]][position[0]] = nullptr;
	for (int i = 0; i < this->organisms.size(); i++) {
		if (this->organisms[i] == organism) {
			this->organisms.erase(this->organisms.begin() + i);
			break;
		}
	}
}

Organism* World::getOrganismAt(vector<int> position) {
	return this->map[position[1]][position[0]];
}