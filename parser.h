#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>
#include "player.h"

class Parser
{
public:
    Parser(const std::string&);

    bool parseLine(Football::Player&);

private:
    Parser();
    std::string m_filename;
    std::ifstream m_file;
    char m_delimiter;

    void ignoreLine();
};

#endif // PARSER_H
