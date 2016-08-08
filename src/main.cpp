#include "WebsiteCompiler.h"
#include "Website.h"
#include <string>


int main(int argc, char* argv[]) {
    WebsiteCompiler::compile(new Website(std::string(argv[1])));
    return 0;
}
