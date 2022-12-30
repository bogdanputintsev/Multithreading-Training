#include "SyncronizedList.h"

SyncronizedList::SyncronizedList()
{
	sortThread = std::thread(&SyncronizedList::sort, this);
}

SyncronizedList::~SyncronizedList()
{
	Data* data = front;
	while (data != nullptr)
	{
		Data* next = data->getNext();
		delete data;
		if (next == nullptr)
		{
			break;
		}

		data = next;
	}
	sortThread.join();

}

void SyncronizedList::sort()
{
	std::unique_ptr<SortAlgorithm> sortAlgorithm = std::make_unique<BubbleSort>();

	while (!isFinished)
	{
		sortSemaphore.acquire();
		if (isFinished)
		{
			break;
		}
		sortAlgorithm->sort(front, end);
		std::cout << "The list has been sorted. \n";
	}
}

void SyncronizedList::exit()
{
	isFinished = true;
	sortSemaphore.release();
}

void SyncronizedList::emplaceBack(const std::string& line)
{
	if (front == nullptr)
	{
		front = new Data(line);
		end = front;
		return;
	}

	end->lock();
	Data* newData = new Data(line, end);
	end->unlock();

	end = newData;
	sortSemaphore.release();
}

std::string SyncronizedList::toString() const
{
	std::string result = "\"syncronizedList\": [\n";

	Data* data = front;
	while (data != nullptr)
	{
		result += "\t\"" + (data->getMessage()) + "\",\n";
		if (data->getNext() == nullptr)
		{
			break;
		}

		data = data->getNext();
	}
	
	result += "]\n";

	return result;
}

std::ostream& operator<<(std::ostream& os, const SyncronizedList& syncronizedList)
{
	return os << syncronizedList.toString();
}
