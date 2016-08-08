#include "WebsiteCompiler.h"


bool WebsiteCompiler::compile(std::string directory) {
    /* Load files that are needed */
    ResourceManager::load(directory + "/site.json");
    ResourceManager::load("src/shards/html.html");
    ResourceManager::load("src/shards/style.css");

    std::string html_text = ResourceManager::get("src/shards/html.html");
    std::string css_text = ResourceManager::get("src/shards/style.css");

    /* Load site json */
    nlohmann::json site = nlohmann::json::parse(ResourceManager::get(directory + "/site.json"));
    std::cout << "Found Website: " << site["title"] << std::endl;

    /* Load font json from site json */
    ResourceManager::load(directory + "/" + site["font"].get<std::string>());
    nlohmann::json font = nlohmann::json::parse(ResourceManager::get(directory + "/" + site["font"].get<std::string>()));

    /* Add css to header */
    ResourceManager::write("src/shards/html.html", WebsiteCompiler::replace_word(
            ResourceManager::get("src/shards/html.html"),
            "{{head}}",
            "\
            <link rel='stylesheet' type='text/css' href='style.css'>\n\
            {{head}}\
            "
            ));

    /* Add font to header */
    ResourceManager::write("src/shards/html.html", WebsiteCompiler::replace_word(
            ResourceManager::get("src/shards/html.html"),
            "{{head}}",
            "\
            <link rel='stylesheet' type='text/css' href='" + font["link"].get<std::string>() + "'>\n\
            {{head}}\
            "
            ));

    /* Add font to css */
    ResourceManager::write("src/shards/style.css", WebsiteCompiler::replace_word(
            ResourceManager::get("src/shards/style.css"),
            "{{family}}",
            font["family"].get<std::string>()
            ));
    ResourceManager::write("src/shards/style.css", WebsiteCompiler::replace_word(
            ResourceManager::get("src/shards/style.css"),
            "{{fallback-family}}",
            font["fallback-family"].get<std::string>()
            ));

    /* Create project directory using title in site.json */
    mkdir(site["title"].get<std::string>().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    
    /* Create and write pages */
    std::vector<std::string> pages = site["pages"].get<std::vector<std::string>>();
    for(auto i : pages) {
        ResourceManager::write_new(
                site["title"].get<std::string>() + "/" + WebsiteCompiler::replace_word(i, ".json", ".html"),
                ResourceManager::get("src/shards/html.html")
                ); 
    }

    /* Write css file */
    ResourceManager::write_new(
                site["title"].get<std::string>() + "/style.css",
                ResourceManager::get("src/shards/style.css")
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
