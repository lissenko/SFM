#include "sfm/file/FileDecorator.hpp"

#include <cmath>

#include "sfm/file/FileCommon.hpp"

/*
 * Strongly inspired by: https://en.cppreference.com/w/cpp/filesystem/file_size
 */
const std::string FileDecorator::humandReadable(const uintmax_t& bytes) const
{
        std::string result {};
        int i{};
        double mantissa = static_cast<double>(bytes);
        for (; mantissa >= 1024.; mantissa /= 1024., ++i) { }
        mantissa = std::ceil(mantissa * 10.) / 10.;
        std::string mantissaStr = std::to_string(mantissa);
        mantissaStr.erase ( mantissaStr.find_last_not_of('0') + 1, std::string::npos );
        if (mantissaStr.ends_with('.'))
                mantissaStr.pop_back();
        if (i == 0) // padding
                mantissaStr.push_back(' ');
        result += mantissaStr + ' ' + "BKMGTPE"[i];
        return i == 0 ? result : result += "B";
}

const std::string FileDecorator::extractCharacteristic(const fs::directory_entry& entry) const noexcept
{
        if (entry.is_directory()) {
                if (FileCommon::isReadAllowed(entry.path())) {
                        std::ptrdiff_t dirCount = std::distance(fs::directory_iterator(entry), fs::directory_iterator{});
                        return std::to_string(dirCount);
                } else {
                        return "?";
                }
        } else if (entry.is_regular_file()) {
                return humandReadable(entry.file_size());

        }
        return "special";
}
