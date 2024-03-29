#include <cstdlib>

#include "RandomMessagesThreadHandler.h"
#include "MessageQueue.h"
#include "ProducersManager.h"


int main()
{
	const auto queue = std::make_shared<MessageQueue>();

	auto threadManager = RandomMessagesThreadHandler{ queue };
	threadManager.run();

	return EXIT_SUCCESS;
}
