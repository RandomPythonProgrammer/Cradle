#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>

#include <cmath>
#include <filesystem>
#include <format>
#include <fstream>
#include <functional>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>

#include "Logger.h"

Logger logger(LogLevel::INFO, "Main", &std::cout);

bool hasToken(const std::vector<std::string>& tokens, const std::string token) {
    return std::find(tokens.begin(), tokens.end(), token) != tokens.end();
}

bool initCheck() {
    if (!std::filesystem::exists("cradle.yaml")) {
        logger.fatal("cradle.yaml not found, please run \"cradle init\"");
        return false;
    }
    return true;
}

/// Note: Does not actually use the arguments
int build(const std::vector<std::string>& args) {
    if (initCheck()) {
        YAML::Node config = YAML::LoadFile("cradle.yaml");

        std::filesystem::create_directory("include");
        std::filesystem::create_directory("src");

        std::ofstream cmake("CMakeLists.txt");

        if (cmake.good()) {
            cmake << "# Auto-Generated File *DO NOT EDIT*\n";

            cmake << "\n";

            cmake << std::format("cmake_minimum_required(VERSION {} FATAL_ERROR)\n", config["CMake Version"].as<std::string>());
            cmake << std::format("project({})\n", config["Project Name"].as<std::string>());

            cmake << "\n";

            cmake << "include(FetchContent)\n";

            cmake << "\n";

            const YAML::Node deps = config["Dependencies"];

            const std::regex pattern("(.+?)==(.+?)");
            int numDeps = deps.size();
            for (int i = 0; i < numDeps; i++) {
                std::smatch matches;
                std::string target = deps[i].as<std::string>();
                std::string targetVer = "latest";

                if (std::regex_match(target, matches, pattern)) {
                    target = matches[1];
                    targetVer = matches[2];
                }

                cmake << std::format("FetchContent_Declare(Lib{}\n", i);
                cmake << std::format("\tGIT_REPOSITORY {}\n", target);
                if (targetVer != "latest") {
                    cmake << std::format("\tGIT_TAG {}\n", targetVer);
                }
                cmake << ")\n";
                cmake << std::format("FetchContent_MakeAvailable(Lib{})\n", i);
            }

            cmake << "\n";

            cmake << "include_directories(\"${CMAKE_SOURCE_DIR}/include\")\n";
            cmake << "file(GLOB_RECURSE SOURCES \"${CMAKE_SOURCE_DIR}/src/*.cpp\")\n";
            cmake << std::format("add_executable({} \"${{SOURCES}}\")\n", config["Executable Name"].as<std::string>());

            cmake << "\n";

            for (int i = 0; i < numDeps; i++) {
                cmake << std::format("target_link_libraries({} PRIVATE Lib{})\n", config["Project Name"].as<std::string>(), i);
            }

            cmake << "\n";

            cmake << std::format("set_property(TARGET {} PROPERTY CXX_STANDARD {})\n", config["Executable Name"].as<std::string>(), config["CXX Standard"].as<std::string>());
            cmake.close();

            logger.info("Successfully generated CMakeLists.txt");
        } else {
            logger.fatal("Failed to create CMakeLists.txt");
            return -1;
        }
    } else {
        return -1;
    }
    return 0;
}

/// Note: Does not actually use the arguments
int init(const std::vector<std::string>& args) {
    YAML::Node config;
    config["Project Name"] = "myProject";
    config["Executable Name"] = "myExecutable";
    config["CXX Standard"] = "20";
    config["CMake Version"] = "3.18";
    config["Dependencies"] = YAML::Node();
    std::ofstream ostream("cradle.yaml");
    if (ostream.good()) {
        ostream << config;
        ostream.close();
        logger.info("Successfully created cradle.yaml");
        build(args);
    } else {
        logger.fatal("Failed to create cradle.yaml");
        return -1;
    }
    return 0;
}

int install(const std::vector<std::string>& args) {
    if (initCheck()) {
        YAML::Node config = YAML::LoadFile("cradle.yaml");

        const std::regex pattern("(.+?)==(.+?)");
        std::smatch matches;

        std::string target = args[2];
        std::string targetVer = "latest";
        if (std::regex_match(target, matches, pattern)) {
            target = matches[1];
            targetVer = matches[2];
        }

        bool duplicate = false;

        for (const YAML::Node node : config["Dependencies"]) {
            matches = std::smatch();
            std::string lib = node.as<std::string>();
            if (std::regex_match(lib, matches, pattern)) {
                if (matches[1] == target) {
                    if (matches[2] == targetVer) {
                        duplicate = true;
                        logger.warn(std::format("Dependency {}=={} is already installed", target, targetVer));
                    }
                }
            }
        }

        if (!duplicate) {
            config["Dependencies"].push_back(std::format("{}=={}", target, targetVer));
            logger.info(std::format("Dependency {}=={} installed", target, targetVer));
        }

        std::ofstream ostream("cradle.yaml");
        if (ostream.good()) {
            ostream << config;
            ostream.close();
        } else {
            logger.fatal("Failed to update cradle.yaml");
            return -1;
        }

        build(args);
    } else {
        return -1;
    }
    return 0;
}

int uninstall(const std::vector<std::string>& args) {
    if (initCheck()) {
        YAML::Node config = YAML::LoadFile("cradle.yaml");

        const std::regex pattern("(.+?)==(.+?)");
        std::smatch matches;

        std::string target = args[2];
        if (std::regex_match(target, matches, pattern)) {
            target = matches[1];
        }

        bool exists = false;

        YAML::Node deps = config["Dependencies"];

        for (int i = 0; i < deps.size(); i++) {
            YAML::Node node = deps[i];
            std::string lib = node.as<std::string>();
            if (std::regex_match(lib, matches, pattern)) {
                if (matches[1] == target) {
                    config["Dependencies"].remove(i);
                    exists = true;
                    logger.info(std::format("Dependency {} uninstalled", target));
                    break;
                }
            }
        }

        if (!exists) {
            logger.warn(std::format("Dependency {} not installed", target));
        }

        std::ofstream ostream("cradle.yaml");
        if (ostream.good()) {
            ostream << config;
            ostream.close();
        } else {
            logger.fatal("Failed to update cradle.yaml");
            return -1;
        }

        build(args);
    } else {
        return -1;
    }
    return 0;
}

int main(int argc, char** argv) {
    std::vector<std::string> tokens(argv, argv + argc);

    std::unordered_map<std::string, std::function<int(const std::vector<std::string>&)>> registry;
    registry["init"] = &init;
    registry["install"] = &install;
    registry["build"] = &build;
    registry["uninstall"] = &uninstall;

    if (argc > 1) {
        std::string command = tokens[1];
        if (registry.contains(command)) {
            int code = registry[command](tokens);
            return code;
        } else {
            logger.fatal("Command not found");
        }
    } else {
        logger.fatal("No command given");
        return -1;
    }
    return 0;
}