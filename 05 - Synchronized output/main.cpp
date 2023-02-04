#include <thread>
#include <mutex>

class SynchronizedOutput final
{
public:
	void run()
	{
		std::thread thread(&SynchronizedOutput::printLines, this, CHILD_IDX, ThreadType::CHILD);
		printLines(PARENT_IDX, ThreadType::PARENT);
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
		for (int i = idx; i < idx + LINES_PER_THREAD * NUM_THREADS; i += NUM_THREADS)
		{
			std::unique_lock<std::mutex> lock{ printMutex };
			sleepCondition.wait(lock, [=]() { return threadType != lastActiveThread; });

			printLine(i, threadType);

			lastActiveThread = threadType;
			sleepCondition.notify_all();
		}
	}

	static void printLine(const int idx, const ThreadType threadType)
	{
		const std::string threadName = threadType == ThreadType::PARENT ? "[PARENT]" : "[CHILD] ";
		printf("%s %d\n", threadName.c_str(), idx);
		std::this_thread::sleep_for(SLEEP_DURATION_MS);
	}
	
	static constexpr std::chrono::milliseconds SLEEP_DURATION_MS = std::chrono::milliseconds(50);
	static constexpr int LINES_PER_THREAD = 30;
	static constexpr int NUM_THREADS = 2;
	static constexpr int PARENT_IDX = 0;
	static constexpr int CHILD_IDX = 1;

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