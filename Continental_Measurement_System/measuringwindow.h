#ifndef MEASURINGWINDOW_H
#define MEASURINGWINDOW_H

#include <QtCore>
#include <QMainWindow>
#include <QMdiSubWindow>
#include <QKeyEvent>
#include <Continental_Measurement_System/widgeta.h>
#include <Continental_Measurement_System/widgetb.h>

#include "signalselect.h"
#include "Continental_Measurement_System/MDF/MDFLib.h"
#include "mysignal.h"
#include "mdffileinfodialog.h"
#include "opensavedialog.h"

namespace Ui {
class MeasuringWindow;
}

class MeasuringWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MeasuringWindow(QWidget *parent = 0);
    ~MeasuringWindow();

private:
    Ui::MeasuringWindow *ui;
    MDFlib::MDF *mdf;
    char percent;
    SignalSelect *signalSelectDialog;
    QMdiSubWindow *signalWindow;
    WidgetA *signalWidget;
    QMdiSubWindow *graphicWindow;
    WidgetB *graphicWidget;
    QString* fileName;

    void keyPressEvent(QKeyEvent* event);
    void initSignals();
    QMap<QString, mySignal*>* allSignal;
    QList<QString>* signalNameList;
    QStringList* selectedSignals;
    QStringList* notSelectedSignals;
    
private slots:
    void on_actionCloseProfil_triggered();
    void on_actionSaveProfil_triggered();
    void on_actionLoadProfil_triggered();
    void on_actionSelect_Signals_triggered();
    void on_actionSignal_window_triggered();
    void on_actionGraphic_Window_triggered();
    void openMDFSlot(QString path, QString name);
    void openProfileSlot(QString path, QString name);
    void saveProfileSlot(QString path, QString name);
    void on_actionMDF_file_info_triggered();
    void on_actionOpen_MDF_file_triggered();

    void on_actionClose_triggered();

public slots:
    void addSignal();

signals:
    void closeSignal();
};

#endif // MEASURINGWINDOW_H
