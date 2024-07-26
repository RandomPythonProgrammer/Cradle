#pragma once
#include <string>

#include "IDependency.h"

class FileDependency : public IDependency {
   public:
    std::string name;
    FileDependency(const std::string& data);
    bool isSimilar(const IDependency* other) const override;
    std::string toString() const override;
};
