#pragma once

#include "IValidator.h"
#include "module/ModuleManager.h"

class ModuleValidator : public IValidator {
   private:
   const ModuleManager* moduleManager;
   public:
    ModuleValidator(const ModuleManager* moduleManager);
    bool validate(const IDependency* dependency) const override;
};