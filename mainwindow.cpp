#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

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
        addRow(player);
    }
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

void MainWindow::addRow(const Player& player)
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
}
