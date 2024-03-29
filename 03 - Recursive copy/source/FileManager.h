#pragma once

#include <filesystem>
#include <future>

namespace fs = std::filesystem;

class FileManager
{
public:
	FileManager() = default;
	virtual ~FileManager() = default;
	FileManager(const FileManager&) = default;
	FileManager(FileManager&&) noexcept = default;
	FileManager& operator=(const FileManager&) = default;
	FileManager& operator=(FileManager&&) noexcept = default;

	void run(const fs::path& sourceDirectory, const fs::path& targetDirectory);
	
	static void generateTree(const fs::path& path);
	static bool compareTrees(const fs::path& sourceDirectory, const fs::path& targetDirectory);
	static void removeDirectory(const fs::path& sourceDirectory);
protected:
	void collectAllPathsToCopy(const fs::path& sourceDirectory);
	virtual void copyAllPaths(const fs::path& sourceDirectory, const fs::path& targetDirectory);
	static void copyFile(const fs::path& item, const fs::path& targetDirectory);
	static void spawn(const fs::path& currentPath, const int depth = 0);
	static std::string getRandomName(const int length);
	static void createFolder(const fs::path& folderPath, const std::string& newFolderName);
	static void createFile(const fs::path& folderPath, const std::string& newFileName);
	static int randomIntInRange(const int from, const int to);
	
	static fs::path getTargetPathFromSourcePath(const fs::path& sourceDirectory, const fs::path& targetDirectory, const fs::path& path);
	static std::string getRelativePath(const std::string& absolutePath, const std::string& pathToRemove);

	[[nodiscard]] std::vector<fs::path> getAllPathsToCopy() const;
private:
	std::vector<fs::path> pathsToCopy;

	constexpr static int MAX_DEPTH = 4;
	constexpr static int MAX_NUM_FOLDERS = 4;
	constexpr static int MAX_NUM_FILES = 8;
	constexpr static int MAX_STRING_LENGTH = 15;
};

