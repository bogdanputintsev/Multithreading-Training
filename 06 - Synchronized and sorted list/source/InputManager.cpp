#include "InputManager.h"

#include <cassert>
#include <iostream>

InputManager::InputManager(SynchronizedList* synchronizedList)
	: synchronizedList(synchronizedList)
{
	assert(synchronizedList != nullptr && "InputManager received and invalid pointer on SynchronizedList on constructor. Value is NULL.");
}

void InputManager::input() const
{
	std::string line;

	while (std::getline(std::cin, line))
	{
		assert(synchronizedList != nullptr && "InputManager contains invalid pointer on SynchronizedList. Value is NULL.");

		if (line.empty())
		{
			printf("%s\n", synchronizedList->toString().c_str());
			continue;
		}

		if (line == "/exit")
		{
			break;
		}

		if (line == "/sort")
		{
			synchronizedList->sort();
			continue;
		}

		synchronizedList->pushBack(line);
	}
}
