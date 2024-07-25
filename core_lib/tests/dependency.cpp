#include <catch2/catch_test_macros.hpp>

#include "dependency/DependencyFactory.h"
#include "dependency/FileDependency.h"
#include "dependency/GitDependency.h"
#include "dependency/IDependency.h"
#include "dependency/ModuleDependency.h"

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

    std::unique_ptr<IDependency> dependency2 = std::unique_ptr<IDependency>(new GitDependency(git));
    GitDependency* gitDependency2 = dynamic_cast<GitDependency*>(dependency2.get());
    REQUIRE(gitDependency2->git == git);
    REQUIRE(gitDependency2->tag == "");
    REQUIRE(gitDependency2->name == name);
}

TEST_CASE("Parse FileDependency", "[Dependency]") {
    std::string prefix = "file://";
    std::string name = "opencv";
    std::string testString = prefix + name;

    std::unique_ptr<IDependency> dependency = std::unique_ptr<IDependency>(new FileDependency(testString));
    FileDependency* fileDependency = dynamic_cast<FileDependency*>(dependency.get());
    REQUIRE(fileDependency->name == name);
}

TEST_CASE("Parse ModuleDependency", "[Dependency]") {
    std::string prefix = "module://";
    std::string name = "core_lib";
    std::string testString = prefix + name;

    std::unique_ptr<IDependency> dependency = std::unique_ptr<IDependency>(new ModuleDependency(testString));
    ModuleDependency* moduleDependency = dynamic_cast<ModuleDependency*>(dependency.get());
    REQUIRE(moduleDependency->name == name);
}

TEST_CASE("DependencyFactory", "[Dependency]") {
    std::string raw;
    IDependency* dep;
    raw = "https://github.com/catchorg/Catch2.git==v3.6.0";
    dep = DependencyFactory::createDependency(raw);
    REQUIRE(dynamic_cast<GitDependency*>(dep));

    raw = "file://opencv";
    dep = DependencyFactory::createDependency(raw);
    REQUIRE(dynamic_cast<FileDependency*>(dep));

    raw = "module://core_lib";
    dep = DependencyFactory::createDependency(raw);
    REQUIRE(dynamic_cast<ModuleDependency*>(dep));
}
