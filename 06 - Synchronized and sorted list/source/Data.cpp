#include "Data.h"

Data::Data(std::string message)
	:
	message(std::move(message)),
	dataMutex(new std::mutex)
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

void Data::lock() const
{
	dataMutex->lock();
}

void Data::unlock() const
{
	dataMutex->unlock();
}

bool operator>(const Data& data1, const Data& data2)
{
	return data1.getMessage() > data2.getMessage();
}
