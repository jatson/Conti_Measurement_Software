#include "widgeta.h"
#include "ui_widgeta.h"

WidgetA::WidgetA(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetA)
{
    ui->setupUi(this);
    numberOfSignals = 0;
    signalList = new QList<SignalLabel*>;

    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(2);
    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setShowGrid(false);
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}

WidgetA::~WidgetA()
{
    delete ui;
}

QCheckBox* WidgetA::addItem(const QString& name, const QString& unit, QList<double>* data, SignalChart *chart)      //a nevet és az egységet fixen be lehet írni, az adatokat pedig tárolni kell
{
    ui->tableWidget->setRowCount(numberOfSignals + 1);
    QCheckBox* checkbox = new QCheckBox(name);
    SignalLabel* newLable = new SignalLabel(checkbox, 0, data, unit, numberOfSignals, chart);
    ui->tableWidget->setCellWidget(numberOfSignals, 0, checkbox);
    ui->tableWidget->setCellWidget(numberOfSignals, 1, newLable);
    ui->tableWidget->setCellWidget(numberOfSignals, 2, newLable->getUnitLabel());
    ui->tableWidget->resizeColumnToContents(0);
    ui->tableWidget->setColumnWidth(1, 50);
    newLable->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->resizeColumnToContents(2);

    QString* colorStr = new QString("Color");
    QString* vertShiftStr = new QString("Vertical offset");
    QString* vertStretchStr = new QString("Vertical stretch");
    QAction* colorAct = new QAction(*colorStr, this);
    QAction* vertShiftAct = new QAction(*vertShiftStr, this);
    QAction* vertStretchAct = new QAction(*vertStretchStr, this);

    newLable->setActions(colorAct, vertShiftAct, vertStretchAct);

    ui->tableWidget->cellWidget(numberOfSignals,0)->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->tableWidget->cellWidget(numberOfSignals,1)->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->tableWidget->cellWidget(numberOfSignals,2)->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->tableWidget->cellWidget(numberOfSignals,0)->addAction(colorAct);
    ui->tableWidget->cellWidget(numberOfSignals,0)->addAction(vertShiftAct);
    ui->tableWidget->cellWidget(numberOfSignals,0)->addAction(vertStretchAct);
    ui->tableWidget->cellWidget(numberOfSignals,1)->addAction(colorAct);
    ui->tableWidget->cellWidget(numberOfSignals,1)->addAction(vertShiftAct);
    ui->tableWidget->cellWidget(numberOfSignals,1)->addAction(vertStretchAct);
    ui->tableWidget->cellWidget(numberOfSignals,2)->addAction(colorAct);
    ui->tableWidget->cellWidget(numberOfSignals,2)->addAction(vertShiftAct);
    ui->tableWidget->cellWidget(numberOfSignals,2)->addAction(vertStretchAct);

    numberOfSignals++;

    signalList->append(newLable);

    connect(newLable, SIGNAL(selectRowSignal(int)), this, SLOT(selectRowSlot(int)));

    return checkbox;
}

void WidgetA::clear()
{
    ui->tableWidget->clear();                              //ki kell őket törölni a grafikus felületről is
    ui->tableWidget->setRowCount(0);
    signalList->clear();
    numberOfSignals = 0;
}

void WidgetA::changedLoopSlot(int pos, int max)
{
    int index;
    for(QList<SignalLabel*>::iterator it = signalList->begin(); it != signalList->end(); it++)
    {
        index = map(pos, 0, max, 0, (*it)->getNumOfData() - 1);
        if(index >= 0 && index < (*it)->getNumOfData())
            (*it)->setData(index);
    }
}

void WidgetA::selectRowSlot(int index)
{
    ui->tableWidget->selectRow(index);
}

qreal WidgetA::map(qreal value, float fromMin, float fromMax, float toMin, float toMax)   //transform a value from an intervall to an other
{
    return (toMin + (((toMax - toMin)/(fromMax - fromMin)) * (value - fromMin)));
}
