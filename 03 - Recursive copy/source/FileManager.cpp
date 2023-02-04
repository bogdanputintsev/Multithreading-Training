#include "FileManager.h"

#include <cassert>
#include <fstream>
#include <iostream>

/*
 * This method is used to calculate number of files to copy and to copy them.
 */
void FileManager::run(const fs::path& sourceDirectory, const fs::path& targetDirectory)
{
	std::cout << "Calculating number of items to copy...\n";
	collectAllPathsToCopy(sourceDirectory);

	std::cout << "There are " << pathsToCopy.size() << " items to copy.\n";
	copyAllPaths(sourceDirectory, targetDirectory);
}

/*
 * This method indexes all files to copy in the source directory.
 */
void FileManager::collectAllPathsToCopy(const fs::path& sourceDirectory)
{
	try
	{
		for (const auto& item : fs::recursive_directory_iterator(sourceDirectory))
		{
			pathsToCopy.emplace_back(item.path());
		}
	}
	catch (fs::filesystem_error& error)
	{
		std::cout << error.what() << '\n';
		abort();
	}
}

void FileManager::copyAllPaths(const fs::path& sourceDirectory, const fs::path& targetDirectory)
{
	for (const auto& path : pathsToCopy)
	{
		const fs::path copyFrom = path;
		const fs::path copyTo = getTargetPathFromSourcePath(sourceDirectory, targetDirectory, path);

		copyFile(copyFrom, copyTo);
	}
}

/*
 * Concatenates the target directory with the relative path of the source directory.
 */
fs::path FileManager::getTargetPathFromSourcePath(const fs::path& sourceDirectory, const fs::path& targetDirectory, const fs::path& absolutePath)
{
	return targetDirectory / getRelativePath(absolutePath.string(), sourceDirectory.string());
}

/*
 * Removes the source directory from the absolute path.
 * Example:
 *		Input: absolutePath = "C:\Users\user\Desktop\source\file.txt"
 *		Output: "file.txt"
 * @param absolutePath - absolute path to the file
 * @param pathToRemove - path to remove from the absolute path
 * @return relative path to the file
 */
std::string FileManager::getRelativePath(const std::string& absolutePath, const std::string& pathToRemove)
{
	assert(!pathToRemove.empty());
	const size_t length = pathToRemove.size();
	return absolutePath.substr(length);
}

/*
 * Getter for pathsToCopy.
 */
std::vector<fs::path> FileManager::getAllPathsToCopy() const
{
	return pathsToCopy;
}

void FileManager::copyFile(const fs::path& item, const fs::path& targetDirectory)
{
	try
	{
		if (fs::is_directory(item))
		{
			fs::create_directories(item);
			return;
		}

		fs::create_directories(targetDirectory.parent_path());
		fs::copy_file(item, targetDirectory);
	}
	catch (fs::filesystem_error& e)
	{
		std::cout << e.what() << "\n\n";
	}
}

/*
 * This method will create a pseudo-random tree of folders and files.
 * @param path - path to the root of the tree
 */
void FileManager::generateTree(const fs::path& path)
{
	std::cout << "Spawning recursive tree at " << path.string() << '\n';
	spawn(path, 0);
}

/*
 * Recursive function that creates pseudo-random tree of folders and files.
 * This method is called from generateTree().
 * @param currentPath - path to the current folder
 * @param depth - current depth of the tree
 */
void FileManager::spawn(const fs::path& currentPath, const int depth)
{
	if (depth > MAX_DEPTH)
	{
		return;
	}

	const int folderCount = randomIntInRange(0, MAX_NUM_FOLDERS);
	for (int i = 0; i < folderCount && depth + 1 <= MAX_DEPTH; i++)
	{
		std::string folderName = getRandomName(randomIntInRange(1, MAX_STRING_LENGTH));
		createFolder(currentPath, folderName);
		spawn(currentPath / folderName, depth + 1);
	}

	const int filesCount = randomIntInRange(1, MAX_NUM_FILES);
	for (int i = 0; i < filesCount; i++)
	{
		std::string fileName = getRandomName(randomIntInRange(1, MAX_STRING_LENGTH)) + ".txt";
		createFile(currentPath, fileName);
	}
}

/*
 * Generates a pseudo-random name for a folder or a file.
 */
std::string FileManager::getRandomName(const int length)
{
	assert(length > 0);
	static constexpr char ALPHANUM[] =
		"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	std::string result;
	result.reserve(length);

	for (int i = 0; i < length; i++)
	{
		result += ALPHANUM[rand() % (sizeof(ALPHANUM) - 1)];  // NOLINT(concurrency-mt-unsafe)
	}

	return result;
}

void FileManager::createFolder(const fs::path& folderPath, const std::string& newFolderName)
{
	assert(!newFolderName.empty());

	try
	{
		fs::create_directory(folderPath / newFolderName);
	}
	catch (fs::filesystem_error& e)
	{
		std::cout << e.what() << "\n\n";
	}
}

void FileManager::createFile(const fs::path& folderPath, const std::string& newFileName)
{
	assert(!newFileName.empty());

	std::ofstream ofs(folderPath / newFileName);
	if (!ofs)
	{
		std::cout << "Failed to create file " << newFileName << '\n';
		return;
	}

	const int stringLength = randomIntInRange(1, MAX_STRING_LENGTH);
	ofs << getRandomName(stringLength) << '\n';
	ofs.close();
}

int FileManager::randomIntInRange(const int from, const int to)
{
	assert(from <= to);
	return rand() % to + from;  // NOLINT(concurrency-mt-unsafe)
}

void FileManager::removeDirectory(const fs::path& sourceDirectory)
{
	std::cout << "Clearing directory: " << sourceDirectory.string() << '\n';

	try
	{
		for (auto& item : fs::directory_iterator(sourceDirectory))
		{
			std::cout << '\t' << item.path().string() << '\n';
			fs::remove_all(item);
		}
	}
	catch (fs::filesystem_error& error)
	{
		std::cout << error.what() << '\n';
		abort();
	}
}

/*
 * This method compares two directories and checks if they are the identical.
 * @param sourceDirectory - path to the source directory
 * @param targetDirectory - path to the target directory
 * @return true if directories are identical, false otherwise
 */
bool FileManager::compareTrees(const fs::path& sourceDirectory, const fs::path& targetDirectory)
{
	std::vector<std::string> source;

	for (const auto& item : fs::recursive_directory_iterator(sourceDirectory))
	{
		const std::string actualPathAbsolute = item.path().string();
		const std::string relativePath = getRelativePath(actualPathAbsolute, sourceDirectory.string());
		source.emplace_back(relativePath);
	}

	std::vector<std::string> target;

	for (const auto& item : fs::recursive_directory_iterator(targetDirectory))
	{
		const std::string actualPathAbsolute = item.path().string();
		const std::string relativePath = getRelativePath(actualPathAbsolute, targetDirectory.string());
		target.emplace_back(relativePath);
	}

	if (source.size() != target.size())
	{
		std::cout << "Size of source and target path doesn't match\n";
		return false;
	}

	return std::equal(source.begin(), source.begin() + static_cast<int>(source.size()), target.begin());
}



