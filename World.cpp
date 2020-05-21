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
#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <iostream>
using namespace std;

#pragma warning(disable:4996)

/*
void World::insertNewOrganism(Organism* newOrganism) {
	for (auto i = 0; i < this->organisms.size(); i++) {
		if (this->organisms[i]->getInitiative() < newOrganism->getInitiative()) {
			this->organisms.insert(this->organisms.begin() + i, newOrganism);
			return;
		}
	}
	this->organisms.push_back(newOrganism);
}
*/

void World::insertNewOrganism(Organism* newOrganism) {
	this->organisms.push_back(newOrganism);
	bool swapped;
	for (int i = 0; i < this->organisms.size(); i++) {
		swapped = false;
		for (int j = 0; j < this->organisms.size() - i - 1; j++) {
			if (this->organisms[j]->getInitiative() < this->organisms[j + 1]->getInitiative()) {
				Organism* tmp = this->organisms[j];
				this->organisms[j] = this->organisms[j + 1];
				this->organisms[j + 1] = tmp;
				swapped = true;
			}
			else if (this->organisms[j]->getInitiative() == this->organisms[j + 1]->getInitiative()) {
				if (this->organisms[j]->getAge() < this->organisms[j + 1]->getAge()) {
					Organism* tmp = this->organisms[j];
					this->organisms[j] = this->organisms[j + 1];
					this->organisms[j + 1] = tmp;
					swapped = true;
				}
			}
		}
		if (swapped == false) break;
	}
}

int World::max(const int a, const int b) {
	if (a > b) return a;
	return b;
}

void World::clearSave() {
	ofstream file;
	file.open("save.txt");
	file.close();
}

void World::saveGame() {
	this->clearSave();
	ofstream stream;
	stream.open("save.txt");
	stream << this->width << ", " << this->height << ", " << this->day << endl;
	for (int i = 0; i < this->organisms.size(); i++) {
		Organism* o = this->organisms[i];
		char name = o->getName();
		int strength = o->getStrength();
		int age = o->getAge();
		int posX = o->getPosition()[0];
		int posY = o->getPosition()[1];
		stream << name << ", " << strength << ", " << age << ", " << posX << ", " << posY << endl;
	}
	stream.close();
}

World::World() {
	this->initFromFile = true;
	FILE* fp;
	fp = fopen("save.txt", "r");
	int width, height, day;
	fscanf(fp, "%d, %d, %d\n", &width, &height, &day);
	printf("%d, %d, %d\n", width, height, day);
	this->width = width;
	this->height = height;
	this->day = day;
	this->spectator = new Spectator();
	this->map = vector<vector<Organism*>>(this->height);
	for (auto i = 0; i < this->height; i++) {
		this->map[i] = vector<Organism*>(this->width);
	}
	char name;
	int strength, age, posX, posY;
	while (fscanf(fp, "%c, %d, %d, %d, %d\n", &name, &strength, &age, &posX, &posY) == 5) {
		fscanf(fp, "%c, %d, %d, %d, %d\n", &name, &strength, &age, &posX, &posY);
		Organism* o = this->createOrganism(name, posX, posY, this);
		o->setStrength(strength);
		o->setAge(age);
		this->organisms.push_back(o);
		this->addOrganism(o);
		printf("%c, %d, %d, %d, %d\n", name, strength, age, posX, posY);
	}
	this->player = this->organisms.front();
}

World::World(const int height, const int width) {
	this->initFromFile = false;
	this->day = 0;
	this->height = height;
	this->width = width;
	this->player = nullptr;
	this->spectator = new Spectator();
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

Spectator* World::getSpectator() const {
	return this->spectator;
}

void World::game() {
	if (!this->initFromFile) {
		this->init();
	}
	this->drawMap();
	this->printInfo();
	while (this->player->isAlive() && this->width * this->height != this->organisms.size()) {
		this->nextTurn();
		this->drawMap();
		this->printInfo();
		this->spectator->commentEvents(10, true);
		this->spectator->clearEvents();
		if(this->day % 10 == 0) this->saveGame();
	}
	// this->clearSave();
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
		// std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		// this->drawMap();
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
	printf("Player:\n");
	printf("  alive:    %s\n", (this->player->isAlive()) ? "true" : "false");
	printf("  strength: %d\n", this->player->getStrength());
	Human* h = (Human*) this->player;
	printf("  cooldown: %d\n", h->getCooldown());
}

bool World::validPosition(const int x, const int y) {
	if (this->map[y][x] == nullptr) return true;
	return false;
}

Organism* World::createOrganism(const char name, const int x, const int y, World* world) {
	Organism* newOrganism = nullptr;
	switch (name) {
		case '@':
			newOrganism = new Human(x, y, world);
			break;
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
	if (plants) initSpawnAmount = this->max(1, this->width * this->height / 200);
	else initSpawnAmount = this->max(2, this->width * this->height / 200);
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
	organism->kill();
	this->map[position[1]][position[0]] = nullptr;
	for (int i = 0; i < this->organisms.size(); i++) {
		if (this->organisms[i] == organism) {
			this->organisms.erase(this->organisms.begin() + i);
			break;
		}
	}
	delete organism;
}

Organism* World::getOrganismAt(vector<int> position) {
	return this->map[position[1]][position[0]];
}