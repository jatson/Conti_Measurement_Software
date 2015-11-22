#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <QObject>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QItemSelectionModel>

#include <QDebug>

class ModelManager : public QObject
{
    Q_OBJECT
private:
    void addToWidgetA(QString name, QVector<double> data, QString unit, bool &enabled);

public:
    explicit ModelManager(QObject *parent = 0);
    QStandardItemModel * m_signalListModel;
    QItemSelectionModel * m_signalItemSelectionModel;

    void emptyModel();
    void addItem(QString name, QVector<double> data, QString unit, bool &enabled);

signals:
    void dataChanged();

public slots:

};

#endif // MODELMANAGER_H
