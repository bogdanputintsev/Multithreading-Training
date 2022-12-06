#pragma once

#include <string>
#include <iostream>
#include <filesystem>
#include <thread>
#include <future>
#include <mutex>
#include <cassert>

namespace fs = std::filesystem;

class CopyManager
{
public:
	void run(const fs::path& sourceDir, const fs::path& targetDir);
	bool copyDir(const fs::path& sourceDir, const fs::path& targetDir);
private:
	void loopDir(const fs::path sourceDir, const fs::path targetDir);
	void copyFile(const fs::path& item, const fs::path& targetDir);

	std::vector<std::future<void>> futureThreads;
	std::mutex m;
};

