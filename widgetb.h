#ifndef WIDGETB_H
#define WIDGETB_H

#include <QWidget>
#include <QPainter>
#include <QGraphicsItem>
#include <QWindow>
#include <QResizeEvent>
#include <QGraphicsView>
#include <math.h>

#include "mysignal.h"
#include "signalchart.h"

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    MyGraphicsView();
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    int getX();

private:
    int x;

signals:
    void changedLoopSignal(int viewPos);
};



namespace Ui {
    class WidgetB;
}

class WidgetB : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetB(QWidget *parent = 0);
    ~WidgetB();
    SignalChart* addNewChart(QList<double>* data, QList<double>* time, QString name);
    void clearWidget();
    void addMainClock(mySignal* signal);

private:
    Ui::WidgetB *ui;
    void resizeEvent(QResizeEvent* event);
    QGraphicsScene *scene;
    QPen* pen;
    QBrush* brush;
    QMap<QString, SignalChart*>* chartMap;
    QList<QGraphicsLineItem*>* list;
    int zoomDepth;
    MyGraphicsView* graphicsView;
    int color;
    int numOfColor;
    QGraphicsLineItem* timeLine;
    mySignal* mainClock;
    bool mainClockLoaded;
    qreal map(qreal value, float fromMin, float fromMax, float toMin, float toMax);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_4_clicked();
    void shiftLeft();
    void shiftRight();
    void changedLoopSlot(int viewPos);

signals:
    void changedLoopSignal(int pos, int max);
};



#endif // WIDGETB_H
