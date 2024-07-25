#pragma once

#include "module/IModuleFactory.h"
#include "module/ModuleManager.h"
#include "validator/IValidatorFactory.h"

class ModuleFactory: public IModuleFactory {
    private:
    const ModuleManager* moduleManager;
    std::unique_ptr<const IValidatorFactory> validatorFactory;
    public:
    ModuleFactory(const ModuleManager* moduleManager, const IValidatorFactory* validatorFactory);
    Module createModule(const std::string& name) const override;
};