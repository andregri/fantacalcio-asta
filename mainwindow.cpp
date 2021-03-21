#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

#include <algorithm>

#include "parser.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->btnLoadCsv->setToolTip("Select the file with the players quotations");

    initTableHeaders();
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
    Player player;
    while (parser.parseLine(player)) {
        // add team name to the list
        std::string team = player.team();
        if ( std::find(m_real_teams.begin(), m_real_teams.end(), team) == m_real_teams.end() ) {
            m_real_teams.push_back(team);
        }

        // add row to the table
        addRow(player, false);

        // set row hidden or visible based on filters
        int row = ui->tablePlayersValues->rowCount() - 1;
        bool hidden = filter(row);
        ui->tablePlayersValues->setRowHidden(row, hidden);
    }

    initTeamsComboBox();

    ui->tablePlayersValues->setSortingEnabled(true);
}

void MainWindow::initTableHeaders()
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

void MainWindow::addRow(const Player& player, bool hidden)
{
    auto p_table = ui->tablePlayersValues;

    // append an empty row
    p_table->insertRow(p_table->rowCount());

    int row = p_table->rowCount() - 1;

    // Populate the row
    QString id = QString::number(player.id());
    QString role = QString(Player::roleToStr(player.role()).c_str());
    QString name = QString(player.name().c_str());
    QString team = QString(player.team().c_str());
    QString actualValue = QString::number(player.actualValue());
    QString initialValue = QString::number(player.initialValue());
    QString diffValue = QString::number(player.diffValue());

    p_table->setItem(row, int(TABLE_COLUMN::id), new QTableWidgetItem(id));
    p_table->setItem(row, int(TABLE_COLUMN::role), new QTableWidgetItem(role));
    p_table->setItem(row, int(TABLE_COLUMN::name), new QTableWidgetItem(name));
    p_table->setItem(row, int(TABLE_COLUMN::team), new QTableWidgetItem(team));
    p_table->setItem(row, int(TABLE_COLUMN::actual_value), new QTableWidgetItem(actualValue));
    p_table->setItem(row, int(TABLE_COLUMN::initial_value), new QTableWidgetItem(initialValue));
    p_table->setItem(row, int(TABLE_COLUMN::diff_value), new QTableWidgetItem(diffValue));

    p_table->setRowHidden(row, hidden);
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

bool MainWindow::filterByRole(Player::Role role)
{
    switch (role) {
    case Player::Role::goalkeeper:
        return !ui->checkBox_goalkeeper->isChecked();
    case Player::Role::defender:
        return !ui->checkBox_defender->isChecked();
    case Player::Role::midfield:
        return !ui->checkBox_midfield->isChecked();
    case Player::Role::forward:
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
    QString role_str = ui->tablePlayersValues->item( row, int(TABLE_COLUMN::role) )->text();
    Player::Role role = Player::strToRole(role_str.toStdString());
    bool hidden = filterByRole(role);
    if  (hidden) {
        return hidden;
    }

    QString team = ui->tablePlayersValues->item( row, int(TABLE_COLUMN::team) )->text();
    hidden = filterByTeam(team.toStdString());
    if (hidden) {
        return hidden;
    }

    QString name = ui->tablePlayersValues->item( row, int(TABLE_COLUMN::name) )->text();
    hidden = filterByName(name.toStdString());
    return hidden;
}

void MainWindow::on_lineEdit_playerName_textEdited(const QString &arg1)
{
    ui->lineEdit_playerName->setText(arg1.toUpper());
}
