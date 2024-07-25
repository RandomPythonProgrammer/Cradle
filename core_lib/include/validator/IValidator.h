#pragma once

#include "dependency/IDependency.h"

class IValidator {
   public:
    virtual ~IValidator() = default;
    virtual bool validate(const IDependency* dependency) const = 0;
};
