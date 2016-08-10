#include "Website.h"
#include "PackageManager.h"
#include "ResourceManager/ResourceManager.h"
#include <string>


void printAvailableCommands(std::map<std::string, int> commands) {
    std::cout << "Available commands:" << std::endl;
    for(auto const &ent1 : commands) {
        std::cout << "- " << ent1.first << std::endl;
    }
}

void generateBoilerPlate(std::string directory) {
    std::cout << "[Boilerplating]: Gathering templates..." << std::endl;
    ResourceManager::load("/etc/websitecompiler/shards/site.json");
    ResourceManager::load("/etc/websitecompiler/shards/index.json");
    ResourceManager::load("/etc/websitecompiler/shards/fonts/lato.json");
    ResourceManager::load("/etc/websitecompiler/shards/modules/hero/module.css");
    ResourceManager::load("/etc/websitecompiler/shards/modules/hero/module.html");

    std::cout << "[Boilerplating]: Creating directories..." << std::endl;
    mkdir(
            directory.c_str(),
            S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH
         );
    mkdir(
            (directory + "/fonts").c_str(),
            S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH
         );
    mkdir(
            (directory + "/modules").c_str(),
            S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH
         );
    mkdir(
            (directory + "/modules/hero").c_str(),
            S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH
         );

    std::cout << "[Boilerplating]: Writing boilerplate files..." << std::endl;
    ResourceManager::write_new(directory + "/site.json",
            ResourceManager::get("/etc/websitecompiler/shards/site.json"));
    ResourceManager::write_new(directory + "/index.json",
            ResourceManager::get("/etc/websitecompiler/shards/index.json"));

    ResourceManager::write_new(directory + "/fonts/lato.json",
            ResourceManager::get("/etc/websitecompiler/shards/fonts/lato.json"));

    ResourceManager::write_new(directory + "/modules/hero/module.css",
            ResourceManager::get("/etc/websitecompiler/shards/modules/hero/module.css"));
    ResourceManager::write_new(directory + "/modules/hero/module.html",
            ResourceManager::get("/etc/websitecompiler/shards/modules/hero/module.html"));

    std::cout << "[Boilerplating]: Done! > " << directory << std::endl;
}

int main(int argc, char* argv[]) {
    std::map<std::string, int> commands;
    commands["compile"] = 1;
    commands["install"] = 2;
    commands["boil"] = 3;

    if(argc < 2) {
        std::cout << "No command was specified" << std::endl;
        std::cout << "Usage: websitecompiler <command>\n" << std::endl;
        printAvailableCommands(commands);
        return 0;
    }

    switch (commands[argv[1]]) {
        case 1:
            {
                if (argc < 3) {
                    std::cout << "No directory was specified" << std::endl;
                    std::cout << "Usage: websitecompiler compile <directory>" << std::endl;
                    return 0;
                }

                Website * website = new Website(std::string(argv[2]));
                website->compile();
                return 0;
            }
        break;
        case 2:
            {
                if (argc < 3) {
                    std::cout << "No module was specified" << std::endl;
                    std::cout << "Usage: websitecompiler install <module>" << std::endl;
                    return 0;
                }

                PackageManager* packagemanager = new PackageManager();
                packagemanager->downloadPackage(argv[2]);
                return 0;
            }
        break;
        case 3:
            {
                if (argc < 3) {
                    std::cout << "No directory was specified" << std::endl;
                    std::cout << "Usage: websitecompiler boil <directory>" << std::endl;
                    return 0;
                }

                generateBoilerPlate(argv[2]);
                return 0;
            }
        break;
    }

    std::cout << "Command not found" << std::endl;
    return 0;
}
