#include <thread>
#include <mutex>

class SyncronizedOutput
{
public:
	void run()
	{
		std::thread thread(&SyncronizedOutput::printLines, this, 1, ThreadType::CHILD);
		printLines(0, ThreadType::PARENT);
		thread.join();
	}

protected:
	enum ThreadType
	{
		PARENT,
		CHILD
	};

	void printLines(const int idx, const ThreadType threadType)
	{
		for (int i = idx; i < idx + LINES_PER_THREAD * 2; i += 2)
		{
			std::unique_lock<std::mutex> lock{ m };
			sleepCondition.wait(lock, [=]() { return threadType != lastActiveThread; });

			printLine(i);

			lastActiveThread = threadType;
			sleepCondition.notify_one();
		}
	}

	void printLine(const int idx) const
	{
		printf("[%d]\n", idx);
		std::this_thread::sleep_for(SLEEP_DURATION_MS);
	}

private:
	static constexpr std::chrono::milliseconds SLEEP_DURATION_MS = std::chrono::milliseconds(50);
	static constexpr int LINES_PER_THREAD = 30;

	std::condition_variable sleepCondition;
	std::mutex m;

	ThreadType lastActiveThread = ThreadType::CHILD;
};

int main()
{
	SyncronizedOutput syncronizedOutput;
	syncronizedOutput.run();

	return EXIT_SUCCESS;
}