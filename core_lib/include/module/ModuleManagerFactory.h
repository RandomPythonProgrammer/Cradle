#pragma once

#include "module/ModuleManager.h"

class ModuleManagerFactory {
   public:
    static ModuleManager* createModuleManager();
};