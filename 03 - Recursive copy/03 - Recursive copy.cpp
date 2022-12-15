#include <iostream>
#include "FileManager.h"

namespace
{
	const std::string SOURCE_DIR = R"(.\assets\FolderFrom\)";
	const std::string TARGET_DIR = R"(.\assets\FolderTo\)";
}

int main()
{
	FileManager::removeDir(SOURCE_DIR);
	FileManager::removeDir(TARGET_DIR);
	FileManager::generateTree(SOURCE_DIR);

	auto start = std::chrono::high_resolution_clock::now();

	FileManager fileManager;
	fileManager.run(SOURCE_DIR, TARGET_DIR);

	auto end = std::chrono::high_resolution_clock::now();

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