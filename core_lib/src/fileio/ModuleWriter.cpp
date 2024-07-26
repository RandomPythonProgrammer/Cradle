#include "fileio/ModuleWriter.h"

#include <yaml-cpp/yaml.h>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <vector>

#include "dependency/IDependency.h"
#include "module/Module.h"

ModuleWriter::ModuleWriter(const std::string& path) {
    this->path = path;
}

ModuleWriter& ModuleWriter::write(ModuleManager& manager) {
    YAML::Node node;
    for (const std::string& name: manager.getModules()) {
        Module& module = manager.getModule(name);
        YAML::Node moduleNode;
        moduleNode["name"] = name;
        int numDeps = module.getDependencyManager().getDependencies().size();
        for (const std::unique_ptr<const IDependency>& dep: module.getDependencyManager().getDependencies()) {
            moduleNode["dependencies"].push_back(dep->toString());
        }
        node["modules"].push_back(moduleNode);
    }

    std::ofstream stream(path);
    if (stream.good()) {
        stream << node;
        stream.close();
    } else {
        throw std::runtime_error("Failed to write module data");
    }

    return *this;
}