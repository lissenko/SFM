#include "sfm/file/FileHandler.hpp"

#include <algorithm>
#include <filesystem>
#include <vector>

bool FileHandler::isDir(const fs::directory_entry& file)
{
        return fs::is_directory(file);
}

size_t FileHandler::
populate(const fs::path& path, std::vector<fs::directory_entry>& files, std::vector<std::string>& characteristics, bool showDots) const noexcept
{
        // populate with file name
        for (const fs::path& entry :  fs::directory_iterator(path)) {
                if (!showDots && entry.filename().string().at(0) == '.') continue;
                fs::directory_entry absoluteEntry = fs::directory_entry(fs::absolute(entry));
                files.push_back(absoluteEntry);
        }

        // sort
        std::partition(files.begin(), files.end(), isDir);
        const auto partitionPoint = std::partition_point(files.cbegin(), files.cend(), isDir);
        std::ptrdiff_t dirCount = std::distance(files.cbegin(), partitionPoint);
	std::sort(files.begin(), files.begin() + dirCount);
	std::sort(files.begin() + dirCount, files.end());

        // populate with characteristic
        for (const fs::directory_entry& e: files) {
                std::string characteristic = fileDecorator.extractCharacteristic(e);
                characteristics.push_back(characteristic);
        }
        return static_cast<size_t>(dirCount);
}

void FileHandler::remove(const fs::path& path) const noexcept
{
        fs::remove_all(path);
}

void FileHandler::rename(const fs::path& oldP, const fs::path& newP) const noexcept
{
        fs::rename(oldP, newP);
}
