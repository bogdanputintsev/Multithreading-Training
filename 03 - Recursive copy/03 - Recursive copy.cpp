#include <iostream>
#include "FileManager.h"
#include "ParallelFileManager.h"

namespace
{
	const std::string SOURCE_DIR = R"(.\assets\FolderFrom\)";
	const std::string TARGET_DIR = R"(.\assets\FolderTo\)";
}

int main()
{
	srand(static_cast<unsigned>(time(nullptr)));  // NOLINT(cert-msc51-cpp)

	FileManager::removeDir(SOURCE_DIR);
	FileManager::removeDir(TARGET_DIR);
	FileManager::generateTree(SOURCE_DIR);

	const auto start = std::chrono::high_resolution_clock::now();

	auto fileManager = ParallelFileManager();
	fileManager.run(SOURCE_DIR, TARGET_DIR);

	const auto end = std::chrono::high_resolution_clock::now();

	if (FileManager::compareTrees(SOURCE_DIR, TARGET_DIR))
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