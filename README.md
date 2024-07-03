# Cradle

This project CLI aims to simplify the process of creating and managing projects with CMake, especially when it comes to libraries. The program will automatically validate repo links and tag versions.

# Usage

## Setup
```
cradle init
```
This creates a `cradle.yaml` file that can be configured, generates a `CMakeLists.txt` file, and also creates `include` and `src` directories which are already linked.

## Generate
```
cradle build
```
This generates the `CMakeLists.txt` file based on the settings in the `cradle.yaml` file.

## Dependency Management
```
cradle install <repo>
```
This installs a library given the `repo` (`.git` repository link). To specify the version `==<git tag>` should be added after the repository link, the default is the latest version. This command will also try to remove other versions/duplicates. This will also run the `build` command to generate the `CMakeLists.txt` file.

```
cradle uninstall <repo|name>
```
This uninstalls a library given the `repo` (`.git` repository link) **or** the `name` of the library. This will remove all versions. This will also run the `build` command to generate the `CMakeLists.txt` file.
