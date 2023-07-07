#pragma once
#include "MessageQueue.h"
#include "ThreadHandler.h"

class RandomMessagesThreadHandler final : public ThreadHandler
{
public:
	RandomMessagesThreadHandler() = delete;
	virtual ~RandomMessagesThreadHandler() override = default;
	RandomMessagesThreadHandler(const RandomMessagesThreadHandler&) = delete;
	RandomMessagesThreadHandler(RandomMessagesThreadHandler&&) = delete;
	RandomMessagesThreadHandler& operator=(const RandomMessagesThreadHandler&) = delete;
	RandomMessagesThreadHandler& operator=(RandomMessagesThreadHandler&&) = delete;

	explicit RandomMessagesThreadHandler(const std::shared_ptr<MessageQueue>& queue);

	virtual void run() override;
private:
	void startConsuming(std::string&& threadId) const;
	void startProducing(std::string&& threadId) const;

	static std::string generateRandomMessage();

	static constexpr int LENGTH_OF_GENERATED_STRING = 5;
	static constexpr int SLEEP_FOR_MILLISECONDS = 500;
};
