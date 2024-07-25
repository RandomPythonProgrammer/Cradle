#pragma once
#include <string>

#include "dependency/DependencyManager.h"
#include "validator/IValidatorFactory.h"

class Module {
   private:
    std::string name;
    std::unique_ptr<DependencyManager> dependencyManager;

   public:
    Module(const IValidatorFactory* validatorFactory, const std::string& name);
    std::string getName();
    Module& setName(const std::string& name);
    DependencyManager& getDependencyManager();
};
