#pragma once
#include <mutex>

class Data
{
public:
	explicit Data(std::string message);
	[[nodiscard]] Data* getNext() const;
	void setNext(Data* data);
	[[nodiscard]] const std::string& getMessage() const;
	void setMessage(const std::string& newMessage);
	void lock() const;
	void unlock() const;
private:
	Data* next = nullptr;
	std::string message;
	std::shared_ptr<std::mutex> dataMutex;
};

bool operator> (const Data& data1, const Data& data2);