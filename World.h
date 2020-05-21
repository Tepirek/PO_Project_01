#pragma once
#include <iostream>
#include <vector>
#include "Organism.h"
#include "Spectator.h"
#include "Human.h"
using namespace std;

class World {
	bool initFromFile;
	int day;
	int width;
	int height;
	const int amountOfPlants = 5;
	const int amountOfAnimals = 5;
	Organism* player;
	Spectator* spectator;
	vector<vector<Organism*>> map;
	vector<Organism*> organisms;
	const char plantNames[5] = { '~', '*', '+', '-', 'x' };
	const char animalNames[5] = { 'W', 'S', 'F', 'T', 'A' };
	void insertNewOrganism(Organism* newOrganism);
	int max(const int a, const int b);
	void clearSave();
public:
	World();
	void saveGame();
	World(const int height, const int width);
	~World();
	int getWidth();
	int getHeight();
	Spectator* getSpectator() const;
	void game();
	void init();
	void nextTurn();
	void updateOrganism(Organism* organism, vector<int> lastPosition, vector<int> newPosition);
	void drawMap();
	void printInfo();
	bool validPosition(const int x, const int y);
	Organism* createOrganism(const char name, const int x, const int y, World* world);
	void spawnOrganisms(const int amount, const char* organismNames, bool plants);
	void addOrganism(Organism* organism);
	void removeOrganism(Organism* organism, vector<int> position);
	Organism* getOrganismAt(vector<int> position);
};
