#ifndef BUYPLAYERDIALOG_H
#define BUYPLAYERDIALOG_H

#include <QDialog>
#include <memory>
#include "team.h"

namespace Ui {
class BuyPlayerDialog;
}

class BuyPlayerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BuyPlayerDialog(std::vector< std::shared_ptr<Fantasy::Team> > teams, QWidget *parent = 0);
    ~BuyPlayerDialog();

    int cost() const;
    QString team() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void update(std::vector< std::shared_ptr<Fantasy::Team> > teams);

private:
    Ui::BuyPlayerDialog *ui;
};

#endif // BUYPLAYERDIALOG_H
