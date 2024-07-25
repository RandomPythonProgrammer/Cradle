#include <catch2/catch_test_macros.hpp>

#include "dependency/DependencyFactory.h"
#include "dependency/IDependency.h"
#include "module/ModuleManager.h"
#include "module/ModuleManagerFactory.h"
#include "validator/FileValidator.h"
#include "validator/GitValidator.h"
#include "validator/IValidator.h"
#include "validator/ModuleValidator.h"
#include "validator/ValidatorFactory.h"

TEST_CASE("Git Validation", "[Validate]") {
    IDependency* dep = DependencyFactory::createDependency("https://github.com/catchorg/Catch2.git");
    IDependency* fakeDep = DependencyFactory::createDependency("https://github.com/catchorg/Catch3.git");
    GitValidator validator;
    REQUIRE(validator.validate(dep));
    REQUIRE_FALSE(validator.validate(fakeDep));
}

TEST_CASE("File Validation", "[Validate]") {
    IDependency* dep = DependencyFactory::createDependency("file://CURL");
    IDependency* fakeDep = DependencyFactory::createDependency("file://veryFakeModule");
    FileValidator validator;
    REQUIRE(validator.validate(dep));
    REQUIRE_FALSE(validator.validate(fakeDep));
}

TEST_CASE("Module Validation", "[Validate]") {
    std::unique_ptr<ModuleManager> manager = std::unique_ptr<ModuleManager>(ModuleManagerFactory::createModuleManager());
    manager->createModule("MyModule");
    Module& module = manager->createModule("MyModule1");
    IDependency* dep = DependencyFactory::createDependency("module://MyModule");
    IDependency* depFake = DependencyFactory::createDependency("module://veryFakeModule");
    REQUIRE(module.getDependencyManager().addDependency(dep));
    REQUIRE_FALSE(module.getDependencyManager().addDependency(depFake));
}

TEST_CASE("ValidatorFactory", "[Validate]") {
    std::unique_ptr<ModuleManager> manager = std::unique_ptr<ModuleManager>(ModuleManagerFactory::createModuleManager());
    ValidatorFactory factory(manager.get());
    IDependency* dep;
    IValidator* validator;

    dep = DependencyFactory::createDependency("https://github.com/catchorg/Catch2.git==v3.6.0");
    validator = factory.createValidator(dep);
    REQUIRE(dynamic_cast<GitValidator*>(validator));

    dep = DependencyFactory::createDependency("file://CURL");
    validator = factory.createValidator(dep);
    REQUIRE(dynamic_cast<FileValidator*>(validator));
    
    dep = DependencyFactory::createDependency("module://MyModule");
    validator = factory.createValidator(dep);
    REQUIRE(dynamic_cast<ModuleValidator*>(validator));
}