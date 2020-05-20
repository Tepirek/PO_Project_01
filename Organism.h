#pragma once
#include <iostream>
#include <vector>
using namespace std;

class World;

class Organism {
	string fullname;
	char name;
	int strength;
	int initiative;
	int age;
	bool alive;
	vector<int> position;
	World* world;
public:
	Organism(const string fullname, const char name, const int strength, const int initiative, const int x, const int y, World* world);
	virtual ~Organism();
	string getFullname() const;
	char getName() const;
	int getStrength() const;
	int getInitiative() const;
	int getAge() const;
	bool isAlive() const;
	vector<int> getPosition() const;
	World* getWorld() const;
	void setName(const char name);
	void setStrength(const int newStrength);
	void incrementAge();
	void kill();
	void changePosition(const int x, const int y);
	void draw() const;
	virtual void action() = 0;
	virtual void collision(Organism* other) = 0;
};

