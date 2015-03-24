#include "widgeta.h"
#include "ui_widgeta.h"

WidgetA::WidgetA(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetA)
{
    ui->setupUi(this);
    m_modelManager = new ModelManager(this);
    ui->tableView->setModel(m_modelManager->m_signalListModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionModel(m_modelManager->m_signalListModel);
}

WidgetA::~WidgetA()
{
    delete ui;
}
