#include "modelmanager.h"

ModelManager::ModelManager(QObject *parent) :
    QObject(parent)
{
    m_signalListModel = new QStandardItemModel(0, 4, this);     /* will be 0 row, 3 collumns in the list (name, value, unit, is enabled?) */
    m_signalItemSelectionModel = new QItemSelectionModel(m_signalItemSelectionModel, this);
    emptyModel();
}

void ModelManager::emptyModel()
{
    m_signalListModel->clear();
    QList<QStandardItem *> newRow;
    m_signalListModel->appendRow(newRow);
    m_signalListModel->setHorizontalHeaderLabels(QStringList()
                                                 << tr("Signal Name")
                                                 << tr("Value")
                                                 << tr("Unit")
                                                 << tr("Enabled"));
    QStandardItem * item0 = new QStandardItem(true);
    item0->setCheckable(true);
    item0->setCheckState(Qt::Checked);
    m_signalListModel->setItem(0, 3, item0);
}
