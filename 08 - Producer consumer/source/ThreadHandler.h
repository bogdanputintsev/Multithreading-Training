#pragma once
#include <memory>

#include "MessageQueue.h"

class ThreadHandler
{
public:
	ThreadHandler() = delete;
	virtual ~ThreadHandler() = default;
	ThreadHandler(const ThreadHandler&) = delete;
	ThreadHandler(ThreadHandler&&) = delete;
	ThreadHandler& operator=(const ThreadHandler&) = delete;
	ThreadHandler& operator=(ThreadHandler&&) = delete;

	explicit ThreadHandler(const std::shared_ptr<MessageQueue>& queue);

	virtual void run() = 0;
protected:
	[[nodiscard]] std::shared_ptr<MessageQueue> getQueue() const;

private:
	std::shared_ptr<MessageQueue> queue{};

};

