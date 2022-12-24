#include "ParallelFileManager.h"

void ParallelFileManager::copyAllPaths(const fs::path& sourceDir, const fs::path& targetDir)
{
	for (const auto& path : pathsToCopy)
	{
		const fs::path copyFrom = path;
		const fs::path copyTo = getTargetPathFromSourcePath(sourceDir, targetDir, path);

		futureThreads.emplace_back(std::async(std::launch::async, &FileManager::copyFile, copyFrom, copyTo));
	}

	for (auto& future : futureThreads)
	{
		future.get();
	}
}