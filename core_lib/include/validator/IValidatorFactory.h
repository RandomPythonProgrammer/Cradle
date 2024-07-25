#pragma once

#include "IValidator.h"
#include "dependency/IDependency.h"

class IValidatorFactory {
   public:
    virtual ~IValidatorFactory() = default;
    virtual IValidator* createValidator(const IDependency* dependency) const = 0;
};