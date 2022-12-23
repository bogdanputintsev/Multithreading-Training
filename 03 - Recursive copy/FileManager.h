#pragma once

#include <filesystem>
#include <fstream>
#include <algorithm>
#include <cassert>
#include <future>

namespace fs = std::filesystem;

class FileManager
{
public:
	FileManager();
	virtual ~FileManager() = default;
	
	void run(const fs::path& sourceDir, const fs::path& targetDir);
	
	static void generateTree(const fs::path& path);
	static bool compareTrees(const fs::path& sourceDir, const fs::path& targetDir);
	static void removeDir(const fs::path& sourceDir);
protected:
	void collectAllPathsToCopy(const fs::path& sourceDir);
	virtual void copyAllPaths(const fs::path& sourceDir, const fs::path& targetDir);
	static void copyFile(const fs::path& item, const fs::path& targetDir);
	static void spawn(const fs::path& currentPath, const int depth = 0);
	static std::string getRandomName(const int length);
	static void createFolder(const fs::path& folderPath, const std::string& newFolderName);
	static void createFile(const fs::path& folderPath, const std::string& newFileName);
	static int randomIntInRange(const int from, const int to);

	std::vector<std::future<void>> futureThreads;
	std::vector<fs::path> pathsToCopy;

	static fs::path getTargetPathFromSourcePath(const fs::path& sourceDir, const fs::path& targetDir, const fs::path& path);
	static std::string getRelativePath(const std::string& absolutePath, const std::string& pathToRemove);

	constexpr static int MAX_DEPTH = 7;
	constexpr static int MAX_NUM_FOLDERS = 8;
	constexpr static int MAX_NUM_FILES = 8;
	constexpr static int MAX_STRING_LENGTH = 15;
};

