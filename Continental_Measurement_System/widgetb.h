#ifndef WIDGETB_H
#define WIDGETB_H

#include <QWidget>
#include <QDebug>
#include "qcustomplot/qcustomplot.h"
#include "widgeta.h"

namespace Ui {
class WidgetB;
}

class WidgetB : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetB(QWidget *parent = 0);
    ~WidgetB();
    void addNewChart(QVector<double> x, QVector<double> y, QString name);

private:
    Ui::WidgetB *ui;
    QCPAxisRect * wideAxisRect;

};

#endif // WIDGETB_H
