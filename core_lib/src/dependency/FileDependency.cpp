#include "dependency/FileDependency.h"

#include <regex>

#include "dependency/MalformedDependencyException.h"

FileDependency::FileDependency(const std::string& data) {
    std::regex regex1(R"~(^file://(.+?)$)~");

    std::smatch match1;

    if (std::regex_match(data, match1, regex1)) {
        name = match1[1];
        return;
    }

    throw MalformedDependencyException(data);
}

bool FileDependency::isSimilar(const IDependency* other) const {
    if (const FileDependency* fileOther = dynamic_cast<const FileDependency*>(other)) {
        return fileOther->name == name;
    }
    return false;
}