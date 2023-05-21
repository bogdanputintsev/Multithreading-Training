#include "Sorter.h"

#include <cassert>

Sorter::Sorter(SynchronizedList* synchronizedList)
	:
	synchronizedList(synchronizedList)
{
	assert(synchronizedList != nullptr && "Sorter received and invalid pointer on SynchronizedList on constructor. Value is NULL.");
}

/*
 * This method will be called when the SynchronizedList is modified.
 */
void Sorter::update()
{
	newUnsortedDataExistSemaphore.release();
}

/*
 * This method will be called by the sorter thread.
 * It will sort the list every SORT_WAIT_FOR_SECS seconds.
 */
void Sorter::sortLoop()
{
	const auto sortAlgorithm = BubbleSort();
	while (isRunning)
	{
		if (!sort(sortAlgorithm))
		{
			break;
		}
		std::this_thread::sleep_for(std::chrono::seconds(SORT_WAIT_FOR_SECS));
	}
}

/*
 * This method will be called by the sorter thread.
 * It will sort the list using the given sort algorithm.
 */
bool Sorter::sort(const SortAlgorithm& sortAlgorithm)
{
	assert(synchronizedList != nullptr && "Sorter contains invalid pointer on SynchronizedList. Value is NULL.");

	newUnsortedDataExistSemaphore.acquire();
	if (!isRunning)
	{
		return false;
	}

	sortAlgorithm.sort(synchronizedList->getFront());
	printf("The synchronizedList has been sorted\n");
	return true;
}

/*
 * Marks the sorter as finished and releases the sort semaphore to be finished the last time.
 * This method is called after all the input threads have been finished.
 */
void Sorter::stop()
{
	isRunning = false;
	newUnsortedDataExistSemaphore.release();
}
