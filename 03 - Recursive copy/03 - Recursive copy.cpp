#include "RecursiveFileGenerator.h"
#include "CopyManager.h"

namespace
{
	const std::string SOURCE_DIR = "D:\\FolderFrom\\";
	const std::string TARGET_DIR = "D:\\FolderTo\\";
	const int MAX_DEPTH = 5;
	const int MAX_NUM_FOLDERS = 5;
	const int MAX_NUM_FILES = 5;
}

int main()
{
	//RecursiveFileGenerator recursiveFileGenerator(SOURCE_DIR, MAX_DEPTH, MAX_NUM_FOLDERS, MAX_NUM_FILES);
	//recursiveFileGenerator.generateTree();

	CopyManager copyManager;
	copyManager.run(SOURCE_DIR, TARGET_DIR);

	return EXIT_SUCCESS;
}