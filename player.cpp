#include "player.h"

namespace Football
{

Player::Player() :
    Player("", "", 0.0f, 0.0f, 0.0f, -1, Role::unknown)
{

}

Player::Player(std::string name, std::string team, double actual_value, double initial_value, double diff_value, int id, Role role) :
    m_name(name),
    m_team(team),
    m_actualValue(actual_value),
    m_initialValue(initial_value),
    m_diffValue(diff_value),
    m_id(id),
    m_role(role),
    m_available(true)
{

}

Player::Role Player::strToRole(const std::string& strRole)
{
    if (strRole == "P") {
        return Role::goalkeeper;
    }
    else if (strRole == "D") {
        return Role::defender;
    }
    else if (strRole == "C") {
        return Role::midfield;
    }
    else if (strRole == "A") {
        return Role::forward;
    }
    else {
        return Role::unknown;
    }
}

std::string Player::roleToStr(Role role)
{
    switch (role) {
    case Role::goalkeeper:
        return "P";
    case Role::defender:
        return "D";
    case Role::midfield:
        return "C";
    case Role::forward:
        return "A";
    default:
        return "";
    }
}

}
