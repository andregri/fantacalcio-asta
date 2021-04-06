#include "buyplayerdialog.h"
#include "ui_buyplayerdialog.h"
#include <algorithm>

BuyPlayerDialog::BuyPlayerDialog(std::vector< std::shared_ptr<Fantasy::Team> > teams, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BuyPlayerDialog)
{
    ui->setupUi(this);

    setWindowTitle("Buy player");

    update(teams);
}

BuyPlayerDialog::~BuyPlayerDialog()
{
    delete ui;
}

int BuyPlayerDialog::cost() const
{
    return ui->cost_spinBox->value();
}

QString BuyPlayerDialog::team() const
{
    return ui->team_comboBox->currentText();
}

void BuyPlayerDialog::update(std::vector< std::shared_ptr<Fantasy::Team> > teams)
{
    // Update the teams ComboBox
    ui->team_comboBox->clear();
    std::sort(teams.begin(), teams.end());
    for (auto team : teams) {
        ui->team_comboBox->addItem(QString(team->name().c_str()));
    }

    // Find the selected team
    QString selectedTeam = ui->team_comboBox->currentText();
    auto found = std::find_if(teams.begin(), teams.end(), [selectedTeam](const auto& team){
        return QString( team->name().c_str() ) == selectedTeam;
    });

    // Update the maximum in the spinBox
    ui->cost_spinBox->setMaximum((*found)->maxOffer());
}

void BuyPlayerDialog::on_buttonBox_accepted()
{
    accept();
}

void BuyPlayerDialog::on_buttonBox_rejected()
{
    reject();
}
