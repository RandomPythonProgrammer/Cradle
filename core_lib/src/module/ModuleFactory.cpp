#include "module/ModuleFactory.h"
#include "module/ModuleManager.h"
#include "validator/IValidatorFactory.h"

ModuleFactory::ModuleFactory(const ModuleManager* moduleManager, const IValidatorFactory* validatorFactory) {
    this->moduleManager = moduleManager;
    this->validatorFactory = std::unique_ptr<const IValidatorFactory>(validatorFactory);
}

Module ModuleFactory::createModule(const std::string& name) const {
    return Module(validatorFactory.get(), name);
}