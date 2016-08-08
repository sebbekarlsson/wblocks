#include "WebsiteCompiler.h"


bool WebsiteCompiler::compile(Website * website) {
    website->addHeaderElement(
            "<link rel='stylesheet' type='text/css' href='style.css'>"
            );
    website->addHeaderElement(
            "<link rel='stylesheet' type='text/css' href='"\
            + website->font["link"].get<std::string>() + "'>"
            );

    website->generatePages();
    website->generateCSS();

    return true;
}

std::string WebsiteCompiler::replace_word(std::string text, std::string word, std::string replacement) {
    size_t start_pos = text.find(word);
    if(start_pos == std::string::npos)
        return text;
    text.replace(start_pos, word.length(), replacement);

    return text;
}
