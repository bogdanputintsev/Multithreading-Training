#include "InputManager.h"

InputManager::InputManager(SyncronizedList* _syncronizedList)
	: syncronizedList(_syncronizedList)
{
	assert(syncronizedList != nullptr && "InputManager received and invalid pointer on SyncronizedList on constructor. Value is NULL.");
}

void InputManager::input()
{
	std::string line;

	while (std::getline(std::cin, line))
	{
		assert(syncronizedList != nullptr && "InputManager contains invalid pointer on SyncronizedList. Value is NULL.");

		if (line.empty())
		{
			std::cout << *syncronizedList << "\n";
			continue;
		}
		else if (line == "/exit")
		{
			break;
		}
		else if (line == "/sort")
		{
			syncronizedList->sort();
			continue;
		}

		syncronizedList->emplaceBack(line);
	}
}
