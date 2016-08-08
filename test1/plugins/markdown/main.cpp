#include "Markdown.h"


int main(int argc, char* argv[]) {
    std::cout << Markdown::process(std::string("Hello There")) << std::endl;
    return 0;
} 
