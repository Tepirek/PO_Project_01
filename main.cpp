#include "Organism.h"
#include "World.h"
#include "random"
#include "time.h"
#include <conio.h>
#include <windows.h>

#define WIDTH 40	
#define HEIGHT 40

int main(void) {
	SetConsoleTitle(TEXT("Arkadiusz Tepper (180287) - Symulacja Œwiata 2019/20"));
	srand(time(nullptr));
	auto* world = new World(HEIGHT, WIDTH);
	world->game();
	return 0;
}