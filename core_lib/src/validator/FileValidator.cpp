#include "validator/FileValidator.h"

#include <format>
#include <stdexcept>
#include <string>

#include "dependency/FileDependency.h"
#include "dependency/IDependency.h"

bool FileValidator::validate(const IDependency* dependency) const {
    if (const FileDependency* fileDependency = dynamic_cast<const FileDependency*>(dependency)) {
        int status = system(std::format("cmake --find-package -D name={}", fileDependency->name).c_str());
        return !status;
    }
    throw std::runtime_error("Not a FileDependency");
}