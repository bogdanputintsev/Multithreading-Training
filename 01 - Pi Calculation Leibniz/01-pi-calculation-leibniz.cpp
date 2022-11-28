#include <cstdlib>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

#define NUM_STEPS 10000

void calculateLeibnizPi(int start, int end, double& pi)
{
	double result = 0;
	for (int i = start; i < end; i++)
	{
		result += 1.0 / (i * 4.0 + 1.0);
		result -= 1.0 / (i * 4.0 + 3.0);
	}

	mutex m;
	m.lock();
	pi += result;
	m.unlock();
}

int main(int argc, char** argv)
{
	const int NUM_THREADS = 2;

	double pi = 0.0;
	vector<thread> threadContainer;

	for (int i = 0; i < NUM_THREADS; i++)
	{
		thread t(calculateLeibnizPi, i * (NUM_STEPS / NUM_THREADS),
			(i + 1) * (NUM_STEPS / NUM_THREADS),
			ref(pi));
		threadContainer.push_back(move(t));
	}


	for (thread& th : threadContainer)
		if (th.joinable())
			th.join();

	pi *= 4.0;
	printf("Pi done - %.40g \n", pi);

	return 0;
}

