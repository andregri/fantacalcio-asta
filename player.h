#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <memory>


namespace Football
{

class Player
{
public:
    enum class Role {unknown, goalkeeper, defender, midfield, forward};

    Player();

    Player(std::string name, std::string team, double actual_value,
           double initial_value, double diff_value, int id, Role role);

    // Getters and Setters
    void name(const std::string& name) { m_name = name; }
    std::string name() const { return m_name; }

    void team(const std::string& team) { m_team = team; }
    std::string team() const { return m_team; }

    void actualValue(double v) { m_actualValue = v; }
    double actualValue() const { return m_actualValue; }

    void initialValue(double v) { m_initialValue = v; }
    double initialValue() const { return m_initialValue; }

    void diffValue(double v) { m_diffValue = v; }
    double diffValue() const { return m_diffValue; }

    void id(int id) { m_id = id; }
    int id() const { return m_id; }

    void role(Role r) { m_role = r; }
    Role role() const { return m_role; }

    void available(bool value) { m_available = true; }
    bool available() const { return m_available; }

    // Utilities
    static Role strToRole(const std::string&);
    static std::string roleToStr(Role);

private:
    std::string m_name;
    std::string m_team;
    double m_actualValue;
    double m_initialValue;
    double m_diffValue;
    int m_id;
    Role m_role;
    bool m_available;
};

}

#endif // PLAYER_H
