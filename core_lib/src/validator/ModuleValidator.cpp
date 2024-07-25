#include "validator/ModuleValidator.h"
#include <stdexcept>

#include "dependency/IDependency.h"
#include "dependency/ModuleDependency.h"
#include "module/ModuleManager.h"

ModuleValidator::ModuleValidator(const ModuleManager* moduleManager) {
    this->moduleManager = moduleManager;
}

bool ModuleValidator::validate(const IDependency* dependency) const {
    if (const ModuleDependency* moduleDependency = dynamic_cast<const ModuleDependency*>(dependency)) {
        return this->moduleManager->hasModule(moduleDependency->name);
    }
    throw std::runtime_error("Not a ModuleDependency");
}