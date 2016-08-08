#include "WebsiteCompiler.h"


bool WebsiteCompiler::compile(Website * website) {
    website->addHeaderElement(
            "<link rel='stylesheet' type='text/css' href='style.css'>"
            );
    website->addHeaderElement(
            "<link rel='stylesheet' type='text/css' href='"\
            + website->font["link"].get<std::string>() + "'>"
            );

    std::vector<std::string> pages = website->site["pages"].get<std::vector<std::string>>();
    for(auto i : pages) {
        website->pages[
            WebsiteCompiler::replace_word(i, ".json", "")
        ] = website->html;
    }


    website->generatePages();

    /* Write css file */
    ResourceManager::write_new(
            website->site["title"].get<std::string>() + "/style.css",
            website->css
            );

    return true;
}

std::string WebsiteCompiler::replace_word(std::string text, std::string word, std::string replacement) {
    size_t start_pos = text.find(word);
    if(start_pos == std::string::npos)
        return "";
    text.replace(start_pos, word.length(), replacement);

    return text;
}
