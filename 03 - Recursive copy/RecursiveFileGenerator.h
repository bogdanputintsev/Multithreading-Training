#pragma once

#include <filesystem>
#include <fstream>
#include <cassert>

namespace fs = std::filesystem;

class RecursiveFileGenerator
{
public:
	RecursiveFileGenerator(const fs::path& _startPath, const int _maxDepth, const int _maxNumFolders, const int _maxNumFiles);
	void generateTree();
protected:
	void spawn(const fs::path& currentPath, const int depth = 0);
	static std::string getRandomName(const int length);
	static void createFolder(const fs::path& folderPath, const std::string& newFolderName);
	static void createFile(const fs::path& folderPath, const std::string& newFileName);
	static int randomIntInRange(const int from, const int to);
private:
	const fs::path startPath;
	const int maxDepth;
	const int maxNumFolders;
	const int maxNumFiles;
	
	const static int MAX_STRING_LENGTH = 15;
};

