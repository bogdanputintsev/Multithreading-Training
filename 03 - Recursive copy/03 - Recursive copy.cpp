#include <iostream>
#include "FileManager.h"
#include "ParallelFileManager.h"

namespace
{
	const std::string SOURCE_DIRECTORY = R"(.\assets\FolderFrom\)";
	const std::string TARGET_DIRECTORY = R"(.\assets\FolderTo\)";
}

int main()
{
	srand(static_cast<unsigned>(time(nullptr)));  // NOLINT(cert-msc51-cpp)

	FileManager::removeDirectory(SOURCE_DIRECTORY);
	FileManager::removeDirectory(TARGET_DIRECTORY);
	FileManager::generateTree(SOURCE_DIRECTORY);

	const auto start = std::chrono::high_resolution_clock::now();

	auto fileManager = ParallelFileManager();
	fileManager.run(SOURCE_DIRECTORY, TARGET_DIRECTORY);

	const auto end = std::chrono::high_resolution_clock::now();

	if (FileManager::compareTrees(SOURCE_DIRECTORY, TARGET_DIRECTORY))
	{
		std::cout << "Copy test passed.\n";
	}
	else
	{
		std::cout << "Copy test failed.\n";
	}

	const double elapsedTimeMs = std::chrono::duration<double, std::milli>(end - start).count();
	std::cout << "Estimated time: " << elapsedTimeMs << "ms.\n";

	return EXIT_SUCCESS;
}