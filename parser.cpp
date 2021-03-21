#include "parser.h"

Parser::Parser(const std::string& filename) :
    m_filename(filename),
    m_file(m_filename),
    m_delimiter(';')
{
    // Ignore first two lines
    if (m_file.is_open()) {
        ignoreLine();
        ignoreLine();
    }
}

bool Parser::parseLine(Football::Player& player)
{
    if (!m_file.is_open()) {
        return false;
    }

    std::string s;
    // Line format: Id; R; Nome; Squadra; Qt.A; Qt.I; Diff.

    // id
    if (getline(m_file, s, m_delimiter).eof()) {  // Check if it has read the en of the file
        return false;
    }
    player.id(std::stoi(s));

    // Role
    if (getline(m_file, s, m_delimiter).eof()) {
        return false;
    }
    player.role(Football::Player::strToRole(s));

    // Name
    if (getline(m_file, s, m_delimiter).eof()) {
        return false;
    }
    player.name(s);

    // Team
    if (getline(m_file, s, m_delimiter).eof()) {
        return false;
    }
    player.team(s);

    // actual value
    if (getline(m_file, s, m_delimiter).eof()) {
        return false;
    }
    player.actualValue(std::stod(s));

    // initial value
    if (getline(m_file, s, m_delimiter).eof()) {
        return false;
    }
    player.initialValue(std::stod(s));

    // diff value
    if (getline(m_file, s, '\n').eof()) {
        return false;
    }
    player.diffValue(std::stod(s));

    return true;
}


void Parser::ignoreLine()
{
    std::string s;
    if (m_file.is_open()) {
        getline(m_file, s, '\n');
    }
}
