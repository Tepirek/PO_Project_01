#include "Organism.h"
#include "World.h"
#include "random"
#include "time.h"
#include <conio.h>
#include <windows.h>
#include <chrono>
#include <thread>

int main(void) {
	SetConsoleTitle(TEXT("Arkadiusz Tepper (180287) - Symulacja Œwiata 2019/20"));
	srand(time(nullptr));
	printf("Welcome to the WORLD SIMULATOR v1.0\n");
	printf("Author: Arkadiusz Tepper 180287\n");
	printf("Press 1 to start a new game\n");
	printf("Press 2 to load saved game\n");
	int option;
	while (true) {
		printf("Option: ");
		scanf_s("%d", &option);
		if (option == 1 || option == 2) break;
		else {
			printf("Do not try to find any issues! :)\n");
			continue;
		}
	}
	switch (option) {
		World* world;
		case 1:
			system("cls");
			printf("Enter world size, keep in mind that the minimum area must be greater than 16!\n");
			int width, height;
			while (true) {
				printf("Size [width, height]: ");
				scanf_s("%d, %d", &width, &height);
				if (width * height > 16) break;
				else printf("Do not try to find any issues! :)\n");
			}
			world = new World(height, width);
			world->game();
			break;
		case 2:
			world = new World();
			printf("Success! Game will start in few seconds!\n");
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			system("cls");
			world->game();
			break;
		default:
			break;
	}
	return 0;
}