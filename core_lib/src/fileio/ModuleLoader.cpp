#include "fileio/ModuleLoader.h"
#include <yaml-cpp/yaml.h>
#include "dependency/DependencyFactory.h"
#include "dependency/IDependency.h"

ModuleLoader::ModuleLoader(const std::string& path) {
    this->path = path;
}

ModuleLoader& ModuleLoader::load(ModuleManager& manager) {
    YAML::Node node = YAML::LoadFile(path);

    YAML::Node modulesData = node["modules"];
    for (const YAML::Node& moduleData: modulesData) {
        std::string name = moduleData["name"].as<std::string>();
        Module& module = manager.createModule(name);
        YAML::Node depsData = moduleData["dependencies"];
        for (const YAML::Node& depData: depsData) {
            std::string rawDep = depData.as<std::string>();
            IDependency* dep = DependencyFactory::createDependency(rawDep);
            module.getDependencyManager().addDependency(dep);
        }
    }
    
    return *this;
}