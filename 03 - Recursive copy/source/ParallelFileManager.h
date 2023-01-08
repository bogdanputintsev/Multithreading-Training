#pragma once

#include "FileManager.h"

class ParallelFileManager final: public FileManager
{
public:
	ParallelFileManager() = default;
	virtual ~ParallelFileManager() override = default;
	ParallelFileManager(const ParallelFileManager&) = default;
	ParallelFileManager(ParallelFileManager&&) noexcept = default;
	ParallelFileManager& operator=(const ParallelFileManager&) = default;
	ParallelFileManager& operator=(ParallelFileManager&&) noexcept = default;
protected:
	virtual void copyAllPaths(const fs::path& sourceDir, const fs::path& targetDir) override;
private:
	std::vector<std::future<void>> futureThreads;
};

