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

/* Seed the random generator with current time */
  QTime time = QTime::currentTime();
  qsrand((uint)time.msec());

    ui->customPlot->setInteractions(QCP::iRangeDrag |
                                    QCP::iRangeZoom |
                                    QCP::iSelectAxes |
                                    QCP::iSelectLegend |
                                    QCP::iSelectPlottables);

/* Ez valamiért bugos... Mért?
    ui->customPlot->legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->legend->setSelectedFont(legendFont);
    ui->customPlot->legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items
*/

    // connect slot that ties some axis selections together (especially opposite axes):
    connect(ui->customPlot, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));

    // connect some interaction slots:
    connect(ui->customPlot, SIGNAL(titleDoubleClick(QMouseEvent*,QCPPlotTitle*)), this, SLOT(titleDoubleClick(QMouseEvent*,QCPPlotTitle*)));
    connect(ui->customPlot, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(axisLabelDoubleClick(QCPAxis*,QCPAxis::SelectablePart)));
    connect(ui->customPlot, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*)));

    // connect slot that shows a message in the status bar when a graph is clicked:
    connect(ui->customPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*)));

    // setup policy and connect slot for context menu popup:
    ui->customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->customPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));

}

WidgetB::~WidgetB()
{
    delete ui;
}

void WidgetB::addNewChart(QVector<double> x, QVector<double> y, QString name)
{
    qDebug() << "data size: " << x.size() << "time size: " << y.size();
/* configure axis rect */
    wideAxisRect->setupFullAxesBox(true);
    wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true); // Sets whether tick labels are displayed. Tick labels are the numbers drawn next to tick marks.

/* add axis to the rect and configure it */
    QCPAxis *axis = wideAxisRect->addAxis(QCPAxis::atLeft);
    axis->setVisible(false);
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
    mainGraph->setAdaptiveSampling(true);
    mainGraph->setData(x, y);
    mainGraph->setName(name);
    mainGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone, QPen(Qt::red), QBrush(Qt::white), 3));
    mainGraph->setPen(QPen(QColor(getRandomNo(0, 255),
                                  getRandomNo(0, 255),
                                  getRandomNo(0, 255)),
                                  1)); // Magic only happens, when line width == 1

/* rescale axes according to graph's data */
    mainGraph->rescaleAxes();
    wideAxisRect->axis(QCPAxis::atLeft, 1)->setRangeLower(0);
}

int WidgetB::getRandomNo(int low, int high)
{
    return qrand() % ((high + 1) - low) + low;
}

void WidgetB::setModel(ModelManager *model)
{
    m_modelManager = model;
    connect(m_modelManager, SIGNAL(dataChanged()), this, SLOT(dataChangedOnModel()));
}

void WidgetB::dataChangedOnModel()
{
    qDebug() << "widgetB: data chaged on model";
}
