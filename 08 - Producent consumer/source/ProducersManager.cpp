#include "ProducersManager.h"

#include <random>

ProducersManager::ProducersManager(const std::shared_ptr<MessageQueue>& queue)
	: queue(queue)
{
}

void ProducersManager::run()
{
    std::thread producerOne(&ProducersManager::startProducing, this, "Producer 1");
    std::thread producerTwo(&ProducersManager::startProducing, this, "Producer 2");

    producerOne.join();
    producerTwo.join();
}

void ProducersManager::startProducing(std::string&& threadId) const
{
    while (queue->getNumberOfPushedMessages() < NUMBER_OF_MESSAGES_TO_PRODUCE)
	{
        const std::string newRandomMessage { generateRandomMessage() };
		queue->push(newRandomMessage);
        printf("[%s]: New message \"%s\" has been pushed.\n", threadId.c_str(), newRandomMessage.c_str());
        printf("%s\n", queue->toString().c_str());
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_FOR_MILLISECONDS));
	}
}

std::string ProducersManager::generateRandomMessage()
{
    const std::string charset = R"(abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+)";
    std::string randomString;

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution distribution(0, static_cast<int>(charset.length()) - 1);

    for (int i = 0; i < LENGTH_OF_GENERATED_STRING; ++i) 
    {
        randomString += charset[distribution(generator)];
    }

    return randomString;
}
