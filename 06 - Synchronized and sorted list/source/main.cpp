#include <iostream>
#include <thread>
#include "InputManager.h"
#include "Sorter.h"

int main()
{
	SynchronizedList list;

	InputManager inputManager(&list);
	std::thread inputThread(&InputManager::input, inputManager);

	const auto sorter = std::make_unique<Sorter>(&list);
	list.attach(sorter.get());
	std::thread sorterThread([&]() {
		sorter->sortLoop();
	});

	inputThread.join();

	sorter->stop();
	sorterThread.join();

	return EXIT_SUCCESS;
}