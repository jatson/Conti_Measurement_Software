#ifndef SIGNALSELECT_H
#define SIGNALSELECT_H

#include <QtCore>
#include <QDialog>
#include <QCheckBox>
#include <QWidget>
#include <QLineEdit>
#include <QKeyEvent>

namespace Ui {
class SignalSelect;
}

class SignalSelect : public QDialog
{
    Q_OBJECT
    
public:
    explicit SignalSelect(QStringList* selectedSignals, QStringList* notSelectedSignals, QWidget *parent = 0);
    ~SignalSelect();

private:
    Ui::SignalSelect *ui;
    QStringList *notSelectedSignals;
    QStringList *selectedSignals;
    QStringList *filteredSignals;
    QStringList *oldNotSelectedSignals;
    QStringList *oldSelectedSignals;
    QModelIndex refreshWidgets(QModelIndex index);
    QModelIndex updateWidgets(QModelIndex index, bool select);
    void keyPressEvent(QKeyEvent* event);

private slots:
    void on_pushButton_clicked();                           //select the current signal
    void on_pushButton_2_clicked();                         //deselect the current signal
    void on_pushButton_5_clicked();                         //OK buttok (close with save)
    void on_pushButton_6_clicked();                         //CANCEL button (close without save)
    void on_pushButton_3_clicked();                         //UP button (change the signal position)
    void on_pushButton_4_clicked();                         //DOWN button (change the signal position)
    void on_pushButton_7_clicked();                         //REFRESH button (delete the changes)
    void on_lineEdit_textChanged(const QString &arg1);      //filter for signal list (emit when a character typed)
    void on_checkBox_clicked();                             //case sensitive filtering
    void on_listWidget_doubleClicked(const QModelIndex &index);
    void on_listWidget_2_doubleClicked(const QModelIndex &index);

signals:
    void updateSignalsSignal();
};

#endif // SIGNALSELECT_H
