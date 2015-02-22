#include "widgetb.h"
#include "ui_widgetb.h"

WidgetB::WidgetB(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetB)
{
    ui->setupUi(this);
    pen = new QPen(Qt::red);
    pen->setWidth(1);
    scene = new QGraphicsScene(this);
    brush = new QBrush(Qt::black);
    timeLine = scene->addLine(0,0,0,0,QPen(Qt::white));
    timeLine->setZValue(0);
    timeLine->setOpacity(0.3);

    graphicsView = new MyGraphicsView();
    ui->verticalLayout->addWidget(graphicsView);
    graphicsView->setScene(scene);
    scene->setBackgroundBrush(*brush);

    chartMap = new QMap<QString, SignalChart*>;
    list = new QList<QGraphicsLineItem*>;
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    connect(graphicsView, SIGNAL(changedLoopSignal(int)), this, SLOT(changedLoopSlot(int)));

    zoomDepth = 0;
    color = 0;
    numOfColor = 25;
    mainClockLoaded = false;

    QTimer* timerRight = new QTimer(this);
    connect(timerRight, SIGNAL(timeout()), this, SLOT(shiftRight()));
    connect(ui->pushButton_3, SIGNAL(pressed()), timerRight, SLOT(start()));
    connect(ui->pushButton_3, SIGNAL(released()), timerRight, SLOT(stop()));

    QTimer* timerLeft = new QTimer(this);
    connect(timerLeft, SIGNAL(timeout()), this, SLOT(shiftLeft()));
    connect(ui->pushButton_2, SIGNAL(pressed()), timerLeft, SLOT(start()));
    connect(ui->pushButton_2, SIGNAL(released()), timerLeft, SLOT(stop()));
}

WidgetB::~WidgetB()
{
    delete ui;
}

SignalChart *WidgetB::addNewChart(QList<double> *data, QList<double> *time, QString name)
{
    SignalChart* chart = new SignalChart(data, time, scene, color);
    if(color >= numOfColor) color = 0;
    else color++;

    for(int i = 0; i < zoomDepth; i++)
    {
        chart->magnify(2);
    }
    chart->setIntervalH(0, graphicsView->width() -1);
    chartMap->insert(name, chart);

    timeLine->setLine(timeLine->line().x1(), 2 - (graphicsView->height() / 2), timeLine->line().x1(), (graphicsView->height() / 2) - 2);       //hosszát meg kell növelni

    return chart;
}

void WidgetB::on_pushButton_clicked()                       //Zoom in
{
    if(zoomDepth < 10)
    {
        for(QMap<QString, SignalChart*>::iterator chartIt = chartMap->begin(); chartIt != chartMap->end(); chartIt++)
        {
            (*chartIt)->magnify(2);
        }
        zoomDepth++;
        timeLine->setPos(timeLine->pos().x() * 2, timeLine->pos().y());
    }
}

void WidgetB::on_pushButton_4_clicked()                     //Zoom out
{
    if(zoomDepth > 0)
    {
        for(QMap<QString, SignalChart*>::iterator chartIt = chartMap->begin(); chartIt != chartMap->end(); chartIt++)
        {
            (*chartIt)->reduce(2);
        }
        zoomDepth--;
        timeLine->setPos(timeLine->pos().x() / 2, timeLine->pos().y());
    }
    scene->setSceneRect(0, scene->itemsBoundingRect().y(), scene->itemsBoundingRect().width() / pow(2.0, (double)zoomDepth) - 2, scene->itemsBoundingRect().height());
}

void WidgetB::shiftLeft()
{
    if(scene->sceneRect().x() > 0)
        scene->setSceneRect(scene->sceneRect().x() - 1, scene->sceneRect().y(), scene->sceneRect().width(), scene->sceneRect().height());
}

void WidgetB::shiftRight()
{
    if(scene->sceneRect().x() < (scene->itemsBoundingRect().width()) - graphicsView->width())
        scene->setSceneRect(scene->sceneRect().x() + 1, scene->sceneRect().y(), scene->sceneRect().width(), scene->sceneRect().height());
}

void WidgetB::changedLoopSlot(int viewPos)
{
    int pos = viewPos + scene->sceneRect().x();
    emit changedLoopSignal(pos, scene->itemsBoundingRect().width() - 1);
    timeLine->setPos((qreal)pos, timeLine->pos().y());
    if(mainClockLoaded){
        QList<double>* mainClockData = mainClock->getData();
        int index = map(pos, 0, scene->itemsBoundingRect().width() - 1, 0, mainClockData->size() - 1);
        if(index >= 0 && index < mainClockData->size())
            ui->label_2->setText(QString::number(mainClockData->at(index)));
    }
}

void WidgetB::resizeEvent(QResizeEvent* /*event*/)
{
    for(QMap<QString, SignalChart*>::iterator chartIt = chartMap->begin(); chartIt != chartMap->end(); chartIt++)
    {
        (*chartIt)->setIntervalH(0, graphicsView->width() + 1);
    }
    timeLine->setLine(timeLine->line().x1(), 2 - (graphicsView->height() / 2), timeLine->line().x1(), (graphicsView->height() / 2) - 2);
    if(zoomDepth != 0)
        scene->setSceneRect(0, scene->itemsBoundingRect().y(), scene->itemsBoundingRect().width() / pow(2.0, (double)zoomDepth) - 2, scene->itemsBoundingRect().height());
    else
        scene->setSceneRect(0, scene->itemsBoundingRect().y(), scene->itemsBoundingRect().width() / pow(2.0, (double)zoomDepth) - 2, scene->itemsBoundingRect().height());
}


MyGraphicsView::MyGraphicsView()
{
    setCursor(QCursor(Qt::CrossCursor));
    setFrameShape(QFrame::NoFrame);
    setCacheMode(QGraphicsView::CacheBackground);
    setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Qt4CompatiblePainting);
    setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    x = event->x();
    emit changedLoopSignal(x);
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{
    emit mouseMoveEvent(event);
}

int MyGraphicsView::getX()
{
    return x;
}

void WidgetB::addMainClock(mySignal *signal)
{
    if(!mainClockLoaded)
    {
        mainClock = signal;
        ui->label_3->setText(*(mainClock->getUnit()));
        mainClockLoaded = true;
    }
}

qreal WidgetB::map(qreal value, float fromMin, float fromMax, float toMin, float toMax)   //transform a value from an intervall to an other
{
    return (toMin + (((toMax - toMin)/(fromMax - fromMin)) * (value - fromMin)));
}
