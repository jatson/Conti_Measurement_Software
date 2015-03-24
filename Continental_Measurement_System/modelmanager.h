#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <QObject>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QItemSelectionModel>

class ModelManager : public QObject
{
    Q_OBJECT
public:
    explicit ModelManager(QObject *parent = 0);
    QStandardItemModel * m_signalListModel;
    QItemSelectionModel * m_signalItemSelectionModel;

    void emptyModel();

signals:

public slots:

};

#endif // MODELMANAGER_H
