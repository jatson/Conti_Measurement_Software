#include "widgetb.h"
#include "ui_widgetb.h"

WidgetB::WidgetB(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetB)
{
    ui->setupUi(this);
}

WidgetB::~WidgetB()
{
    delete ui;
}

void WidgetB::addNewChart(QVector<double> x, QVector<double> y, QString name)
{
    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(ui->customPlot->graphCount() - 1)->setData(x, y);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("Time");
    ui->customPlot->yAxis->setLabel(name);
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->rescale();
    ui->customPlot->yAxis->rescale();
    ui->customPlot->replot();
}
