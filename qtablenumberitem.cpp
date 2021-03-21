#include "qtablenumberitem.h"

QTableNumberItem::QTableNumberItem(const QString& text) :
    QTableWidgetItem(text),
    m_value(text.toDouble())
{

}

QTableNumberItem::QTableNumberItem(double v) :
    QTableWidgetItem(QString::number(v)),
    m_value(v)
{

}

QTableNumberItem::QTableNumberItem(const QTableWidgetItem& item) :
    QTableWidgetItem(item),
    m_value(item.text().toDouble())
{

}

bool QTableNumberItem::operator<(const QTableWidgetItem& rhs) const
{
    auto casted_rhs = static_cast<QTableNumberItem>(rhs);
    return m_value < casted_rhs.m_value;
}
