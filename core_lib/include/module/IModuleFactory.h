#pragma once

#include "Module.h"

class IModuleFactory {
   public:
    virtual ~IModuleFactory() = default;
    virtual Module createModule(const std::string& name) const = 0;
};