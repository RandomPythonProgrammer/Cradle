#pragma once

#include <string>
#include "module/ModuleManager.h"

class ModuleLoader {
   private:
    std::string path;
    public:
    ModuleLoader(const std::string& path);
    ModuleLoader& load(ModuleManager& manager);
};