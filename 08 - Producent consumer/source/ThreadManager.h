#pragma once
#include "MessageQueue.h"

class ThreadManager
{
public:
	ThreadManager() = delete;
	~ThreadManager() = default;
	ThreadManager(const ThreadManager&) = delete;
	ThreadManager(ThreadManager&&) = delete;
	ThreadManager& operator=(const ThreadManager&) = delete;
	ThreadManager& operator=(ThreadManager&&) = delete;

	explicit ThreadManager(const std::shared_ptr<MessageQueue>& queue);

	void run();
private:
	void startConsuming(std::string&& threadId) const;
	void startProducing(std::string&& threadId) const;

	static std::string generateRandomMessage();

	std::shared_ptr<MessageQueue> queue{};

	static constexpr int LENGTH_OF_GENERATED_STRING = 5;
	static constexpr int SLEEP_FOR_MILLISECONDS = 500;
};
