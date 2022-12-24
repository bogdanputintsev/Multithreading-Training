#pragma once

#include "FileManager.h"

class ParallelFileManager : public FileManager
{
public:
	virtual ~ParallelFileManager() override = default;
protected:
	virtual void copyAllPaths(const fs::path& sourceDir, const fs::path& targetDir) override;
};

