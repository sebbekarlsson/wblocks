#include "Website.h"
#include <string>


int main(int argc, char* argv[]) {
    Website * website = new Website(std::string(argv[1]));
    
    website->compile();

    return 0;
}
