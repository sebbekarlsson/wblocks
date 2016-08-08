#include "WebsiteCompiler.h"


bool WebsiteCompiler::compile(std::string directory) {
    /* Define paths */
    std::string html_path = "src/shards/html.html";
    std::string css_path = "src/shards/style.css";

    /* Load files that are needed */
    ResourceManager::load(directory + "/site.json");
    ResourceManager::load(html_path);
    ResourceManager::load(css_path);

    /* Load site json */
    nlohmann::json site = nlohmann::json::parse(ResourceManager::get(directory + "/site.json"));
    std::cout << "Found Website: " << site["title"] << std::endl;

    /* Load font json from site json */
    ResourceManager::load(directory + "/" + site["font"].get<std::string>());
    nlohmann::json font = nlohmann::json::parse(ResourceManager::get(directory + "/" + site["font"].get<std::string>()));

    /* Add css to header */
    ResourceManager::write(html_path, WebsiteCompiler::replace_word(
            ResourceManager::get(html_path),
            "{{head}}",
            "\
            <link rel='stylesheet' type='text/css' href='style.css'>\n\
            {{head}}\
            "
            ));

    /* Add font to header */
    ResourceManager::write(html_path, WebsiteCompiler::replace_word(
            ResourceManager::get(html_path),
            "{{head}}",
            "\
            <link rel='stylesheet' type='text/css' href='" + font["link"].get<std::string>() + "'>\n\
            {{head}}\
            "
            ));

    /* Add font to css */
    ResourceManager::write(css_path, WebsiteCompiler::replace_word(
            ResourceManager::get(css_path),
            "{{family}}",
            font["family"].get<std::string>()
            ));

    ResourceManager::write(css_path, WebsiteCompiler::replace_word(
            ResourceManager::get(css_path),
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
                ResourceManager::get(html_path)
                ); 
    }

    /* Write css file */
    ResourceManager::write_new(
                site["title"].get<std::string>() + "/style.css",
                ResourceManager::get(css_path)
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
