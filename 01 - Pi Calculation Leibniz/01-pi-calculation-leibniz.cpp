#include <cstdlib>
#include <future>
#include <vector>
#include <cassert>
#include <ctime>

namespace
{
	constexpr int NUM_STEPS = 999999999;
	constexpr int NUM_THREADS = 11;

	double calculateLeibnizPi(const int start, const int end)
	{
		assert(start >= 0);
		assert(end > start);
		assert(end <= NUM_STEPS);

		double result = 0;
		for (int i = start; i < end; i++)
		{
			result += 1.0 / (i * 4.0 + 1.0);
			result -= 1.0 / (i * 4.0 + 3.0);
		}

		return result;
	}
}


int main()
{
	const clock_t beginTime = clock();

	double pi = 0.0;
	std::vector<std::future<double>> futureContainer;

	for (int i = 0; i < NUM_THREADS; i++)
	{
		auto f = std::async(std::launch::async, calculateLeibnizPi,
			i * (NUM_STEPS / NUM_THREADS),
			(i + 1) * (NUM_STEPS / NUM_THREADS));
		futureContainer.push_back(std::move(f));
	}

	for (auto& i : futureContainer)
	{
		pi += i.get();
	}

	pi *= 4.0;
	printf("PI calculation done - %.15g \n", pi);

	const double timeElapsed{ static_cast<double>(clock() - beginTime) / CLOCKS_PER_SEC };
	printf("Execution time: %.3f\n", timeElapsed);

	return EXIT_SUCCESS;
}

