#include "validator/ValidatorFactory.h"
#include <stdexcept>
#include "dependency/FileDependency.h"
#include "dependency/GitDependency.h"
#include "dependency/IDependency.h"
#include "dependency/ModuleDependency.h"
#include "module/ModuleManager.h"
#include "validator/FileValidator.h"
#include "validator/GitValidator.h"
#include "validator/IValidator.h"
#include "validator/ModuleValidator.h"

ValidatorFactory::ValidatorFactory(const ModuleManager* moduleManager) {
    this->moduleManager = moduleManager;
}

IValidator* ValidatorFactory::createValidator(const IDependency* dependency) const {
    if (dynamic_cast<const ModuleDependency*>(dependency)) {
        return new ModuleValidator(moduleManager);
    } else if (dynamic_cast<const FileDependency*>(dependency)) {
        return new FileValidator();
    } else if (dynamic_cast<const GitDependency*>(dependency)) {
        return new GitValidator();
    }
    throw std::runtime_error("No applicable IValidator");
}