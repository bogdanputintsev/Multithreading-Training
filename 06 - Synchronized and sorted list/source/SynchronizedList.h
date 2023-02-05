#pragma once

#include <list>
#include <sstream>
#include <thread>

#include "BubbleSort.h"
#include "Subject.h"

class SynchronizedList final : public Subject
{
public:
	SynchronizedList() = default;
	SynchronizedList(const SynchronizedList&) = delete;
	SynchronizedList(SynchronizedList&&) = delete;
	SynchronizedList& operator=(const SynchronizedList&) = delete;
	SynchronizedList& operator=(SynchronizedList&&) = delete;

	~SynchronizedList() override;
	void pushBack(const std::string& line);

	virtual void attach(Observer* observer) override;
	virtual void detach(Observer* observer) override;
	virtual void notify() override;

	[[nodiscard]] Data* getFront() const;
	[[nodiscard]] Data* getEnd() const;
	[[nodiscard]] std::string toString() const;
private:
	friend std::ostream& operator <<(std::ostream& os, const SynchronizedList& synchronizedList);

	Data* front = nullptr;
	Data* end = nullptr;

	std::list<Observer*> observers;
	std::mutex writeMutex;
};

