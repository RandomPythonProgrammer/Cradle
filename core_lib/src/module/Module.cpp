#include "module/Module.h"

#include <string>

#include "dependency/DependencyManager.h"
#include "validator/IValidatorFactory.h"

Module::Module(const IValidatorFactory* validatorFactory, const std::string& name) {
    dependencyManager = std::make_unique<DependencyManager>(validatorFactory);
    this->name = name;
}

std::string Module::getName() {
    return name;
}

Module& Module::setName(const std::string& name) {
    this->name = name;
    return *this;
}

DependencyManager& Module::getDependencyManager() {
    return *dependencyManager.get();
}