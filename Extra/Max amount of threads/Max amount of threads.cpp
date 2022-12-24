#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <cassert>

/*
Thread	Execution time	Valid result
1-8		2.02			T
1000	3.12			T
2000	6.71			T
5000	20.288 ms		T
10000	60.0			T
30000	257.0			T
80000	1056 s			?
*/
namespace
{
	const int NUM_SECONDS_TO_WAIT = 2000;
	const int NUM_THREADS = 80000;

	void sleepThread(const int idx)
	{
		std::this_thread::sleep_for(std::chrono::seconds(NUM_SECONDS_TO_WAIT));
	}
}

int main()
{
	std::vector<std::thread> threadList;

	auto startTime = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < NUM_THREADS; i++)
	{
		threadList.push_back(std::thread(sleepThread, i));
	}

	for (int i = 0; i < NUM_THREADS; i++)
	{
		threadList[i].join();
	}

	auto stopTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - startTime);

	std::cout << "Execution time: " << (duration.count() / 1000.0) << " [s]\n";
	return EXIT_SUCCESS;
}