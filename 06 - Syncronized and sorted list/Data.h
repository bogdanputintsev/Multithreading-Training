#pragma once
#include <mutex>

class Data
{
public:
	Data(std::string _value);
	Data(std::string _value, Data* prev);
	Data* getNext() const;
	void setNext(Data* data);
	std::string getMessage() const;
	void setMessage(const std::string& newMessage);
	void lock();
	void unlock();
private:
	Data* next = nullptr;
	Data* prev = nullptr;
	std::string message;
	std::shared_ptr<std::mutex> mutex;
};

bool operator> (const Data& data1, const Data& data2);
void swapData(Data& first, Data& second);