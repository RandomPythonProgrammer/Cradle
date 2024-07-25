#pragma once

#include "IValidator.h"

class GitValidator : public IValidator {
   public:
    bool validate(const IDependency* dependency) const override;
};
