#include "ParallelFileManager.h"

void ParallelFileManager::copyAllPaths(const fs::path& sourceDirectory, const fs::path& targetDirectory)
{
	const std::vector<fs::path> paths = getAllPathsToCopy();
	for (const auto& path : paths)
	{
		const fs::path& copyFrom = path;
		const fs::path copyTo = getTargetPathFromSourcePath(sourceDirectory, targetDirectory, path);

		futureThreads.emplace_back(std::async(std::launch::async, &FileManager::copyFile, copyFrom, copyTo));
	}

	for (auto& future : futureThreads)
	{
		future.get();
	}
}
