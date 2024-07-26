#pragma once

#include "module/ModuleManager.h"

class ModuleWriter {
   private:
    std::string path;

   public:
    ModuleWriter(const std::string& path);
    ModuleWriter& write(ModuleManager& manager);
};