#include "module/ModuleManagerFactory.h"
#include <cstdlib>
#include "module/IModuleFactory.h"
#include "module/ModuleManager.h"
#include "module/ModuleFactory.h"
#include "validator/IValidatorFactory.h"
#include "validator/ValidatorFactory.h"

ModuleManager* ModuleManagerFactory::createModuleManager() {
    IModuleFactory* moduleFactory = (IModuleFactory*) malloc(sizeof(ModuleFactory));
    IValidatorFactory* validatorFactory = (IValidatorFactory*) malloc(sizeof(ValidatorFactory));
    ModuleManager* manager = new ModuleManager(moduleFactory);
    new (validatorFactory) ValidatorFactory(manager);
    new (moduleFactory) ModuleFactory(manager, validatorFactory);
    return manager;
}