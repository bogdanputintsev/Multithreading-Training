#include "FileManager.h"

#include <iostream>

FileManager::FileManager()
{
	srand(static_cast<unsigned>(time(nullptr)));
}

void FileManager::run(const fs::path& sourceDir, const fs::path& targetDir)
{
	std::cout << "Calculating number of items to copy...\n";
	collectAllPathsToCopy(sourceDir);

	std::cout << "There are " << pathsToCopy.size() << " items to copy.\n";
	copyAllPaths(sourceDir, targetDir);
}

void FileManager::collectAllPathsToCopy(const fs::path& sourceDir)
{
	try
	{
		for (const auto& item : fs::recursive_directory_iterator(sourceDir))
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

void FileManager::copyAllPaths(const fs::path& sourceDir, const fs::path& targetDir)
{
	for (const auto& path : pathsToCopy)
	{
		const fs::path copyFrom = path;
		const fs::path copyTo = getTargetPathFromSourcePath(sourceDir, targetDir, path);

		copyFile(copyFrom, copyTo);
	}
}

fs::path FileManager::getTargetPathFromSourcePath(const fs::path& sourceDir, const fs::path& targetDir, const fs::path& absolutePath)
{
	return targetDir / getRelativePath(absolutePath.string(), sourceDir.string());
}

std::string FileManager::getRelativePath(const std::string& absolutePath, const std::string& pathToRemove)
{
	const size_t length = pathToRemove.size();
	return absolutePath.substr(length);
}

void FileManager::copyFile(const fs::path& item, const fs::path& targetDir)
{
	if (fs::is_directory(item))
	{
		fs::create_directories(item);
		return;
	}

	assert(fs::is_regular_file(item));

	if (!fs::exists(targetDir.parent_path()))
	{
		fs::create_directories(targetDir.parent_path());
	}

	try
	{
		fs::copy_file(item, targetDir);
	}
	catch (fs::filesystem_error& e)
	{
		std::cout << e.what() << "\n\n";
	}
}

void FileManager::generateTree(const fs::path& path)
{
	srand(static_cast<unsigned>(time(nullptr)));
	std::cout << "Spawning recursive tree at " << path.string() << '\n';
	spawn(path, 0);
}

void FileManager::spawn(const fs::path& currentPath, const int depth)
{
	assert(fs::exists(currentPath) && fs::is_directory(currentPath));

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

std::string FileManager::getRandomName(const int length)
{
	assert(length > 0);
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	std::string result;
	result.reserve(length);

	for (int i = 0; i < length; i++)
	{
		result += alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	return result;
}

void FileManager::createFolder(const fs::path& folderPath, const std::string& newFolderName)
{
	assert(fs::exists(folderPath) && fs::is_directory(folderPath));
	assert(!newFolderName.empty());

	fs::create_directory(folderPath / newFolderName);
}

void FileManager::createFile(const fs::path& folderPath, const std::string& newFileName)
{
	assert(fs::exists(folderPath) && fs::is_directory(folderPath));
	assert(!newFileName.empty());

	std::ofstream ofs(folderPath / newFileName);

	const int stringLength = randomIntInRange(1, MAX_STRING_LENGTH);
	ofs << getRandomName(stringLength) << '\n';
	ofs.close();
}

int FileManager::randomIntInRange(const int from, const int to)
{
	assert(from <= to);
	return rand() % to + from;
}

void FileManager::removeDir(const fs::path& sourceDir)
{
	std::cout << "Clearing directory: " << sourceDir.string() << '\n';

	try
	{
		for (auto& item : fs::directory_iterator(sourceDir))
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

bool FileManager::compareTrees(const fs::path& sourceDir, const fs::path& targetDir)
{
	std::vector<std::string> source;

	for (const auto& item : fs::recursive_directory_iterator(sourceDir))
	{
		const std::string actualPathAbsolute = item.path().string();
		const std::string relativePath = getRelativePath(actualPathAbsolute, sourceDir.string());
		source.emplace_back(relativePath);
	}

	std::vector<std::string> target;

	for (const auto& item : fs::recursive_directory_iterator(targetDir))
	{
		const std::string actualPathAbsolute = item.path().string();
		const std::string relativePath = getRelativePath(actualPathAbsolute, targetDir.string());
		target.emplace_back(relativePath);
	}

	if (source.size() != target.size())
	{
		std::cout << "Size of source and target path doesn't match\n";
		return false;
	}

	return std::equal(source.begin(), source.begin() + source.size(), target.begin());
}



