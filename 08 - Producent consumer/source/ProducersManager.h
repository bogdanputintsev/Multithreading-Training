#pragma once
#include <memory>

#include "MessageQueue.h"

class ProducersManager
{
public:
	ProducersManager() = delete;
	~ProducersManager() = default;

	explicit ProducersManager(const std::shared_ptr<MessageQueue>& queue);
	void run();
private:
	void startProducing(std::string&& threadId) const;
	static std::string generateRandomMessage();

	std::shared_ptr<MessageQueue> queue{};

	static constexpr int NUMBER_OF_MESSAGES_TO_PRODUCE = 10;
	static constexpr int LENGTH_OF_GENERATED_STRING = 5;
	static constexpr int SLEEP_FOR_MILLISECONDS = 500;
};

