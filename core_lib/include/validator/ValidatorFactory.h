#pragma once

#include "IValidatorFactory.h"
#include "dependency/IDependency.h"
#include "module/ModuleManager.h"

class ValidatorFactory : public IValidatorFactory {
   private:
    const ModuleManager* moduleManager;

   public:
    ValidatorFactory(const ModuleManager* moduleManager);
    IValidator* createValidator(const IDependency* dependency) const override;
};