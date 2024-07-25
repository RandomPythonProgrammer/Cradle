#pragma once

#include <memory>
#include <vector>

#include "IDependency.h"
#include "validator/IValidatorFactory.h"

class DependencyManager {
   private:
    std::vector<std::unique_ptr<const IDependency>> dependencies;
    std::unique_ptr<const IValidatorFactory> validatorFactory;

    public:
        DependencyManager(const IValidatorFactory* validatorFactory);
        DependencyManager& addDependency(const IDependency* dependency);
        const std::vector<std::unique_ptr<const  IDependency>>& getDependencies() const;
        DependencyManager& removeDependency(const IDependency* dependency);
        const IDependency* getSimilar(const IDependency* dependency) const;
};
