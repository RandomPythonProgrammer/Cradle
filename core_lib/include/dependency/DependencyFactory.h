#pragma once
#include <string>

#include "IDependency.h"

class DependencyFactory {
   public:
    static IDependency* createDependency(const std::string& data);
};
