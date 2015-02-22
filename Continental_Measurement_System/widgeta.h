#ifndef WIDGETA_H
#define WIDGETA_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QCheckBox>

#include "signalchart.h"
#include "signallabel.h"

namespace Ui {
class WidgetA;
}

class WidgetA : public QWidget
{
    Q_OBJECT
    
public:
    explicit WidgetA(QWidget *parent = 0);
    ~WidgetA();
    QCheckBox* addItem(const QString& name, const QString &unit, QList<double> *data, SignalChart* chart);
    void clear();

private slots:
    void changedLoopSlot(int pos, int max);
    void selectRowSlot(int index);

private:
    Ui::WidgetA *ui;
    QList<SignalLabel*>* signalList;
    int numberOfSignals;
    int dataIndex;
    qreal map(qreal value, float fromMin, float fromMax, float toMin, float toMax);
};

#endif // WIDGETA_H
