#include "Spectator.h"
#include <stdio.h>

Spectator::Spectator() {

}

Spectator::~Spectator() = default;

void Spectator::addComment(const string comment) {
	this->comments.push_back(comment);
}

void Spectator::commentEvents(const int limit, bool x) {
	printf("Event log:\n----------\n");
	int a = this->comments.size();
	if (x && (limit < this->comments.size())) a = limit;
	for (int i = 0; i < a; i++) {
		printf("%d. %s\n", i + 1, this->comments[i]);
	}
}

void Spectator::clearEvents() {
	this->comments.clear();
}