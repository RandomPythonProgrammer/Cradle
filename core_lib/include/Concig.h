#pragma once
#include <yaml-cpp/yaml.h>

#include <string>
#include <vector>

#include "dependency.h"

class Config {
   private:
    YAML::Node config;

   public:
    std::string getProjectName() const;
    std::string getExecutableName() const;
    int getCXXVersion() const;
    int getCMakeVersion() const;
};