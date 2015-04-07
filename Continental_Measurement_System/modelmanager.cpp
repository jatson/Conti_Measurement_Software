#include "modelmanager.h"

ModelManager::ModelManager(QObject *parent) :
    QObject(parent)
{
    m_signalListModel = new QStandardItemModel(0, 4, this);     /* will be 0 row, 3 collumns in the list (name, value, unit, is enabled?) */
    m_signalItemSelectionModel = new QItemSelectionModel(m_signalListModel, this);
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
    /* Example for checkbox */
    QStandardItem * item0 = new QStandardItem(true);
    item0->setCheckable(true);
    item0->setCheckState(Qt::Checked);
    m_signalListModel->setItem(0, 3, item0);
}


/*
 * ide kell majd átdobálni az adatokat, amire szükség lesz..
 * és szintén itt kel majd törölni...
 * a view magától feldolgozza  változást
 *
 * itt nem kell foglalkozni a kijelöléssekkel, azt a WidgetA-tól elkérni.
 * Ő pontosan tudni fogja mi a kijelölt elem idexe, amit aztán oda lehet
 * adni a chart-nak.
 */
