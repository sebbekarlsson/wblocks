#include "Website.h"
#include <string>


int main(int argc, char* argv[]) {
    Website * website = new Website(std::string(argv[1]));

    website->addHeaderElement(
            "<link rel='stylesheet' type='text/css' href='style.css'>"
            );
    website->addHeaderElement(
            "<link rel='stylesheet' type='text/css' href='"\
            + website->font["link"].get<std::string>() + "'>"
            );

    website->generatePages();
    website->generateCSS();

    return 0;
}
