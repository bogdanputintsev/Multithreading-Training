#include "RecursiveFileGenerator.h"

RecursiveFileGenerator::RecursiveFileGenerator(const fs::path& _startPath, const int _maxDepth, const int _maxNumFolders, const int _maxNumFiles)
	: startPath(_startPath),
		maxDepth(_maxDepth),
		maxNumFolders(_maxNumFolders),
		maxNumFiles(_maxNumFiles)
{
	assert(fs::exists(_startPath));
	assert(fs::is_directory(_startPath));
	assert(_maxDepth > 0);
	assert(_maxNumFolders >= 0);
	assert(_maxNumFiles >= 0);

	srand(static_cast<unsigned>(time(nullptr)));
}

void RecursiveFileGenerator::generateTree()
{
	spawn(startPath, 0);
}

void RecursiveFileGenerator::spawn(const fs::path& currentPath, const int depth)
{
	assert(fs::exists(currentPath) && fs::is_directory(currentPath));

	if (depth > maxDepth)
	{
		return;
	}

	int folderCount = randomIntInRange(0, maxNumFolders);
	for (int i = 0; i < folderCount; i++)
	{
		std::string folderName = getRandomName(randomIntInRange(1, MAX_STRING_LENGTH));
		createFolder(currentPath, folderName);
		spawn(currentPath / folderName, depth + 1);
	}

	int filesCount = randomIntInRange(0, maxNumFiles);
	for (int i = 0; i < filesCount; i++)
	{
		std::string fileName = getRandomName(randomIntInRange(1, MAX_STRING_LENGTH));
		createFile(currentPath, fileName);
	}
}

std::string RecursiveFileGenerator::getRandomName(const int length)
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

void RecursiveFileGenerator::createFolder(const fs::path& folderPath, const std::string& newFolderName)
{
	assert(fs::exists(folderPath) && fs::is_directory(folderPath));
	assert(newFolderName != "" && newFolderName.size() > 0);

	fs::create_directory(folderPath / newFolderName);
}

void RecursiveFileGenerator::createFile(const fs::path& folderPath, const std::string& newFileName)
{
	assert(fs::exists(folderPath) && fs::is_directory(folderPath));
	assert(newFileName != "" && newFileName.size() > 0);

	std::ofstream ofs(folderPath / newFileName);
	
	int stringLength = randomIntInRange(1, MAX_STRING_LENGTH);
	ofs << getRandomName(stringLength) << '\n';
	ofs.close();
}

int RecursiveFileGenerator::randomIntInRange(const int from, const int to)
{
	assert(from <= to);
	return rand() % to + from;
}
