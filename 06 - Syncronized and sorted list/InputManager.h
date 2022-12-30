#pragma once

#include <iostream>
#include <sstream>
#include <mutex>
#include <list>
#include <cassert>
#include "SyncronizedList.h"

class InputManager
{
public:
	InputManager(SyncronizedList* _syncronizedList);
	void input();
private:
	SyncronizedList* syncronizedList = nullptr;
};

