#ifndef SIGNALCHART_H
#define SIGNALCHART_H

#include <QWidget>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QObject>

class SignalChart : public QObject
{
    Q_OBJECT
public:
    SignalChart(QList<double>* data, QList<double> *time, QGraphicsScene *sc, int color);
    ~SignalChart();

    void magnify(double scale);
    void reduce(double scale);
    void setIntervalH(float toMin, float toMax);
    void setIntervalV(float toMin, float toMax);
    qreal map(qreal value, float fromMin, float fromMax, float toMin, float toMax);
    void changeColor(int colorIndex);
    QColor* getColor();
    int getColorIndex() const;

//OffsetY
    void setOffsetY(int offset);
    int getOffsetY();
//rateY
    void setRateY(double rate);
    double getRateY();

private:
    QGraphicsScene* scene;
    QGraphicsLineItem* parent;
    int offsetY;
    QPen* pen;
    int sizeX;
    QList<QGraphicsLineItem*>* lines;
    float intVMin;
    float intVMax;
    float intHMin;
    float intHMax;
    QList<QString> colorList;
    QColor* color;
    int colorIndex;
    double rateY;

public slots:
    void addToSceneSlot();
    void removeFromSceneSlot();
};

#endif // SIGNALCHART_H
