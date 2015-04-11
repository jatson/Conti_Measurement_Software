#include "widgetb.h"
#include "ui_widgetb.h"

WidgetB::WidgetB(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetB)
{
    ui->setupUi(this);
/* Clearing plot layout */
    ui->customPlot->plotLayout()->clear();
/* Create rect */
    wideAxisRect = new QCPAxisRect(ui->customPlot);
}

WidgetB::~WidgetB()
{
    delete ui;
}

void WidgetB::addNewChart(QVector<double> x, QVector<double> y, QString name)
{
/* configure axis rect */
    wideAxisRect->setupFullAxesBox(true);
    wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true); // Sets whether tick labels are displayed. Tick labels are the numbers drawn next to tick marks.

/* add axis to the rect and configure it */
    QCPAxis *axis = wideAxisRect->addAxis(QCPAxis::atLeft);
    axis->setVisible(true);
    axis->setTickLabelColor(QColor(0, 0, 0));

/* configure axis rect low left */
    if(!(ui->customPlot->plotLayout()->hasElement(0, 0))) ui->customPlot->plotLayout()->addElement(0, 0, wideAxisRect);

/* synchronize the left and right margins of the top and bottom axis rects */
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->customPlot);
    wideAxisRect->setMarginGroup(QCP::msLeft | QCP::msRight, marginGroup);

/* create and configure plottables */
    QCPGraph *mainGraph = ui->customPlot->addGraph(
                wideAxisRect->axis(QCPAxis::atBottom, wideAxisRect->axisCount(QCPAxis::atBottom) - 1),
                wideAxisRect->axis(QCPAxis::atLeft, wideAxisRect->axisCount(QCPAxis::atLeft) - 1));
    mainGraph->setData(x, y);
    mainGraph->setName(name);
    mainGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDot, QPen(Qt::red), QBrush(Qt::white), 5));
    mainGraph->setPen(QPen(QColor( 120,  00,  00), 2));

/* rescale axes according to graph's data */
    mainGraph->rescaleAxes();
    wideAxisRect->axis(QCPAxis::atLeft, 1)->setRangeLower(0);
}
