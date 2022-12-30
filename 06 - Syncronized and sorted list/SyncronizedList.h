#pragma once

#include <iostream>
#include <sstream>
#include <list>
#include <queue>
#include <thread>
#include <semaphore>
#include <condition_variable>

#include "BubbleSort.h"

class SyncronizedList
{
public:
	SyncronizedList();
	~SyncronizedList();
	void emplaceBack(const std::string& line);
	void sort();
	void exit();
protected:
	friend std::ostream& operator << (std::ostream& os, const SyncronizedList& syncronizedList);
	std::string toString() const;
private:
	std::thread sortThread;
	Data* front = nullptr;
	Data* end = nullptr;

	std::binary_semaphore sortSemaphore{ 0 };
	bool isFinished = false;
};

