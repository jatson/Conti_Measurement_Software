#ifndef MYSIGNAL_H
#define MYSIGNAL_H

#include <QObject>
#include <QCheckBox>

#include "MDFChannel.h"
#include "signalchart.h"

class mySignal : public QObject
{
    Q_OBJECT
public:
    mySignal();
    mySignal(MDFlib::MDFChannel* ch);
    void loadData();

    MDFlib::MDFChannel *getChannel() const;
    void setChannel(MDFlib::MDFChannel *value);
    QString *getName() const;
    QString *getDescription() const;
    QCheckBox *getCheckBox() const;
    void setCheckBox(QCheckBox *value, bool checked);
    QList<double> *getData() const;
    QList<double> *getTime() const;
    SignalChart *getChart() const;
    void setChart(SignalChart *value);
    bool isVisible() const;
    bool isLoaded() const;
    QString *getUnit() const;
    void setUnit(QString *value);

private:
    bool visible;
    bool loaded;
    QString* name;
    QString* description;
    QString* unit;
    QString* timeUnit;
    QCheckBox* checkBox;
    SignalChart* chart;
    MDFlib::MDFChannel* channel;
    QList<double>* data;
    QList<double>* time;

private slots:
    void checkboxChangedSlot(int state);

signals:
    void checkBoxCheckedSignal();
    void checkBoxUncheckedSignal();
};

#endif // MYSIGNAL_H
