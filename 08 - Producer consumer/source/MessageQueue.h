#pragma once
#include <mutex>
#include <optional>

#include "Node.h"

class MessageQueue final
{
public:
	MessageQueue();
	~MessageQueue() = default;
	MessageQueue(const MessageQueue& messageQueue) = delete;
	MessageQueue(MessageQueue&& messageQueue) = delete;
	MessageQueue& operator= (const MessageQueue& messageQueue) = delete;
	MessageQueue& operator= (MessageQueue&& messageQueue) = delete;

	void push(std::string message);
	std::optional<std::string> pop();
	bool isFinished() const;
	std::string toString() const;
private:
	int size() const;
	bool empty() const;
	std::optional<std::string> getPoppedMessage() const;
	void removeFirstNode();
	void incrementNumberOfTransactions();
	void drop();

	const std::shared_ptr<Node> sentinelNode;
	std::shared_ptr<Node> lastNode;

	mutable std::mutex sentinelMutex;
	mutable std::mutex writeMutex;
	std::condition_variable queueConditionVariable;

	int queueSize = 0;
	int numberOfTransactions = 0;
	std::atomic<bool> finishFlag = false;

	static constexpr int MAX_NUMBER_OF_TRANSACTIONS = 20;
	static constexpr int BUFFER_SIZE = 10;
};
