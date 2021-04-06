#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

#include <algorithm>

#include "parser.h"
#include "qtablenumberitem.h"
#include "buyplayerdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Fantacalcio Manager");

    // Teams table
    initFantasyTeams();
    initTeamsTableHeaders();
    initTeamsTable();

    // Load button
    ui->btnLoadCsv->setToolTip("Select the file with the players quotations");

    // Quotations table
    initPlayersTableHeaders();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Load the csv file of quotations in the table
void MainWindow::on_btnLoadCsv_clicked()
{
    // Browse the csv file
    QString filename = QFileDialog::getOpenFileName(this, tr("Select quotation file"), QDir::currentPath(), tr("csv files (*.csv)"));

    // Parse the csv file
    Parser parser(filename.toStdString());

    // Populate the table
    Football::Player player;
    while (parser.parseLine(player)) {
        // add team name to the list
        std::string team = player.team();
        if ( std::find(m_real_teams.begin(), m_real_teams.end(), team) == m_real_teams.end() ) {
            m_real_teams.push_back(team);
        }

        // add player to the vector
        player_sptr player_p( new Football::Player(player) );
        m_players.push_back( player_p );

        // add row to the table
        addPlayerRow(player, false);

        // set row hidden or visible based on filters
        int row = ui->tablePlayersValues->rowCount() - 1;
        bool hidden = filter(row);
        ui->tablePlayersValues->setRowHidden(row, hidden);
    }

    initTeamsComboBox();

    ui->tablePlayersValues->resizeColumnsToContents();
    ui->tablePlayersValues->setSortingEnabled(true);
}

void MainWindow::initPlayersTableHeaders()
{
    auto p_table = ui->tablePlayersValues;

    // Set columns number
    p_table->setColumnCount(7);

    // set horizontal header
    QStringList tableHorizontalHeader {"ID", "Role", "Name", "Team", "Actual Value", "Initial Value", "Difference"};
    p_table->setHorizontalHeaderLabels(tableHorizontalHeader);

    // hide vertical header
    //p_table->verticalHeader()->setVisible(false);

    // Disable editing
    p_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::addPlayerRow(const Football::Player& player, bool hidden)
{
    auto p_table = ui->tablePlayersValues;

    // append an empty row
    p_table->insertRow(p_table->rowCount());

    int row = p_table->rowCount() - 1;

    // Populate the row
    int id = player.id();
    QString role = QString(Football::Player::roleToStr(player.role()).c_str());
    QString name = QString(player.name().c_str());
    QString team = QString(player.team().c_str());
    double actualValue = player.actualValue();
    double initialValue = player.initialValue();
    double diffValue = player.diffValue();

    p_table->setItem(row, int(TABLE_PLAYER_COLUMN::id), new QTableNumberItem(id));
    p_table->setItem(row, int(TABLE_PLAYER_COLUMN::role), new QTableWidgetItem(role));
    p_table->setItem(row, int(TABLE_PLAYER_COLUMN::name), new QTableWidgetItem(name));
    p_table->setItem(row, int(TABLE_PLAYER_COLUMN::team), new QTableWidgetItem(team));
    p_table->setItem(row, int(TABLE_PLAYER_COLUMN::actual_value), new QTableNumberItem(actualValue));
    p_table->setItem(row, int(TABLE_PLAYER_COLUMN::initial_value), new QTableNumberItem(initialValue));
    p_table->setItem(row, int(TABLE_PLAYER_COLUMN::diff_value), new QTableNumberItem(diffValue));

    p_table->setRowHidden(row, hidden);
}

void MainWindow::updatePlayersTableBgColorRow(int row)
{
    auto p_table = ui->tablePlayersValues;

    p_table->item(row, int(TABLE_PLAYER_COLUMN::id))->setBackgroundColor(Qt::red);
    p_table->item(row, int(TABLE_PLAYER_COLUMN::role))->setBackgroundColor(Qt::red);
    p_table->item(row, int(TABLE_PLAYER_COLUMN::name))->setBackgroundColor(Qt::red);
    p_table->item(row, int(TABLE_PLAYER_COLUMN::team))->setBackgroundColor(Qt::red);
    p_table->item(row, int(TABLE_PLAYER_COLUMN::actual_value))->setBackgroundColor(Qt::red);
    p_table->item(row, int(TABLE_PLAYER_COLUMN::initial_value))->setBackgroundColor(Qt::red);
    p_table->item(row, int(TABLE_PLAYER_COLUMN::diff_value))->setBackgroundColor(Qt::red);
}

void MainWindow::on_checkBox_goalkeeper_toggled(bool checked)
{
    Q_UNUSED(checked);

    auto table = ui->tablePlayersValues;
    for(int row = 0; row < table->rowCount(); ++row) {
        bool hidden = filter(row);
        table->setRowHidden(row, hidden);
    }
}

void MainWindow::on_checkBox_defender_toggled(bool checked)
{
    Q_UNUSED(checked);

    auto table = ui->tablePlayersValues;
    for(int row = 0; row < table->rowCount(); ++row) {
        bool hidden = filter(row);
        table->setRowHidden(row, hidden);
    }
}

void MainWindow::on_checkBox_midfield_toggled(bool checked)
{
    Q_UNUSED(checked);

    auto table = ui->tablePlayersValues;
    for(int row = 0; row < table->rowCount(); ++row) {
        bool hidden = filter(row);
        table->setRowHidden(row, hidden);
    }
}

void MainWindow::on_checkBox_forward_toggled(bool checked)
{
    Q_UNUSED(checked);

    auto table = ui->tablePlayersValues;
    for(int row = 0; row < table->rowCount(); ++row) {
        bool hidden = filter(row);
        table->setRowHidden(row, hidden);
    }
}

void MainWindow::initTeamsComboBox()
{
    ui->comboBox_teams->clear();

    std::sort(m_real_teams.begin(), m_real_teams.end());

    ui->comboBox_teams->addItem(QString("ALL"));
    for (auto team : m_real_teams) {
        ui->comboBox_teams->addItem(QString(team.c_str()));
    }
}

void MainWindow::on_comboBox_teams_activated(const QString &selected)
{
    Q_UNUSED(selected);

    // Only show the players of the selected team
    auto table = ui->tablePlayersValues;
    for(int row = 0; row < table->rowCount(); ++row) {
        bool hidden = filter(row);
        table->setRowHidden(row, hidden);
    }
}

void MainWindow::on_lineEdit_playerName_returnPressed()
{
    auto table = ui->tablePlayersValues;
    for(int row = 0; row < table->rowCount(); ++row) {
        bool hidden = filter(row);
        table->setRowHidden(row, hidden);
    }
}

bool MainWindow::filterByRole(Football::Player::Role role)
{
    switch (role) {
    case Football::Player::Role::goalkeeper:
        return !ui->checkBox_goalkeeper->isChecked();
    case Football::Player::Role::defender:
        return !ui->checkBox_defender->isChecked();
    case Football::Player::Role::midfield:
        return !ui->checkBox_midfield->isChecked();
    case Football::Player::Role::forward:
        return !ui->checkBox_forward->isChecked();
    default:
        return true;
    }
}

bool MainWindow::filterByTeam(const std::string& team)
{
    QString comboBoxTeam = ui->comboBox_teams->currentText();
    QString playerTeam = QString(team.c_str());

    if (comboBoxTeam == "ALL" || comboBoxTeam == "") {
        return false;
    }

    if (comboBoxTeam == playerTeam) {
        return false;
    }

    return true;
}

bool MainWindow::filterByName(const std::string& name)
{
    QString filterName = ui->lineEdit_playerName->text();
    filterName = filterName.trimmed();
    QString playerName = QString(name.c_str());

    if (filterName == "") {
        return false;
    }

    if (playerName.contains(filterName)) {
        return false;
    }

    return true;
}

bool MainWindow::filter(int row)
{
    QString role_str = ui->tablePlayersValues->item( row, int(TABLE_PLAYER_COLUMN::role) )->text();
    Football::Player::Role role = Football::Player::strToRole(role_str.toStdString());
    bool hidden = filterByRole(role);
    if  (hidden) {
        return hidden;
    }

    QString team = ui->tablePlayersValues->item( row, int(TABLE_PLAYER_COLUMN::team) )->text();
    hidden = filterByTeam(team.toStdString());
    if (hidden) {
        return hidden;
    }

    QString name = ui->tablePlayersValues->item( row, int(TABLE_PLAYER_COLUMN::name) )->text();
    hidden = filterByName(name.toStdString());
    return hidden;
}

void MainWindow::on_lineEdit_playerName_textEdited(const QString &arg1)
{
    ui->lineEdit_playerName->setText(arg1.toUpper());
}


/*
 *  Teams Table
 */

void MainWindow::initTeamsTableHeaders()
{
    auto p_table = ui->tableTeams;

    // Set columns number
    p_table->setColumnCount(7);

    // set horizontal header
    QStringList tableHorizontalHeader {"Team", "Money", "Max Offer", "# P", "# D", "# C", "# A"};
    p_table->setHorizontalHeaderLabels(tableHorizontalHeader);
}

void MainWindow::initTeamsTable()
{
    auto p_table = ui->tableTeams;

    for (auto team_p : m_teams) {
        addTeamRow(*team_p);
    }

    // Disable editing
    p_table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //p_table->resizeColumnsToContents();
    p_table->setSortingEnabled(true);
}

void MainWindow::addTeamRow(const Fantasy::Team& team)
{
    auto p_table = ui->tableTeams;

    // append an empty row
    p_table->insertRow(p_table->rowCount());

    int row = p_table->rowCount() - 1;

    // Populate the row
    QString name = QString(team.name().c_str());
    int money = team.money();
    int max_offer = team.maxOffer();
    int num_gk = team.numByRole(Football::Player::Role::goalkeeper);
    int num_def = team.numByRole(Football::Player::Role::defender);
    int num_mid = team.numByRole(Football::Player::Role::midfield);
    int num_for = team.numByRole(Football::Player::Role::forward);

    p_table->setItem(row, int(TABLE_TEAM_COLUMN::name), new QTableWidgetItem(name));
    p_table->setItem(row, int(TABLE_TEAM_COLUMN::money), new QTableNumberItem(money));
    p_table->setItem(row, int(TABLE_TEAM_COLUMN::max_offer), new QTableNumberItem(max_offer));
    p_table->setItem(row, int(TABLE_TEAM_COLUMN::num_gk), new QTableNumberItem(num_gk));
    p_table->setItem(row, int(TABLE_TEAM_COLUMN::num_def), new QTableNumberItem(num_def));
    p_table->setItem(row, int(TABLE_TEAM_COLUMN::num_mid), new QTableNumberItem(num_mid));
    p_table->setItem(row, int(TABLE_TEAM_COLUMN::num_for), new QTableNumberItem(num_for));
}

void MainWindow::updateTeamsTableRow(int row, std::shared_ptr<Fantasy::Team> team)
{
    auto p_table = ui->tableTeams;

    p_table->setSortingEnabled(false);

    // Populate the row
    QString name = QString(team->name().c_str());
    int money = team->money();
    int max_offer = team->maxOffer();
    int num_gk = team->numByRole(Football::Player::Role::goalkeeper);
    int num_def = team->numByRole(Football::Player::Role::defender);
    int num_mid = team->numByRole(Football::Player::Role::midfield);
    int num_for = team->numByRole(Football::Player::Role::forward);

    p_table->setItem(row, int(TABLE_TEAM_COLUMN::name), new QTableWidgetItem(name));
    p_table->setItem(row, int(TABLE_TEAM_COLUMN::money), new QTableNumberItem(money));
    p_table->setItem(row, int(TABLE_TEAM_COLUMN::max_offer), new QTableNumberItem(max_offer));
    p_table->setItem(row, int(TABLE_TEAM_COLUMN::num_gk), new QTableNumberItem(num_gk));
    p_table->setItem(row, int(TABLE_TEAM_COLUMN::num_def), new QTableNumberItem(num_def));
    p_table->setItem(row, int(TABLE_TEAM_COLUMN::num_mid), new QTableNumberItem(num_mid));
    p_table->setItem(row, int(TABLE_TEAM_COLUMN::num_for), new QTableNumberItem(num_for));

    p_table->setSortingEnabled(true);
}


/*
 *  Teams
 */

void MainWindow::initFantasyTeams()
{
    for (int i = 0; i < 10; ++i) {
        std::string team_name = "team " + std::to_string(i);
        team_sptr team_p( new Fantasy::Team(team_name, 500) );
        m_teams.push_back(team_p);
    }
}

void MainWindow::on_tablePlayersValues_itemDoubleClicked(QTableWidgetItem *item)
{
    // Open dialog to select team and cost
    BuyPlayerDialog bp_dialog(m_teams, this);
    auto res = bp_dialog.exec();
    if (res == QDialog::Rejected) {
        return;
    }

    QString teamName = bp_dialog.team();
    int cost = bp_dialog.cost();

    // Find fantasy team by name
    auto found_team = std::find_if(m_teams.begin(), m_teams.end(), [teamName](const auto& team){
        return QString( team->name().c_str() ) == teamName;
    });

    // Find player
    int playerRow = ui->tablePlayersValues->row(item);
    QString playerName = ui->tablePlayersValues->item( playerRow, int(TABLE_PLAYER_COLUMN::name) )->text();
    auto found_player = std::find_if(m_players.begin(), m_players.end(), [playerName](const auto& player){
        return QString( player->name().c_str() ) == playerName;
    });

    // Buy player
    (*found_team)->buyPlayer((*found_player), cost);

    // Update Players table
    updatePlayersTableBgColorRow(playerRow);
    item->setSelected(false);

    // Update Teams table
    for(int row = 0; row < ui->tableTeams->rowCount(); ++row) {
        QString team_qs = ui->tableTeams->item(row, int(TABLE_TEAM_COLUMN::name))->text();
        if ( team_qs == QString((*found_team)->name().c_str()) ) {
            updateTeamsTableRow(row, (*found_team));
            break;
        }
    }
}
