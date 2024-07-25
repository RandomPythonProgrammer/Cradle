#include <catch2/catch_all.hpp>
#include "dependency/IDependency.h"
#include "dependency/GitDependency.h"

TEST_CASE("Parse GitDependency", "[Dependency]") {
    std::string git = "https://github.com/catchorg/Catch2.git";
    std::string tag = "v3.6.0";
    std::string name = "Catch2";
    std::string testString = git + "==" + tag;

    std::unique_ptr<IDependency> dependency = std::unique_ptr<IDependency>(new GitDependency(testString));
    GitDependency* gitDependency = dynamic_cast<GitDependency*>(dependency.get());
    REQUIRE(gitDependency->git == git);
    REQUIRE(gitDependency->tag == tag);
    REQUIRE(gitDependency->name == name);
}