#include "signalchart.h"

SignalChart::SignalChart(QList<double>* data, QList<double>* time, QGraphicsScene* sc, int color)
{
    if(!(time->isEmpty()))
    {
        intHMax = time->last();
    }
    else
    {
        intHMax = 0;
    }
    intHMin = time->first();

    colorList << "red" << "green" << "blue" << "cyan" << "magenta" << "yellow" << "gray" << "teal" << "tomato" << "white" << "brown" << "greenyellow" << "deeppink" << "steelblue" << "darkRed" << "darkGreen" << "darkBlue" << "darkCyan" << "darkMagenta" << "darkYellow" << "darkGray" << "darkOrange" << "darkOrchid" << "slateblue" << "springgreen";
    this->color = new QColor(colorList[color]);
    pen = new QPen(*(this->color));
    pen->setWidth(1);

    qreal prevPosX = time->first();
    qreal actPosX = 0;
    qreal prevPosY = 0;
    qreal actPosY = 0;
    int i = 1;
    double min;
    QGraphicsLineItem* actual;
    parent = new QGraphicsLineItem();
    parent->setZValue(255);
    scene = sc;
    lines = new QList<QGraphicsLineItem*>();

    QList<double>::iterator dataIt = data->begin();
    prevPosY = *dataIt * -1;
    min = prevPosY;

    for(dataIt++; dataIt != data->end(); dataIt++)
    {
        actPosX = time->at(i);
        actPosY = *dataIt * -1;
        if(actPosY < min) min = actPosY;
        actual = scene->addLine(prevPosX,prevPosY,prevPosX,actPosY,*pen);
        actual->setParentItem(parent);
        actual->setZValue(255);
        lines->append(actual);
        actual = scene->addLine(prevPosX,actPosY,actPosX,actPosY,*pen);
        lines->append(actual);
        actual->setParentItem(parent);
        actual->setZValue(255);
        i++;
        prevPosX = actPosX;
        prevPosY = actPosY;
    }
    sizeX = actPosX;
    colorIndex = color;
    offsetY = min;
    rateY = 1.0;
}

SignalChart::~SignalChart()
{
}

void SignalChart::setOffsetY(int offset)
{
    QList<QGraphicsLineItem*>::iterator listIt;
    for(listIt=lines->begin(); listIt!=lines->end(); listIt++)
    {
        QLineF line = (*listIt)->line();
        QPointF point1 = line.p1();
        QPointF point2 = line.p2();
        point1.setY(point1.y() - offsetY + offset);
        point2.setY(point2.y() - offsetY + offset);
        line.setP1(point1);
        line.setP2(point2);
        (*listIt)->setLine(line);
        (*listIt)->update();
    }
    offsetY = offset;
}

int SignalChart::getOffsetY()
{
    return offsetY;
}

void SignalChart::setRateY(double rate)
{
    QList<QGraphicsLineItem*>::iterator listIt;
    for(listIt=lines->begin(); listIt!=lines->end(); listIt++)
    {
        QLineF line = (*listIt)->line();
        QPointF point1 = line.p1();
        QPointF point2 = line.p2();
        point1.setY(((point1.y() - offsetY) / rateY * rate) + offsetY);
        point2.setY(((point2.y() - offsetY) / rateY * rate) + offsetY);
        line.setP1(point1);
        line.setP2(point2);
        (*listIt)->setLine(line);
        (*listIt)->update();
    }
    rateY = rate;
}

double SignalChart::getRateY()
{
    return rateY;
}

QColor *SignalChart::getColor()
{
    return color;
}

int SignalChart::getColorIndex() const
{
    return colorIndex;
}

void SignalChart::addToSceneSlot()
{
    scene->addItem(parent);
}

void SignalChart::removeFromSceneSlot()
{
    scene->removeItem(parent);
}

void SignalChart::magnify(double scale)
{
    QList<QGraphicsLineItem*>::iterator listIt;
    for(listIt=lines->begin(); listIt!=lines->end(); listIt++)
    {
        QLineF line = (*listIt)->line();
        QPointF point1 = line.p1();
        QPointF point2 = line.p2();
        point1.setX(point1.x() * scale);
        point2.setX(point2.x() * scale);
        line.setP1(point1);
        line.setP2(point2);
        (*listIt)->setLine(line);
        (*listIt)->update();
    }
}

void SignalChart::reduce(double scale)
{
    QList<QGraphicsLineItem*>::iterator listIt;
    for(listIt=lines->begin(); listIt!=lines->end(); listIt++)
    {
        QLineF line = (*listIt)->line();
        QPointF point1 = line.p1();
        QPointF point2 = line.p2();
        point1.setX(point1.x() / scale);
        point2.setX(point2.x() / scale);
        line.setP1(point1);
        line.setP2(point2);
        (*listIt)->setLine(line);
        (*listIt)->update();
    }
}

void SignalChart::setIntervalH(float toMin, float toMax)
{
    QList<QGraphicsLineItem*>::iterator it;
    for(it = lines->begin(); it != lines->end(); it++)
    {
        QLineF line = (*it)->line();
        QPointF point1 = line.p1();
        QPointF point2 = line.p2();
        point1.setX(map(point1.x(), intHMin, intHMax, toMin, toMax));
        point2.setX(map(point2.x(), intHMin, intHMax, toMin, toMax));
        line.setP1(point1);
        line.setP2(point2);
        (*it)->setLine(line);
        (*it)->update();
    }
    intHMin = map(intHMin, intHMin, intHMax, toMin, toMax);
    intHMax = map(intHMax, intHMin, intHMax, toMin, toMax);
}

qreal SignalChart::map(qreal value, float fromMin, float fromMax, float toMin, float toMax)   //transform a value from an intervall to an other
{
    return (toMin + (((toMax - toMin)/(fromMax - fromMin)) * (value - fromMin)));
}

void SignalChart::changeColor(int colorIndex)
{
    QColor* newColor = new QColor(colorList[colorIndex]);
    pen->setColor(*newColor);
    parent->setPen(*pen);
    QList<QGraphicsLineItem*>::iterator it;
    for(it = lines->begin(); it != lines->end(); it++)
    {
       (*it)->setPen(*pen);
    }
    color = newColor;
    this->colorIndex = colorIndex;
}
