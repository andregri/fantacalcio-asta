#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>

#include <vector>
#include <memory>

#include "team.h"
#include "player.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnLoadCsv_clicked();

    void on_checkBox_goalkeeper_toggled(bool checked);

    void on_checkBox_defender_toggled(bool checked);

    void on_checkBox_midfield_toggled(bool checked);

    void on_checkBox_forward_toggled(bool checked);

    void on_comboBox_teams_activated(const QString &arg1);

    void on_lineEdit_playerName_returnPressed();

    void on_lineEdit_playerName_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;

    typedef std::shared_ptr<Football::Player> player_sptr;
    std::vector<player_sptr> m_players;

    typedef std::shared_ptr<Fantasy::Team> team_sptr;
    std::vector<team_sptr> m_teams;
    void initTeams();

    // Players quotations table
    enum class TABLE_PLAYER_COLUMN { id, role, name, team, actual_value, initial_value, diff_value };
    void initPlayersTableHeaders();
    void addPlayerRow(const Football::Player& player, bool hidden);

    // Teams combo box
    std::vector<std::string> m_real_teams; // list of team names in the real championship
    void initTeamsComboBox();

    // Filters: return true if row SHOULD be hidden
    enum class TABLE_TEAM_COLUMN { name, money, max_offer, num_gk, num_def, num_mid, num_for };
    bool filterByRole(Football::Player::Role);
    bool filterByTeam(const std::string&);
    bool filterByName(const std::string&);
    bool filter(int row);

    // Teams table
    void initTeamsTableHeaders();
    void initTeamsTable();
    void addTeamRow(const Fantasy::Team&);
};

#endif // MAINWINDOW_H
