#include "Data.h"

Data::Data(std::string _message)
	:
	message(std::move(_message)),
	mutex(new std::mutex)
{
}

Data::Data(std::string _message, Data* _prev)
	:
	message(std::move(_message)),
	mutex(new std::mutex),
	prev(_prev)
{
	if (_prev != nullptr)
	{
		_prev->setNext(this);
	}
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

std::string Data::getMessage() const
{
	return message;
}

void Data::setMessage(const std::string& newMessage)
{
	message = newMessage;
}

void Data::lock()
{
	mutex->lock();
}

void Data::unlock()
{
	mutex->unlock();
}

bool operator>(const Data& data1, const Data& data2)
{
	return data1.getMessage() > data2.getMessage();
}

void swapData(Data& first, Data& second)
{
	first.lock();
	second.lock();

	std::string tmp = first.getMessage();
	first.setMessage(second.getMessage());
	second.setMessage(tmp);

	first.unlock();
	second.unlock();
}
