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

private:
    Ui::MainWindow *ui;

    // Players quotations table
    enum class TABLE_COLUMN { id, role, name, team, actual_value, initial_value, diff_value };
    void initTableHeaders();
    void addRow(const Player& player);
};

#endif // MAINWINDOW_H
