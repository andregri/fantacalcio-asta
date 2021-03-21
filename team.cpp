#include "team.h"

#include <algorithm>

namespace Fantasy {

Team::Team(const std::string& name, int money) :
    m_name(name),
    m_money(money)
{

}

void Team::buyPlayer(const std::shared_ptr<Football::Player>& player, int cost)
{
    if (m_money - cost < 0) {
        throw m_name + " cannot afford to buy " + player->name();
    }
    auto new_player = std::weak_ptr<Football::Player>(player);
    m_players.push_back(new_player);
    m_money -= cost;
}

void Team::sellPlayer(const std::shared_ptr<Football::Player>& player, int value)
{
    auto removed_it = std::remove_if(m_players.begin(), m_players.end(), [player](const player_wptr& weak_ptr){
        auto shared_ptr = weak_ptr.lock();
        return player.get() == shared_ptr.get();
    });
    if (removed_it != m_players.end()) {
        m_money += value;
    }
}

int Team::maxOffer() const
{
    int maxNumPlayers = m_maxNumGoalkeepers +
            m_maxNumDefenders +
            m_maxNumMidfielders +
            m_maxNumForwards;

    int numPlayersToBuy = maxNumPlayers - m_players.size();

    int max_offer = m_money - numPlayersToBuy + 1;
    return max_offer;
}

int Team::numByRole(Football::Player::Role role) const
{
    return std::count_if(m_players.begin(), m_players.end(), [role](const player_wptr& player){
        auto p = player.lock();
        return p->role() == role;
    });
}

}
