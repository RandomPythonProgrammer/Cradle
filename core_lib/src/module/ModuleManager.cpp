#include "module/ModuleManager.h"
#include <pstl/glue_algorithm_defs.h>
#include <unordered_map>
#include "module/IModuleFactory.h"

ModuleManager::ModuleManager(const IModuleFactory* moduleFactory) {
    this->moduleFactory = std::unique_ptr<const IModuleFactory>(moduleFactory);
}

Module& ModuleManager::createModule(const std::string& name) {
    modules.emplace(name, moduleFactory->createModule(name));
    return getModule(name);
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

std::vector<std::string> ModuleManager::getModules() const {
    std::vector<std::string> vec;
    for (const std::pair<const std::string, Module>& pair: modules) {
        vec.push_back(pair.first);
    }
    return vec;
}