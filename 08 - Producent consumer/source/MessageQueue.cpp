#include "MessageQueue.h"

#include <cassert>

MessageQueue::MessageQueue()
	: sentinelNode(std::make_shared<Node>(Node("Sentinel")))
	, lastNode(sentinelNode)
{
}

void MessageQueue::push(const std::string& message)
{
	std::unique_lock pushLock(queueMutex);
	queueConditionVariable.wait(pushLock, [&]
		{
			return size() < BUFFER_SIZE || finishFlag;
		});

	if (finishFlag)
	{
		queueConditionVariable.notify_all();
		return;
	}

	lastNode->setNext(std::make_shared<Node>(Node(message)));
	lastNode = lastNode->getNext();
	++queueSize;
	++numberOfTransactions;
	if (numberOfTransactions == MAX_NUMBER_OF_TRANSACTIONS)
	{
		drop();
	}
	printf("%s\n", toString().c_str());

	pushLock.unlock();

	queueConditionVariable.notify_all();
}

std::optional<std::string> MessageQueue::pop()
{
	std::unique_lock popLock(queueMutex);
	queueConditionVariable.wait(popLock, [&]
		{
			return !empty() || finishFlag;
		});

	if (finishFlag)
	{
		queueConditionVariable.notify_all();
		return std::nullopt;
	}

	auto poppedMessage = getPoppedMessage();
	removeFirstNode();
	--queueSize;
	++numberOfTransactions;
	if (numberOfTransactions == MAX_NUMBER_OF_TRANSACTIONS)
	{
		drop();
	}

	printf("%s\n", toString().c_str());
	popLock.unlock();

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
	const auto nodeToRemove = sentinelNode->getNext();
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

void MessageQueue::drop()
{
	finishFlag = true;
	queueConditionVariable.notify_all();
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
	std::unique_lock statusLock(queueMutex);
	return finishFlag;
}

std::string MessageQueue::toString() const
{
	std::string result = "Queue: [ ";
	//std::unique_lock popLock(queueMutex);
	const Node* currentNode = sentinelNode->getNext().get();
	while (currentNode)
	{
		result += currentNode->getMessage() + " ";
		currentNode = currentNode->getNext().get();
	}
	result += "]";

	return result;
}
