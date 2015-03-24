#ifndef SIGNALLABLE_H
#define SIGNALLABLE_H

#include <QLabel>
#include <QCheckBox>
#include <QMouseEvent>
#include <QObject>
#include <QAction>
#include <QInputDialog>

#include "signalchart.h"
#include "colorchangedialog.h"

class SignalLabel: public QLabel
{
    Q_OBJECT

public:
    SignalLabel(QCheckBox *chb, const QString &text);
    SignalLabel(QCheckBox* chb, int index, QList<double> *data, const QString& unit, int row, SignalChart* chart);
    void setData(int index);
    SignalLabel* getUnitLabel();
    int getNumOfData();
    void setActions(QAction* color, QAction* vertShift, QAction* vertStretch);

private:
    QCheckBox* checkbox;
    SignalLabel* unit;
    QList<double>* data;
    int dataPrecision;
    int row;
    SignalChart* chart;
    QAction* colorAct;
    QAction* vertShiftAct;
    QAction* vertStretchAct;
    void mousePressEvent(QMouseEvent *e);

private slots:
    void checkboxCheckedSlot();
    void colorActTriggSlot();
    void vertShiftActTriggSlot();
    void vertStretchActTriggSlot();
    void changeColorSlot(int index);

signals:
    void selectRowSignal(int);
};

#endif // SIGNALLABLE_H
