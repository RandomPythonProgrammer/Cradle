#include "dependency/MalformedDependencyException.h"

#include <format>

MalformedDependencyException::MalformedDependencyException(const std::string& dependency) {
    message = std::format("Malformed Dependency: {}", dependency);
}

const char* MalformedDependencyException::what() const throw() {
    return message.c_str();
}
