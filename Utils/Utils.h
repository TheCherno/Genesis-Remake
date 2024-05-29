#pragma once

#include <filesystem>

namespace Genesis {

    namespace Utils {

        char * ResolvePath(const char *path);
        std::filesystem::path ResolvePath(const std::filesystem::path& path);
    }
}
