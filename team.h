#ifndef TEAM_H
#define TEAM_H

#include <string>
#include <vector>

#include "player.h"


namespace Fantasy {

class Team
{
public:
    Team(const std::string&, int);

    void buyPlayer(std::shared_ptr<Football::Player>, int);
    void sellPlayer(std::shared_ptr<Football::Player>, int);
    int maxOffer() const; // return the max legal offer during the auction

    // getters
    std::string name() const { return m_name; }
    //const std::vector<Football::Player>& players() const { return *m_players; }
    int money() const { return m_money; }

    int numByRole(Football::Player::Role) const;

    int maxNumGoalkeepers() const { return m_maxNumGoalkeepers; }
    int maxNumDefenders() const { return m_maxNumDefenders; }
    int maxNumMidfielders() const { return m_maxNumMidfielders; }
    int maxNumForwards() const { return m_maxNumForwards; }


private:
    Team();

    std::string m_name;

    typedef std::weak_ptr<Football::Player> player_wptr;
    std::vector<player_wptr> m_players;

    int m_money;

    const int m_maxNumGoalkeepers = 3;
    const int m_maxNumDefenders   = 8;
    const int m_maxNumMidfielders = 8;
    const int m_maxNumForwards    = 6;
};

}

#endif // TEAM_H
