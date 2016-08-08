#ifndef WEBSITECOMPILER_H
#define WEBSITECOMPILER_H
#include <iostream>
#include <string>
#include "json/src/json.hpp"
#include "ResourceManager/ResourceManager.h"
#include "Website.h"


class WebsiteCompiler {
    public:
        static bool compile(Website * website);
        static std::string replace_word(std::string text, std::string word, std::string replacement);
};

#endif
