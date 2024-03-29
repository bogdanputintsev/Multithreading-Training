#include "MessageQueue.h"

#include <cassert>

MessageQueue::MessageQueue()
	: sentinelNode(std::make_shared<Node>(Node{ "Sentinel" }))
	, lastNode(sentinelNode)
{
}

void MessageQueue::push(std::string message)
{
	{
		std::unique_lock sentinelLock(sentinelMutex);
		std::unique_lock writeLock(writeMutex);
		if (sentinelNode->getNext() != lastNode)
		{
			sentinelLock.unlock();
		}

		queueConditionVariable.wait(writeLock, [&]
			{
				return size() < BUFFER_SIZE || finishFlag;
			});

		if (finishFlag)
		{
			queueConditionVariable.notify_all();
			return;
		}

		lastNode->setNext(std::make_shared<Node>(Node{ std::move(message) }));
		lastNode = lastNode->getNext();
		++queueSize;
		incrementNumberOfTransactions();
	}

	queueConditionVariable.notify_all();
}

std::optional<std::string> MessageQueue::pop()
{
	std::optional<std::string> poppedMessage = std::nullopt;

	{
		std::unique_lock sentinelLock(sentinelMutex);
		std::unique_lock writeLock(writeMutex);
		if (sentinelNode->getNext() != lastNode)
		{
			writeLock.unlock();
		}

		queueConditionVariable.wait(sentinelLock, [&]
			{
				return !empty() || finishFlag;
			});

		if (finishFlag)
		{
			queueConditionVariable.notify_all();
			return std::nullopt;
		}

		poppedMessage = getPoppedMessage();
		removeFirstNode();
		--queueSize;
		incrementNumberOfTransactions();
	}

	queueConditionVariable.notify_all();
	return poppedMessage;
}

std::optional<std::string> MessageQueue::getPoppedMessage() const
{
	return (sentinelNode->getNext())
		? std::optional(sentinelNode->getNext()->getMessage())
		: std::nullopt;
}

void MessageQueue::removeFirstNode()
{
	const auto nodeToRemove{ sentinelNode->getNext() };
	assert(nodeToRemove);

	if (!nodeToRemove->getNext().get())
	{
		sentinelNode->setNext(nullptr);
		lastNode = sentinelNode;
	}
	else
	{
		sentinelNode->setNext(nodeToRemove->getNext());
	}
}

void MessageQueue::incrementNumberOfTransactions()
{
	++numberOfTransactions;
	if (numberOfTransactions == MAX_NUMBER_OF_TRANSACTIONS)
	{
		drop();
	}
}

void MessageQueue::drop()
{
	finishFlag = true;
}

int MessageQueue::size() const
{
	assert(queueSize >= 0);
	return queueSize;
}

bool MessageQueue::empty() const
{
	assert(queueSize == 0 || sentinelNode->getNext());
	return queueSize == 0;
}

bool MessageQueue::isFinished() const
{
	return finishFlag;
}

std::string MessageQueue::toString() const
{
	std::string result = "Queue: [ ";
	{
		std::unique_lock sentinelLock(sentinelMutex);

		const Node* currentNode = sentinelNode->getNext().get();
		while (currentNode)
		{
			result += currentNode->getMessage() + " ";
			currentNode = currentNode->getNext().get();
		}
	}
	result += "]";
	return result;
}
