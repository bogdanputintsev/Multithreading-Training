#include <iostream>
#include <thread>
#include "InputManager.h"

int main()
{
	SyncronizedList list;

	InputManager inputManager(&list);
	std::thread inputThread(&InputManager::input, inputManager);
	
	inputThread.join();
	list.exit();

	return EXIT_SUCCESS;
}