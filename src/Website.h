#ifndef WEBSITE_H
#define WEBSITE_H
#include <vector>
#include <map>
#include "ResourceManager/ResourceManager.h"
#include "json/src/json.hpp"
#include <sys/stat.h>
#include <sys/types.h>
#include <regex>
#include <unistd.h>


class Website {
    public:
        nlohmann::json site;
        nlohmann::json font;
        std::string dir;
        std::string html;
        std::string css;
        std::string title;
        std::vector<std::string> header;
        std::map<std::string, std::string> pages;
        std::string family;
        std::string fallbackFamily;

        void addHeaderElement(std::string text);
        bool addPage(std::string title, std::string content);
        void generatePages();
        void generateCSS();
        void setFont(std::string family, std::string fallbackFamily, std::string link);
        void compile();
        std::string formatHTML(std::string html);
        std::string replace_word(std::string text, std::string word, std::string replacement);
        std::string jinjaFormat(std::string text, std::map<std::string, std::string> data);

        Website(std::string directory);
};

#endif
