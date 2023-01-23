#pragma once

#include <sstream>
#include <thread>
#include <semaphore>

#include "BubbleSort.h"

class SynchronizedList final
{
public:
	SynchronizedList() = default;
	SynchronizedList(const SynchronizedList&) = delete;
	SynchronizedList(SynchronizedList&&) = delete;
	SynchronizedList& operator=(const SynchronizedList&) = delete;
	SynchronizedList& operator=(SynchronizedList&&) = delete;

	~SynchronizedList();
	void run();
	void pushBack(const std::string& line);
	void sort();
	void exit();
private:
	friend std::ostream& operator <<(std::ostream& os, const SynchronizedList& synchronizedList);
	std::string toString() const;

	std::thread sortThread;
	Data* front = nullptr;
	Data* end = nullptr;

	std::mutex writeMutex;
	std::binary_semaphore sortSemaphore{ 0 };
	bool isFinished = false;
};

