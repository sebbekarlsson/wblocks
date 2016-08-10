#include "Website.h"


Website::Website(std::string directory) {
    this->dir = directory;

    ResourceManager::load(this->dir + "/site.json");
    this->site = nlohmann::json::parse(ResourceManager::get(this->dir + "/site.json"));

    std::cout << "[Initializing]: Creating directory: " << this->site["title"].get<std::string>() << std::endl;
    mkdir(
            this->site["title"].get<std::string>().c_str(),
            S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH
         );
    mkdir(
            this->site["title"].get<std::string>().append("/images").c_str(),
            S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH
         );

    /* move files from images to new images location */
    std::cout << "[Initializing]: Moving images: " << std::endl;
    DIR *dpdf;
    struct dirent *epdf;
    dpdf = opendir((this->dir + "/images").c_str());
    if (dpdf != NULL){
        while (epdf = readdir(dpdf)){
            std::ifstream  src(this->dir + "/images/" + epdf->d_name, std::ios::binary);
            std::ofstream  dst(this->site["title"].get<std::string>() + "/images/" + epdf->d_name,   std::ios::binary);
            dst << src.rdbuf();
        }
    }
    closedir(dpdf);

    ResourceManager::load("/etc/websitecompiler/shards/html.html");
    ResourceManager::load("/etc/websitecompiler/shards/style.css");
    ResourceManager::load(this->dir + "/" + this->site["font"].get<std::string>());

    this->title = this->site["title"].get<std::string>(); 
    this->html = ResourceManager::get("/etc/websitecompiler/shards/html.html");
    this->css = ResourceManager::get("/etc/websitecompiler/shards/style.css");
    this->font = nlohmann::json::parse(ResourceManager::get(this->dir + "/" + this->site["font"].get<std::string>()));

    std::vector<std::string> _pages = this->site["pages"].get<std::vector<std::string>>();
    for(auto i : _pages) {
        if (!ResourceManager::fileExists(this->dir + "/" + i)) { continue; }
        ResourceManager::load(this->dir + "/" + i);
        if (
                ResourceManager::get(this->dir + "/" + i).empty() ||
                ResourceManager::get(this->dir + "/" + i) == ""
           ) { continue; }
        this->pages[
            this->replace_word(i, ".json", "")
        ] = ResourceManager::get(this->dir + "/" + i);
    }

    this->setFont(
            this->font["family"].get<std::string>(),
            this->font["fallback-family"].get<std::string>(),
            this->font["link"].get<std::string>()
            );
}

/**
 * Add element to the header.
 *
 * @param String text
 */
void Website::addHeaderElement(std::string text) {
    this->header.push_back(text);
}

/**
 * Set the font of the website.
 *
 * @param String family
 * @param String fallbackFamily
 * @param String link
 */
void Website::setFont(std::string family, std::string fallbackFamily, std::string link) {
    this->family = family;
    this->fallbackFamily = fallbackFamily;
    this->addHeaderElement(
            "<link rel='stylesheet' type='text/css' href='"\
            + link + "'>"
            );
    this->css = this->replace_word(this->css, "{{family}}", this->family);
    this->css = this->replace_word(this->css, "{{fallback-family}}", this->fallbackFamily);
}

/**
 * Add a page to the website.
 *
 * @param String title
 * @param String content
 */
bool Website::addPage(std::string title, std::string content) {
    this->pages.insert(std::pair<std::string, std::string>(title, content));
}

/**
 * Generate all pages into physical files.
 */
void Website::generatePages() {
    const std::regex r("\\{\\{(.*)}}");

    this->addHeaderElement(
            "<link rel='stylesheet' type='text/css' href='style.css'>"
            );
    this->addHeaderElement(
            "<meta name='viewport' content='width=device-width, initial-scale=1'>"
            );
    this->addHeaderElement(
            "<meta charset='UTF-8'>"
            );

    for(auto const &ent1 : pages) {
        //std::cout << ent1.first << std::endl;
        //std::cout << pages.at(ent1.first) << std::endl;
        std::cout << "[Generating Page]: " << ent1.first << std::endl;

        std::string page_content = "";
        nlohmann::json page_json = nlohmann::json::parse(pages.at(ent1.first));

        for(auto i : page_json["sections"]) {
            for (auto ii : i["children"]) {
                if (ii["type"].get<std::string>() == "module") {
                    std::string module_html_path = this->dir + "/" + ii["source"].get<std::string>() + "/" + "module.html";
                    std::string module_css_path = this->dir + "/" + ii["source"].get<std::string>() + "/" + "module.css";

                    ResourceManager::load(module_html_path);
                    ResourceManager::load(module_css_path);

                    std::string module_html = ResourceManager::get(module_html_path);
                    std::string module_css = ResourceManager::get(module_css_path);

                    std::smatch sm;
                    if (regex_search(module_html, sm, r)){
                        for (int i=1; i<sm.size(); i++){
                            for (auto iz : ii["args"]) {
                                for (auto it = iz.begin(); it != iz.end(); ++it) {
                                    std::string v = it.value();
                                    if (v.find("{{") != std::string::npos) {
                                        v = this->replace_word(v, "{{", "");
                                        v = this->replace_word(v, "}}", "");
                                        ResourceManager::load(this->dir + "/" + v);
                                        v = ResourceManager::get(this->dir + "/" + v);
                                    }

                                    std::cout << "[Generating Page]: " << ent1.first << " " << it.key() << ": " << v << std::endl;
                                    module_html = this->replace_word(module_html, "{{"+it.key()+"}}", v);
                                }
                            }
                        }
                    }

                    this->css += "\n" + module_css;

                    page_content += "<section>\n" + module_html + "</section>\n";
                }
            }
        }

        ResourceManager::write_new(this->title + "/" + ent1.first + ".html",
                this->replace_word(this->formatHTML(this->html), "{{body}}", page_content)
                );
    }
}

/**
 * Generete the physical CSS file.
 */
void Website::generateCSS() {
    ResourceManager::write_new(
            this->site["title"].get<std::string>() + "/style.css",
            this->css
            );
}

/**
 * Format page HTML, adding the header etc.
 *
 * @param String _html
 */
std::string Website::formatHTML(std::string _html) {
    std::string header_final = "";
    for(auto i : header) {
        header_final += i + "\n"; 
    }

    return this->replace_word(_html, "{{head}}", header_final);
}

/**
 * Replace a word in a String with another word
 */
std::string Website::replace_word(std::string text, std::string word, std::string replacement) {
    size_t start_pos = text.find(word);
    if(start_pos == std::string::npos)
        return text;
    text.replace(start_pos, word.length(), replacement);

    return text;
}

/**
 * Create the physical website.
 * This function is a wrapper that does all the necessary steps to "compile"
 * the website.
 */
void Website::compile() {
    this->generatePages();
    this->generateCSS();
}
