#include "CopyManager.h"

const std::string SOURCE_DIR = "D:\\FolderFrom\\";
const std::string TARGET_DIR = "D:\\FolderTo\\";

int main()
{
	if (!CopyManager::copyDir(SOURCE_DIR, TARGET_DIR))
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}