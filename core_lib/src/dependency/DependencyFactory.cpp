#include "dependency/DependencyFactory.h"

#include "dependency/FileDependency.h"
#include "dependency/GitDependency.h"
#include "dependency/MalformedDependencyException.h"
#include "dependency/ModuleDependency.h"

IDependency* DependencyFactory::createDependency(const std::string& data) {
    if (data.starts_with("https://")) {
        return new GitDependency(data);
    } else if (data.starts_with("module://")) {
        return new ModuleDependency(data);
    } else if (data.starts_with("file://")) {
        return new FileDependency(data);
    }
    throw MalformedDependencyException(data);
}