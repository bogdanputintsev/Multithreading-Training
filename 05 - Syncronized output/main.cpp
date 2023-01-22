#include <thread>
#include <mutex>

class SynchronizedOutput final
{
public:
	void run()
	{
		std::thread thread(&SynchronizedOutput::printLines, this, 1, ThreadType::CHILD);
		printLines(0, ThreadType::PARENT);
		thread.join();
	}

private:
	enum class ThreadType
	{
		PARENT,
		CHILD
	};

	void printLines(const int idx, const ThreadType threadType)
	{
		for (int i = idx; i < idx + LINES_PER_THREAD * 2; i += 2)
		{
			std::unique_lock<std::mutex> lock{ printMutex };
			sleepCondition.wait(lock, [=]() { return threadType != lastActiveThread; });

			printLine(i);

			lastActiveThread = threadType;
			sleepCondition.notify_one();
		}
	}

	static void printLine(const int idx)
	{
		printf("[%d]\n", idx);
		std::this_thread::sleep_for(SLEEP_DURATION_MS);
	}
	
	static constexpr std::chrono::milliseconds SLEEP_DURATION_MS = std::chrono::milliseconds(50);
	static constexpr int LINES_PER_THREAD = 30;

	std::condition_variable sleepCondition;
	std::mutex printMutex;

	ThreadType lastActiveThread = ThreadType::CHILD;
};

int main()
{
	SynchronizedOutput synchronizedOutput;
	synchronizedOutput.run();

	return EXIT_SUCCESS;
}