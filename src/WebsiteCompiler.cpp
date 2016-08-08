#include "WebsiteCompiler.h"


bool WebsiteCompiler::compile(std::string directory) {
    ResourceManager::load(directory + "/site.json");
    nlohmann::json site = nlohmann::json::parse(ResourceManager::get(directory + "/site.json"));
    
    std::cout << "Found Website: " << site["title"] << std::endl; 
    return true;
}
