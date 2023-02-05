#include "SynchronizedList.h"

#include <algorithm>
#include <iostream>

SynchronizedList::~SynchronizedList()
{
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

	const Data* dataToUnlock = end;
	end = newData;
	dataToUnlock->unlock();

	// Notify all the sorter observers that the list has been modified.
	notify();
}

/*
 * This method will attach a new observer (sorter) to the list.
 * This observer will be notified when the list is modified.
 */
void SynchronizedList::attach(Observer* observer)
{
	observers.push_back(observer);
}

/*
 * After detaching an observer, it will no longer be notified when the list is modified.
 */
void SynchronizedList::detach(Observer* observer)
{
	observers.remove(observer);
}

/*
 * This method will notify all observers that the list has been modified.
 */
void SynchronizedList::notify()
{
	std::ranges::for_each(observers, [](Observer* observer) { observer->update(); });
}

Data* SynchronizedList::getFront() const
{
	return front;
}

Data* SynchronizedList::getEnd() const
{
	return end;
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