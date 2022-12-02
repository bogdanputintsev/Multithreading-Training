#pragma once

#include <string>
#include <iostream>
#include <filesystem>
#include <thread>

namespace fs = std::filesystem;

class CopyManager
{
public:
	static bool copyDir(const fs::path& sourceDir, const fs::path& targetDir);
private:
	static void loopDir(const fs::path& sourceDir, const fs::path& targetDir, const fs::directory_entry& item);
	static void copyFile(const fs::path& item, const fs::path& targetDir);

	std::vector<std::thread> activeThreads;
};

