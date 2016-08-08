#include "WebsiteCompiler.h"


bool WebsiteCompiler::compile(std::string directory) {
    ResourceManager::load(directory + "/site.json");
    ResourceManager::load("src/shards/html.html");

    nlohmann::json site = nlohmann::json::parse(ResourceManager::get(directory + "/site.json"));

    std::cout << "Found Website: " << site["title"] << std::endl;

    mkdir(site["title"].get<std::string>().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    std::vector<std::string> pages = site["pages"].get<std::vector<std::string>>();

    for(auto i : pages) {
        ResourceManager::write_new(
            site["title"].get<std::string>() + "/" + WebsiteCompiler::replace_word(i, ".json", ".html"),
            ResourceManager::get("src/shards/html.html")
            ); 
    }
     
    return true;
}

std::string WebsiteCompiler::replace_word(std::string text, std::string word, std::string replacement) {
    size_t start_pos = text.find(word);
    if(start_pos == std::string::npos)
        return "";
    text.replace(start_pos, word.length(), replacement);

    return text;
}
