#include "Data.h"

Data::Data(std::string message)
	:
	message(std::move(message))
{
}

Data* Data::getNext() const
{
	return next;
}

void Data::setNext(Data* data)
{
	if (data == nullptr)
		return;

	next = data;
}

const std::string& Data::getMessage() const
{
	return message;
}

void Data::setMessage(const std::string& newMessage)
{
	message = newMessage;
}

std::unique_lock<std::mutex> Data::getUniqueLock()
{
	return std::unique_lock(dataMutex);
}

void Data::lock()
{
	dataMutex.lock();
}

void Data::unlock()
{
	dataMutex.unlock();
}

bool operator>(const Data& data1, const Data& data2)
{
	return data1.getMessage() > data2.getMessage();
}
