#include "fileio/ProjectConfig.h"

#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>

#include <fstream>
#include <stdexcept>

bool ProjectConfig::save() const {
    std::ofstream ostream(path);
    if (ostream.good()) {
        ostream << data;
        return true;
        ostream.close();
    } else {
        throw std::runtime_error("Failed to write project config");
    }

    return false;
}

ProjectConfig::ProjectConfig(const std::string& path) {
    this->path = path;
    data = YAML::LoadFile(path);
}

const std::string& ProjectConfig::getCXXVersion() const {
    return cxxVersion;
}

const std::string& ProjectConfig::getCMakeVersion() const {
    return cmakeVersion;
}

const std::string& ProjectConfig::getProjectName() const {
    return projectName;
}

ProjectConfig& ProjectConfig::setCXXVersion(const std::string& cxxVersion) {
    this->cxxVersion = cxxVersion;
    save();
    return *this;
}

ProjectConfig& ProjectConfig::setCMakeVersion(const std::string& cmakeVersion) {
    this->cmakeVersion = cmakeVersion;
    save();
    return *this;
}

ProjectConfig& ProjectConfig::setProjectName(const std::string& projectName) {
    this->projectName = projectName;
    save();
    return *this;
}