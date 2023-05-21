#include "SynchronizedList.h"

#include <algorithm>
#include <cassert>
#include <iostream>

SynchronizedList::SynchronizedList()
	:
	sentinel(std::make_shared<Data>("Sentinel"))
{
}

SynchronizedList::~SynchronizedList()
{
	std::unique_lock sentinelLock(sentinel->getUniqueLock());
	const Data* data = sentinel->getNext();
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
 * Pushes a new element to the end of the list.
 */
void SynchronizedList::pushBack(const std::string& line)
{
	{
		const auto newData = new Data(line);
		std::unique_lock sentinelLock(sentinel->getUniqueLock());

		if (sentinel->getNext())
		{
			std::unique_lock frontLock(sentinel->getNext()->getUniqueLock());
			const auto dataToAssignNext = sentinel->getNext();
			sentinel->setNext(newData);
			newData->setNext(dataToAssignNext);
		}
		else
		{
			sentinel->setNext(newData);
		}
	}

	// Notify all the sorter observers that the list has been modified.
	notify();
}

/*
 * This method will attach a new observer (sorter) to the list.
 * This observer will be notified when the list is modified.
 */
void SynchronizedList::attach(Observer* observer)
{
	std::lock_guard lock(observersMutex);
	observers.push_back(observer);
}

/*
 * After detaching an observer, it will no longer be notified when the list is modified.
 */
void SynchronizedList::detach(Observer* observer)
{
	std::lock_guard lock(observersMutex);
	observers.remove(observer);
}

/*
 * This method will notify all observers that the list has been modified.
 */
void SynchronizedList::notify()
{
	std::lock_guard lock(observersMutex);
	std::ranges::for_each(observers, [](Observer* observer) { observer->update(); });
}

Data* SynchronizedList::getFront() const
{
	std::unique_lock sentinelLock(sentinel->getUniqueLock());
	std::unique_lock frontLock(sentinel->getNext()->getUniqueLock());
	Data* returnData = sentinel->getNext();
	return returnData;
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
	sentinel->lock();

	// Empty list
	if (sentinel->getNext() == nullptr)
	{
		sentinel->unlock();
		return "\"synchronizedList\": []";
	}

	sentinel->getNext()->lock(); // lock current (front) point

	const Data* current = sentinel->getNext();

	// Only one message
	if (current->getNext() == nullptr)
	{
		const std::string frontMessage = current->getMessage();
		sentinel->getNext()->unlock();
		sentinel->unlock();
		return "\"synchronizedList\": [\n\t\"" + frontMessage + "\"\n]\n";
	}

	// At least two messages
	current->getNext()->lock();	// lock next point
	Data* previous = sentinel.get();
	const Data* next = current->getNext();

	std::string result = "\"synchronizedList\": [";

	while (current != nullptr)
	{
		result += "\n\t\""
			+ (current->getMessage()) + "\""
			+ (next->getNext() ? "," : "");

		if(next->getNext() != nullptr)
		{
			next->getNext()->lock();
			next = next->getNext();
		}

		current = current->getNext();
		Data* dataToUnlock = previous;
		previous = previous->getNext();
		dataToUnlock->unlock();
	}

	previous->unlock();

	result += "\n]\n";

	return result;
}