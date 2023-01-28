#include <string>
#include <thread>
#include <vector>
#include <chrono>
#include <cassert>

namespace input
{
    constexpr int LINE_COUNT = 7;
    constexpr int MAX_STRING_LENGTH = 15;

    std::string generateRandomString(const int length)
    {
        assert(length > 0);
        static constexpr char ALPHANUM[] =
            "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

        std::string result;
        result.reserve(length);

        for (int i = 0; i < length; i++)
        {
            result += ALPHANUM[rand() % (sizeof(ALPHANUM) - 1)];
        }

        return result;
    }

    std::vector<std::string> generateInput()
    {
        std::vector<std::string> input;
        input.reserve(LINE_COUNT);

        for (int i = 0; i < LINE_COUNT; i++)
        {
	        const int stringLength = rand() % MAX_STRING_LENGTH + 1;
            input.push_back(generateRandomString(stringLength));
        }

        return input;
    }
}

namespace sleepsort
{
    void sleepPrint(const std::string& line)
    {
        assert(!line.empty());

        const size_t length = line.size();
        assert(length > 0);

        std::this_thread::sleep_for(std::chrono::seconds(length));

        printf("\t%s\n", line.c_str());
    }

    void printLinesBeforeSorting(const std::vector<std::string>& lines)
    {
        printf("List before the Sleepsort:\n");
        for (const std::string& line : lines)
        {
            printf("\t%s \n", line.c_str());
        }
    }

    void run(const std::vector<std::string>& lines)
    {
        assert(!lines.empty());
        printLinesBeforeSorting(lines);

        printf("Sorted result:\n");
        std::vector<std::thread> threads;
        threads.reserve(lines.size());

        for (const std::string& line : lines)
        {
            threads.emplace_back(sleepsort::sleepPrint, std::ref(line));
        }

        for (std::thread& th : threads)
        {
            if (th.joinable())
            {
                th.join();
            }
        }
    }
}

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    const std::vector<std::string> lines = input::generateInput();
    sleepsort::run(lines);

	return EXIT_SUCCESS;
}