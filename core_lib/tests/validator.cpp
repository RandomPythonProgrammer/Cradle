#include <catch2/catch_test_macros.hpp>

#include "dependency/DependencyFactory.h"
#include "dependency/IDependency.h"
#include "validator/GitValidator.h"

TEST_CASE("Git Validation", "[Validate]") {
    IDependency* dep = DependencyFactory::createDependency("https://github.com/catchorg/Catch2.git");
    IDependency* fakeDep = DependencyFactory::createDependency("https://github.com/catchorg/Catch3.git");
    GitValidator validator;
    REQUIRE(validator.validate(dep));
    REQUIRE_FALSE(validator.validate(fakeDep));
}