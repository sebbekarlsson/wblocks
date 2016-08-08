#include <iostream>
#include <string>


#ifndef MARKDOWN_H
#define MARKDOWN_H

class HTMLProcessor {};

class Markdown: public HTMLProcessor {
    public:
        static std::string process (std::string html);
};

#endif
