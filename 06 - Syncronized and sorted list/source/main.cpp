#include <iostream>
#include <thread>
#include "InputManager.h"

int main()
{
	SynchronizedList list;
	list.run();

	InputManager inputManager(&list);
	std::thread inputThread(&InputManager::input, inputManager);
	inputThread.join();

	list.exit();

	return EXIT_SUCCESS;
}