#ifndef WIDGETB_H
#define WIDGETB_H

#include <QWidget>
#include <QDebug>
#include "qcustomplot/qcustomplot.h"
#include "modelmanager.h"

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
    int getRandomNo(int low, int high);

    void setModel(ModelManager * model);

private:
    Ui::WidgetB *ui;
    QCPAxisRect * wideAxisRect;

    ModelManager* m_modelManager;

public slots:
    void dataChangedOnModel();

};

#endif // WIDGETB_H
