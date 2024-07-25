#include <catch2/catch_all.hpp>
#include <memory>

#include "catch2/catch_test_macros.hpp"
#include "module/ModuleManager.h"
#include "module/ModuleManagerFactory.h"

TEST_CASE("Create Module", "[Module]") {
    std::unique_ptr<ModuleManager> manager = std::unique_ptr<ModuleManager>(ModuleManagerFactory::createModuleManager());
    manager->createModule("MyModule");
    REQUIRE(manager->hasModule("MyModule"));
}