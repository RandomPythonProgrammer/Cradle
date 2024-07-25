#include "validator/FileValidator.h"

#include <filesystem>
#include <format>
#include <fstream>
#include <stdexcept>
#include <string>

#include "dependency/FileDependency.h"
#include "dependency/IDependency.h"

bool FileValidator::validate(const IDependency* dependency) const {
    //TODO: There has to be a better way than this to check if a package exists
    //I have already tried the --find-package and -P mode but none of them work
    if (const FileDependency* fileDependency = dynamic_cast<const FileDependency*>(dependency)) {
        std::filesystem::path dir(".temp");
        std::filesystem::path build = dir / "build";
        std::filesystem::path fullPath = dir / "CMakeLists.txt";
        std::filesystem::create_directories(build);
        std::ofstream stream(fullPath);
        if (stream.is_open()) {
            stream << std::format("find_package({})\nif(NOT {}_FOUND)\n\tmessage(FATAL_ERROR \"NOT FOUND\")\nendif()", fileDependency->name, fileDependency->name) << std::endl;
            stream.close();
            int status = system(std::format("cmake -S {} -B {} > output.txt 2>&1", dir.string(), build.string()).c_str());
            std::filesystem::remove_all(".temp");
            return status == 0;
        }
        throw std::runtime_error("Failed to create temp CMakeLists.txt");
    }
    throw std::runtime_error("Not a FileDependency");
}