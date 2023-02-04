#pragma once

#include "SynchronizedList.h"

class InputManager final
{
public:
	explicit InputManager(SynchronizedList* synchronizedList);
	void input() const;
private:
	SynchronizedList* synchronizedList = nullptr;
};

