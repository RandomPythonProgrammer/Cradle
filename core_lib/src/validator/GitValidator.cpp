#include "validator/GitValidator.h"

#include <cpr/cpr.h>
#include <stdexcept>

#include "dependency/GitDependency.h"
#include "dependency/IDependency.h"

bool GitValidator::validate(const IDependency* dependency) const {
    if (const GitDependency* gitDependency = dynamic_cast<const GitDependency*>(dependency)) {
        cpr::Response cmakeResponse = cpr::Get(cpr::Url(std::format("https://github.com/{}/{}", gitDependency->owner, gitDependency->name)));
        return cmakeResponse.status_code == 200;
    }
    throw std::runtime_error("Not a GitDependency");
}