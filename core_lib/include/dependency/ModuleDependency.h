#pragma once

#include <string>

#include "IDependency.h"

class ModuleDependency : public IDependency {
   public:
    std::string name;
    ModuleDependency(const std::string& data);
    bool isSimilar(const IDependency* other) const override;
};