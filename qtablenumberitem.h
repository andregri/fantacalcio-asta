#ifndef QTABLENUMBERITEM_H
#define QTABLENUMBERITEM_H

#include <QTableWidgetItem>

class QTableNumberItem : public QTableWidgetItem
{
public:
    QTableNumberItem(const QString&);
    QTableNumberItem(double);
    QTableNumberItem(const QTableWidgetItem&);

    bool operator<(const QTableWidgetItem&) const;

private:
    QTableNumberItem();
    double m_value;
};

#endif // QTABLENUMBERITEM_H
