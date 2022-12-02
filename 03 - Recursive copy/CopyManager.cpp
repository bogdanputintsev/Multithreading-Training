#include "CopyManager.h"

bool CopyManager::copyDir(const fs::path& sourceDir, const fs::path& targetDir)
{
	if (!fs::exists(sourceDir) || !fs::exists(targetDir))
	{
		std::cout << "The path is not exist.\n";
		return false;
	}

	if (!fs::is_directory(sourceDir) || !fs::is_directory(targetDir))
	{
		std::cout << "The path is not directory.\n";
		return false;
	}

	for (const auto& item : fs::directory_iterator(sourceDir))
	{
		fs::path filename = item.path().filename();
	}

	return true;
}

void CopyManager::loopDir(const fs::path& sourceDir, const fs::path& targetDir, const fs::directory_entry& item)
{
	fs::path filename = item.path().filename();

	if (fs::is_directory(item))
	{
		std::cout << "\t" << (sourceDir / filename) << '\n';
		fs::create_directory(targetDir / filename);
		copyDir(sourceDir / filename, targetDir / filename);
	}
	else if (fs::is_regular_file(item))
	{
		copyFile(item, targetDir);
	}
}

void CopyManager::copyFile(const fs::path& item, const fs::path& targetDir)
{
	try
	{
		fs::copy_file(item, targetDir);
	}
	catch (fs::filesystem_error& e)
	{
		std::cout << e.what() << '\n';
	}
}