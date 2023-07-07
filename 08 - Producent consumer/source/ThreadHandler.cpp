#include "ThreadHandler.h"

ThreadHandler::ThreadHandler(const std::shared_ptr<MessageQueue>& queue)
	: queue(queue)
{
}

std::shared_ptr<MessageQueue> ThreadHandler::getQueue() const
{
	return queue;
}
