#include "module/ModuleManagerFactory.h"
#include "module/ModuleManager.h"
#include "module/ModuleFactory.h"
#include "validator/IValidatorFactory.h"
#include "validator/ValidatorFactory.h"

ModuleManager* ModuleManagerFactory::createModuleManager() {
    IModuleFactory* moduleFactory;
    IValidatorFactory* validatorFactory;
    ModuleManager* manager = new ModuleManager(moduleFactory);
    validatorFactory = new ValidatorFactory(manager);
    moduleFactory = new ModuleFactory(manager, validatorFactory);
    return manager;
}