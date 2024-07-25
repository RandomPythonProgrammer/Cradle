#include "module/ModuleManager.h"
#include <pstl/glue_algorithm_defs.h>
#include "module/IModuleFactory.h"

ModuleManager::ModuleManager(const IModuleFactory* moduleFactory) {
    this->moduleFactory = std::unique_ptr<const IModuleFactory>(moduleFactory);
}

ModuleManager& ModuleManager::createModule(const std::string& name) {
    modules.emplace(name, moduleFactory->createModule(name));
    return *this;
}

Module& ModuleManager::getModule(const std::string& name) {
    return modules.at(name);
}

ModuleManager& ModuleManager::removeModule(const std::string& name) {
    modules.erase(modules.find(name));
    return *this;
}

bool ModuleManager::hasModule(const std::string& name) const {
    return modules.contains(name);
}