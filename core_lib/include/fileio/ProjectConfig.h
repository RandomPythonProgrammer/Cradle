#pragma once
#include <string>
#include "yaml-cpp/node/node.h"

class ProjectConfig {
   private:
    std::string path;
    YAML::Node data;

    std::string cxxVersion;
    std::string cmakeVersion;
    std::string projectName;

    bool save() const;
   public:
    ProjectConfig(const std::string& path);
    const std::string& getCXXVersion() const;
    const std::string& getCMakeVersion() const;
    const std::string& getProjectName() const;

    ProjectConfig& setCXXVersion(const std::string& cxxVersion);
    ProjectConfig& setCMakeVersion(const std::string& cmakeVersion);
    ProjectConfig& setProjectName(const std::string& projectName);
};