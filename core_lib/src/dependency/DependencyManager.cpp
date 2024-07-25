#include "dependency/DependencyManager.h"

#include <algorithm>
#include <memory>
#include <vector>

#include "dependency/IDependency.h"
#include "validator/IValidatorFactory.h"

DependencyManager::DependencyManager(const IValidatorFactory* validatorFactory) {
    this->validatorFactory = validatorFactory;
}

bool DependencyManager::addDependency(const IDependency* dependency) {
    std::unique_ptr<const IValidator> validator = std::unique_ptr<const IValidator>(validatorFactory->createValidator(dependency));
    if (validator->validate(dependency)) {
        dependencies.push_back(std::unique_ptr<const IDependency>(dependency));
        return true;
    }
    return false;
}

DependencyManager& DependencyManager::removeDependency(const IDependency* dependency) {
    dependencies.erase(std::remove_if(dependencies.begin(), dependencies.end(), [&](const std::unique_ptr<const IDependency>& ptr) { return ptr->isSimilar(dependency); }), dependencies.end());
    return *this;
}

const std::vector<std::unique_ptr<const IDependency>>& DependencyManager::getDependencies() const {
    return dependencies;
}

const IDependency* DependencyManager::getSimilar(const IDependency* dependency) const {
    return std::find_if(dependencies.begin(), dependencies.end(), [&](const std::unique_ptr<const IDependency>& ptr) { return ptr->isSimilar(dependency);})->get();
}