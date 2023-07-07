#include "ThreadManager.h"

#include <random>
#include <iostream>

ThreadManager::ThreadManager(const std::shared_ptr<MessageQueue>& queue)
	: queue(queue)
{
}

void ThreadManager::run()
{
    std::thread producerOne(&ThreadManager::startProducing, this, "Producer 1");
    std::thread producerTwo(&ThreadManager::startProducing, this, "Producer 2");
    std::thread consumerOne(&ThreadManager::startConsuming, this, "Consumer 1");
    std::thread consumerTwo(&ThreadManager::startConsuming, this, "Consumer 2");

    producerOne.join();
    producerTwo.join();
    consumerOne.join();
    consumerTwo.join();
}

void ThreadManager::startConsuming(std::string&& threadId) const
{
    while (!queue->isFinished())
    {
        auto pop = queue->pop();
        std::string poppedMessage = pop.has_value() ? pop.value() : "[empty]";
        printf("[%s]: New message \"%s\" has been popped.\n", threadId.c_str(), poppedMessage.c_str());
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_FOR_MILLISECONDS));
    }
}

void ThreadManager::startProducing(std::string&& threadId) const
{
    while (!queue->isFinished())
    {
        const std::string newRandomMessage{ generateRandomMessage() };
        queue->push(newRandomMessage);
        printf("[%s]: New message \"%s\" has been pushed.\n", threadId.c_str(), newRandomMessage.c_str());
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_FOR_MILLISECONDS));
    }
}

std::string ThreadManager::generateRandomMessage()
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


