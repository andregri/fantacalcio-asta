#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
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

private:
    Ui::MainWindow *ui;

    // Players quotations table
    enum class TABLE_COLUMN { id, role, name, team, actual_value, initial_value, diff_value };
    void initTableHeaders();
    void addRow(const Player& player, bool hidden);
    bool isRoleVisible(Player::Role);

    // Teams combo box
    std::vector<std::string> m_real_teams; // list of team names in the real championship
    void initTeamsComboBox();
};

#endif // MAINWINDOW_H
