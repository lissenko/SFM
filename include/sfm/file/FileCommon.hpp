#include <filesystem>

namespace fs = std::filesystem;

namespace FileCommon {

        namespace { // anonymous namespace for "private" functions
        };

        bool isReadAllowed(const fs::path&) noexcept;

        std::string getFilePermissions(const fs::path&);

};
