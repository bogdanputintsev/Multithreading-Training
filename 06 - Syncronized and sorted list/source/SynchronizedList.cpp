#include "SynchronizedList.h"

#include <iostream>

SynchronizedList::~SynchronizedList()
{
	if (sortThread.joinable())
	{
		sortThread.join();
	}
	
	const Data* data = front;
	while (data != nullptr)
	{
		const Data* next = data->getNext();
		delete data;
		if (next == nullptr)
		{
			break;
		}

		data = next;
	}
}

/*
 * Method that starts the sort thread.
 * Has to be called at the beginning of the list instance.
 */
void SynchronizedList::runAutoSorting()
{
	sortThread = std::thread(&SynchronizedList::sort, this);
}

/*
 * This method is called by the sort thread.
 */
void SynchronizedList::sort()
{
	const auto sortAlgorithm = BubbleSort();
	while (!isFinished)
	{
		sortSemaphore.acquire();
		if (isFinished)
		{
			break;
		}

		sortAlgorithm.sort(front, end);
		printf("The list has been sorted\n");
		std::this_thread::sleep_for(std::chrono::seconds(SORT_WAIT_FOR_SECS));
	}
}

/*
 * Marks the list as finished and releases the sort semaphore to be finished.
 * This method is called after all the input threads have been finished.
 */
void SynchronizedList::exit()
{
	isFinished = true;
	sortSemaphore.release();
}

/*
 * Pushes a new element to the end of the list.
 */
void SynchronizedList::pushBack(const std::string& line)
{
	std::lock_guard lock(writeMutex);
	if (front == nullptr)
	{
		front = new Data(line);
		end = front;
		return;
	}

	const auto newData = new Data(line);
	end->lock();
	end->setNext(newData);

	const Data* tmp = end;
	end = newData;
	tmp->unlock();
	sortSemaphore.release();
}

std::ostream& operator<<(std::ostream& os, const SynchronizedList& synchronizedList)
{
	return os << synchronizedList.toString();
}

/*
 * This method will return a string representation of the list in JSON format.
 * The class function DOES NOT guarantee that the list will not be modified while the method is running.
 */
std::string SynchronizedList::toString() const
{
	std::string result = "\"synchronizedList\": [\n";

	const Data* data = front;
	while (data != nullptr)
	{
		data->lock();
		const Data* tmp = data;

		result += "\t\"" + (data->getMessage()) + "\",\n";
		if (data->getNext() == nullptr)
		{
			tmp->unlock();
			break;
		}

		data = data->getNext();
		tmp->unlock();
	}
	
	result += "]\n";

	return result;
}