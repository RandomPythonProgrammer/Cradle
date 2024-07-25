#pragma once

#include <memory>
#include "Module.h"
#include "IModuleFactory.h"
#include <unordered_map>

struct ModuleManager {
    private:
        std::unordered_map<std::string, Module> modules;
        std::unique_ptr<const IModuleFactory> moduleFactory;
    public:
        ModuleManager(const IModuleFactory* moduleFactory);
        Module& createModule(const std::string& name);
        Module& getModule(const std::string& name);
        ModuleManager& removeModule(const std::string& name);
        bool hasModule(const std::string& name) const;
};