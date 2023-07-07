#include "RandomMessagesThreadHandler.h"

#include <random>
#include <iostream>

RandomMessagesThreadHandler::RandomMessagesThreadHandler(const std::shared_ptr<MessageQueue>& queue)
	: ThreadHandler(queue)
{
}

void RandomMessagesThreadHandler::run()
{
    std::thread producerOne(&RandomMessagesThreadHandler::startProducing, this, "Producer 1");
    std::thread producerTwo(&RandomMessagesThreadHandler::startProducing, this, "Producer 2");
    std::thread consumerOne(&RandomMessagesThreadHandler::startConsuming, this, "Consumer 1");
    std::thread consumerTwo(&RandomMessagesThreadHandler::startConsuming, this, "Consumer 2");

    producerOne.join();
    producerTwo.join();
    consumerOne.join();
    consumerTwo.join();
}

void RandomMessagesThreadHandler::startConsuming(std::string&& threadId) const
{
    while (!getQueue()->isFinished())
    {
        auto pop = getQueue()->pop();
        std::string poppedMessage = pop.has_value() ? pop.value() : "[empty]";

        printf("[%s]: New message \"%s\" has been popped.\n", threadId.c_str(), poppedMessage.c_str());
        printf("%s\n", getQueue()->toString().c_str());
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_FOR_MILLISECONDS));
    }
}

void RandomMessagesThreadHandler::startProducing(std::string&& threadId) const
{
    while (!getQueue()->isFinished())
    {
        const std::string newRandomMessage{ generateRandomMessage() };
        getQueue()->push(newRandomMessage);

        printf("[%s]: New message \"%s\" has been pushed.\n", threadId.c_str(), newRandomMessage.c_str());
        printf("%s\n", getQueue()->toString().c_str());
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_FOR_MILLISECONDS));
    }
}

std::string RandomMessagesThreadHandler::generateRandomMessage()
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


