#include "Organism.h"
#include <iostream>
using namespace std;

Organism::Organism(const string fullname, const char name, const int strength, const int initiative, const int x, const int y, World* world) {
	this->fullname = fullname;
	this->name = name;
	this->strength = strength;
	this->initiative = initiative;
	this->age = 1;
	this->alive = true;

	this->position = vector<int>(2);
	this->position[0] = x;
	this->position[1] = y;
	this->world = world;
}

Organism::~Organism() = default;

string Organism::getFullname() const {
	return this->fullname;
}

char Organism::getName() const {
	return this->name;
}

int Organism::getStrength() const {
	return this->strength;
}

int Organism::getInitiative() const {
	return this->initiative;
}

int Organism::getAge() const {
	return this->age;
}

bool Organism::isAlive() const {
	return this->alive;
}

vector<int> Organism::getPosition() const {
	return this->position;
}

World* Organism::getWorld() const {
	return this->world;
}

void Organism::setName(const char name) {
	this->name = name;
}

void Organism::setStrength(const int newStrength) {
	this->strength = newStrength;
}

void Organism::incrementAge() {
	this->age++;
}

void Organism::kill() {
	this->alive = false;
}

void Organism::changePosition(const int x, const int y) {
	this->position[0] = x;
	this->position[1] = y;
}

void Organism::draw() const {
	printf("%c ", this->name);
}