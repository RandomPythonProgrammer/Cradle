#pragma once
#include <string>

#include "IDependency.h"

class GitDependency : public IDependency {
   public:
    std::string git, tag, name, owner;
    GitDependency(const std::string& data);
    bool isSimilar(const IDependency* other) const override;
    std::string toString() const override;
};
