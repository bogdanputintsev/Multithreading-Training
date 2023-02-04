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
	void runAutoSorting();
	void pushBack(const std::string& line);
	void sort();
	void exit();
	std::string toString() const;
private:
	friend std::ostream& operator <<(std::ostream& os, const SynchronizedList& synchronizedList);

	std::thread sortThread;
	Data* front = nullptr;
	Data* end = nullptr;

	std::mutex writeMutex;
	std::binary_semaphore sortSemaphore{ 0 };
	bool isFinished = false;

	static constexpr int SORT_WAIT_FOR_SECS = 5;
};

