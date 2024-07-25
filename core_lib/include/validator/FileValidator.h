#pragma once

#include "IValidator.h"

class FileValidator : public IValidator {
   public:
    bool validate(const IDependency* dependency) const override;
};
