#include "sfm/file/FileCommon.hpp"

#include <array>
#include <iostream>

#include <grp.h>
#include <pwd.h>
#include <sys/stat.h>
#include <unistd.h>

constexpr size_t PERMS_TYPE_COUNT = 3;

constexpr std::array<fs::perms, 9> PERMS = {fs::perms::owner_read,
        fs::perms::owner_write, fs::perms::owner_exec,
        fs::perms::group_read, fs::perms::group_write,
        fs::perms::group_exec, fs::perms::others_read,
        fs::perms::others_write, fs::perms::others_exec };

constexpr std::string_view NO_PERM = "-";

bool FileCommon::isReadAllowed(const fs::path& path) noexcept
{
        struct stat info;
        if ( stat(path.c_str(), &info) == -1 ){
                std::cerr << "Error occured with stat\n";
                return 0;
        }
        struct passwd *pw = getpwuid(info.st_uid);
        struct group *gr = getgrgid(info.st_gid);
        __uid_t uid = getuid();
        bool me = pw->pw_uid == uid;
        bool group = gr->gr_gid == uid;
        bool others = (fs::status(path).permissions() & fs::perms::others_read) != fs::perms::none;
        return (me || group || others);
}


std::string FileCommon::getFilePermissions(const fs::path& filePath)
{
        const fs::perms& p = fs::status(filePath).permissions();
        std::string permsString {};
        std::string c {};
        for (size_t i = 0; i < PERMS.size(); ++i) {
                size_t type = i % PERMS_TYPE_COUNT;
                if (type == 0)
                        c = 'r';
                else if (type == 1)
                        c = 'w';
                else
                        c = 'x';
                permsString += ((p & PERMS.at(i)) != fs::perms::none ? c : NO_PERM);
        }
        return permsString;
}
