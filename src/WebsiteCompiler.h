#include <iostream>
#include <string>
#include "json/src/json.hpp"
#include "ResourceManager/ResourceManager.h"
#include <sys/stat.h>
#include <sys/types.h>


#ifndef WEBSITECOMPILER_H
#define WEBSITECOMPILER_H

class WebsiteCompiler {
    public:
        static bool compile(std::string directory);
    private:
        static std::string replace_word(std::string text, std::string word, std::string replacement);
};

#endif
