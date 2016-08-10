#include "Website.h"
#include <string>


void printAvailableCommands(std::map<std::string, int> commands) {
    std::cout << "Available commands:" << std::endl;
    for(auto const &ent1 : commands) {
        std::cout << "- " << ent1.first << std::endl;
    }
}

int main(int argc, char* argv[]) {
    std::map<std::string, int> commands;
    commands["compile"] = 1;
    commands["install"] = 2;

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
                }
                return 0;
            }
        break;
    }

    std::cout << "Command not found" << std::endl;
    return 0;
}
