#pragma once
#include <string>
#include <vector>
using namespace std;

class Spectator {
	vector<string> comments;
public:
	Spectator();
	~Spectator();
	void addComment(const string comment);
	void commentEvents(const int limit, bool x);
	void clearEvents();
};

