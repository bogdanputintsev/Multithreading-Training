#include "CopyManager.h"

void CopyManager::run(const fs::path& sourceDir, const fs::path& targetDir)
{
	copyDir(sourceDir, targetDir);

	for (auto & f : futureThreads)
	{
		f.get();
	}
}

bool CopyManager::copyDir(const fs::path& sourceDir, const fs::path& targetDir)
{
	if (!fs::exists(sourceDir) || !fs::exists(targetDir))
	{
		std::cout << "The directory doesn't exist.\n";
		return false;
	}

	if (!fs::is_directory(sourceDir) || !fs::is_directory(targetDir))
	{
		std::cout << "The path is not directory.\n";
		return false;
	}

	std::lock_guard<std::mutex> lock(m);
	futureThreads.emplace_back(std::async(std::launch::async, &CopyManager::loopDir, this, sourceDir, targetDir));
	return true;
}

void CopyManager::loopDir(const fs::path sourceDir, const fs::path targetDir)
{
	assert(fs::exists(sourceDir));
	assert(fs::is_directory(sourceDir));
	assert(fs::exists(targetDir));
	assert(fs::is_directory(sourceDir));

	for (const auto& item : fs::directory_iterator(sourceDir))
	{
		assert(fs::exists(item));

		fs::path filename = item.path().filename();

		if (fs::is_directory(item))
		{
			//std::cout << "\t" << (sourceDir / filename) << '\n';
			fs::create_directory(targetDir / filename);

			assert(fs::exists(targetDir / filename));
			assert(fs::is_directory(targetDir / filename));

			copyDir(sourceDir / filename, targetDir / filename);
		}
		else if (fs::is_regular_file(item))
		{
			//copyThreads.push_back(std::move(std::thread(CopyManager::copyFile, std::ref(item), std::ref(targetDir))));
		}
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