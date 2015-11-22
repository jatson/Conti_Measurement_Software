#include "widgeta.h"
#include "ui_widgeta.h"

WidgetA::WidgetA(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetA)
{
    ui->setupUi(this);
}

WidgetA::~WidgetA()
{
    delete ui;
}

void WidgetA::setModel(ModelManager *model)
{
    m_modelManager = model;
    ui->tableView->setModel(m_modelManager->m_signalListModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->setSelectionModel(m_modelManager->m_signalItemSelectionModel);
    connect(m_modelManager, SIGNAL(dataChanged()), this, SLOT(dataChangedOnModel()));
}

void WidgetA::dataChangedOnModel()
{
    qDebug() << "widgetA: data chaged on model";
}
