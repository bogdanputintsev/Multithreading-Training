#include <cstdlib>

#include "ThreadManager.h"
#include "MessageQueue.h"
#include "ProducersManager.h"


int main()
{
	const auto queue = std::make_shared<MessageQueue>();

	auto threadManager = ThreadManager(queue);
	threadManager.run();

	return EXIT_SUCCESS;
}
