#include "dependency/ModuleDependency.h"

#include <format>
#include <regex>

#include "dependency/MalformedDependencyException.h"

ModuleDependency::ModuleDependency(const std::string& data) {
    std::regex regex1(R"~(^module://(.+?)$)~");

    std::smatch match1;

    if (std::regex_match(data, match1, regex1)) {
        name = match1[1];
        return;
    }

    throw MalformedDependencyException(data);
}

bool ModuleDependency::isSimilar(const IDependency* other) const {
    if (const ModuleDependency* moduleOther = dynamic_cast<const ModuleDependency*>(other)) {
        return moduleOther->name == name;
    }
    return false;
}

std::string ModuleDependency::toString() const {
    return std::format("module://{}", name);
}
