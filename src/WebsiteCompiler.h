#include <iostream>
#include <string>
#include "json/src/json.hpp"
#include "ResourceManager/ResourceManager.h"


#ifndef WEBSITECOMPILER_H
#define WEBSITECOMPILER_H

class WebsiteCompiler {
    public:
        static bool compile(std::string directory);
};

#endif
