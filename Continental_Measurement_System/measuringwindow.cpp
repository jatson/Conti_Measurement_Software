#include "measuringwindow.h"
#include "ui_measuringwindow.h"

MeasuringWindow::MeasuringWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MeasuringWindow)
{
    ui->setupUi(this);

    ui->mdiArea->closeAllSubWindows();
    allSignal = new QMap<QString, mySignal*>();
    selectedSignals = new QStringList();
    notSelectedSignals = new QStringList();
    this->setWindowTitle("Continental Measurement System");

    signalWidget = new WidgetA();
    signalWindow = ui->mdiArea->addSubWindow(signalWidget, Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint);
    signalWindow->resize(275, 500);
    signalWindow->setWindowTitle("Signals");
    signalWindow->setAccessibleDescription("signals");
    signalWindow->show();
    ui->actionSignal_window->setChecked(true);

    graphicWidget = new WidgetB();
    graphicWindow = ui->mdiArea->addSubWindow(graphicWidget, Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint);
    graphicWindow->resize(800, 500);
    graphicWindow->setWindowTitle("Charts");
    graphicWindow->setAccessibleDescription("charts");
    graphicWindow->show();
    ui->actionGraphic_Window->setChecked(true);

    connect(graphicWidget, SIGNAL(changedLoopSignal(int,int)), signalWidget, SLOT(changedLoopSlot(int,int)));
}

MeasuringWindow::~MeasuringWindow()
{
    emit closeSignal();
    delete ui;
}

void MeasuringWindow::addSignal()
{
    signalWidget->clear();
    for(QStringList::iterator it = selectedSignals->begin(); it != selectedSignals->end(); it++)
    {
        mySignal* signal = allSignal->value(*it);
        if(!(signal->isLoaded()))
        {
            signal->loadData();
            SignalChart* chart = graphicWidget->addNewChart(signal->getData(), signal->getTime(), *signal->getName());
            signal->setChart(chart);
        }
        signal->setCheckBox(signalWidget->addItem(*it, *signal->getUnit(), signal->getData(), signal->getChart()), signal->isVisible());
    }
    QString mainClockName = notSelectedSignals->filter("MAIN_CLOCK", Qt::CaseSensitive).first();
    mySignal* mainClockSignal = allSignal->value(mainClockName);
    if(!(mainClockSignal->isLoaded()))
    {
        mainClockSignal->loadData();
        graphicWidget->addMainClock(mainClockSignal);
    }
}

void MeasuringWindow::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Escape) emit on_actionClose_triggered();
    if(event->key() == Qt::Key_S) emit on_actionSelect_Signals_triggered();
    if(event->key() == Qt::Key_I) emit on_actionMDF_file_info_triggered();
    if(event->key() == Qt::Key_O) emit on_actionOpen_MDF_file_triggered();
}

void MeasuringWindow::on_actionCloseProfil_triggered()
{   
}

void MeasuringWindow::on_actionSaveProfil_triggered()
{
    OpenSaveDialog *saveProfileDialog =new OpenSaveDialog("Save profile file", "Save", 0, this);
    saveProfileDialog->show();
    connect(saveProfileDialog, SIGNAL(fileSelectedSignal(QString,QString)), this, SLOT(saveProfileSlot(QString,QString)));
}

void MeasuringWindow::on_actionLoadProfil_triggered()
{
    OpenSaveDialog *openProfileDialog =new OpenSaveDialog("Open profile file", "Open", 1, this);
    openProfileDialog->show();
    connect(openProfileDialog, SIGNAL(fileSelectedSignal(QString,QString)), this, SLOT(openProfileSlot(QString,QString)));
}

void MeasuringWindow::on_actionSelect_Signals_triggered()
{
    signalSelectDialog = new SignalSelect(selectedSignals, notSelectedSignals, this);
    connect(signalSelectDialog, SIGNAL(updateSignalsSignal()), this, SLOT(addSignal()));
    signalSelectDialog->show();
}

void MeasuringWindow::on_actionSignal_window_triggered()
{
    if(ui->actionSignal_window->isChecked()) signalWindow->show();
    else signalWindow->hide();
}

void MeasuringWindow::on_actionGraphic_Window_triggered()
{
    if(ui->actionGraphic_Window->isChecked()) graphicWindow->show();
    else graphicWindow->hide();
}

void MeasuringWindow::openMDFSlot(QString path, QString name)
{
    QList<MDFlib::MDFDG*> *dgList;
    QList<MDFlib::MDFCG*> *cgList;
    QList<MDFlib::MDFChannel*> *cnList;
    mdf = new MDFlib::MDF();
    signalNameList = new QList<QString>();


    int numberOfSignals = 0;
    QDir::setCurrent(path);
    bool error = mdf->Open(& name);
    if(error)
    {
        ui->statusbar->showMessage("ERROR: File not loaded!", 10000);
    }
    else
    {
        ui->statusbar->showMessage("Loading from file!");
        dgList = mdf->getDataGroups();
        for(QList<MDFlib::MDFDG*>::iterator dgIt = dgList->begin(); dgIt != dgList->end(); dgIt++)
        {
            cgList = (*dgIt)->getChannelGroups();
            for(QList<MDFlib::MDFCG*>::iterator cgIt = cgList->begin(); cgIt != cgList->end(); cgIt++)
            {
                cnList = (*cgIt)->getChannels();
                for(QList<MDFlib::MDFChannel*>::iterator cnIt = cnList->begin(); cnIt != cnList->end(); cnIt++)
                {
                    signalNameList->append(*((*cnIt)->getNameOfSignal()));
                    numberOfSignals++;

                    mySignal* signal = new mySignal(*cnIt);
                    allSignal->insert(*signal->getName(), signal);
                }
            }
        }
        notSelectedSignals->append(*signalNameList);
        fileName = new QString(name);
        ui->statusbar->showMessage("Signals loaded!", 5000);
    }
    ui->statusbar->clearMessage();
}

void MeasuringWindow::openProfileSlot(QString path, QString name)
{
    QDir::setCurrent(path);
    QFile file(name);
    if( !file.open(QFile::ReadOnly | QFile::Text) )
    {
        ui->statusbar->showMessage("ERROR: Profile not opened!", 10000);
    }
    else
    {
        QTextStream stream(&file);
        QList<QMdiSubWindow*> winList = ui->mdiArea->subWindowList();
        QList<QMdiSubWindow*>::iterator winListIt;
        QString signalName;
        int isHidden, width, height, xPos, yPos, windowsNumber, signalsNumber, colorIndex, offsetY;
        double rateY;

        stream >> windowsNumber;
        for(winListIt=winList.begin();winListIt!=winList.end();winListIt++)
        {
            stream >> isHidden >> width >> height >> xPos >> yPos;
            (*winListIt)->setHidden(isHidden);
            (*winListIt)->size().setWidth(width);
            (*winListIt)->size().setHeight(height);
            (*winListIt)->pos().setX(xPos);
            (*winListIt)->pos().setY(yPos);
        }
        stream >> signalsNumber;
        selectedSignals->clear();
        notSelectedSignals->clear();
        notSelectedSignals->append(allSignal->keys());
        for(int i = 0; i < signalsNumber; i++)
        {
            stream >> signalName;
            selectedSignals->append(signalName);
            notSelectedSignals->removeOne(signalName);
        }
        addSignal();
        for(QStringList::iterator it = selectedSignals->begin(); it != selectedSignals->end(); it++)
        {
            mySignal* signal = allSignal->value(*it);
            stream >> colorIndex >> offsetY >> rateY ;
            signal->getChart()->changeColor(colorIndex);
            signal->getChart()->setOffsetY(offsetY);
            signal->getChart()->setRateY(rateY);
        }

        file.flush();
        file.close();
        ui->statusbar->showMessage("Profile opened!", 10000);
    }
}

void MeasuringWindow::saveProfileSlot(QString path, QString name)
{
    QDir::setCurrent(path);
    QFile file(name);
    if( !file.open(QFile::WriteOnly | QFile::Text) )
    {
        ui->statusbar->showMessage("ERROR: Profile not saved!", 10000);
    }
    else
    {
        QTextStream stream(&file);
        QList<QMdiSubWindow*> winList = ui->mdiArea->subWindowList();
        QList<QMdiSubWindow*>::iterator winListIt;

        stream << winList.size() << "\n";
        for(winListIt=winList.begin();winListIt!=winList.end();winListIt++)
        {
            stream << (*winListIt)->isHidden() << " " << (*winListIt)->size().width() << " " << (*winListIt)->size().height() << " "
                   << (*winListIt)->pos().x() << " " << (*winListIt)->pos().y() << "\n";
        }
        stream << selectedSignals->size() << "\n";
        for(QStringList::iterator it = selectedSignals->begin(); it != selectedSignals->end(); it++)
        {
            mySignal* signal = allSignal->value(*it);
            stream << *signal->getName() << "\n";
        }
        for(QStringList::iterator it = selectedSignals->begin(); it != selectedSignals->end(); it++)
        {
            mySignal* signal = allSignal->value(*it);
            stream << signal->getChart()->getColorIndex() << " " << signal->getChart()->getOffsetY() << " " << signal->getChart()->getRateY() << "\n";
        }
        file.flush();
        file.close();
        ui->statusbar->showMessage("Profile saved!", 10000);
    }
}

void MeasuringWindow::on_actionMDF_file_info_triggered()
{
    MDFFileInfoDialog* dialog = new MDFFileInfoDialog(*fileName, mdf->getFileID()->getFileID(), mdf->getFileID()->getFileVer(),
                                                      mdf->getFileID()->getProgID(), mdf->getFileID()->getByteOrder(),
                                                      mdf->getFileID()->getFileVerInt(), mdf->getFileHeader()->getDate(),
                                                      mdf->getFileHeader()->getTime(), mdf->getFileHeader()->getAuthor(),
                                                      mdf->getFileHeader()->getOrganization(), mdf->getFileHeader()->getProject(),
                                                      mdf->getFileHeader()->getVehicleID(), mdf->getFileHeader()->getComment(), this);
    dialog->show();
}

void MeasuringWindow::on_actionOpen_MDF_file_triggered()
{
    OpenSaveDialog *openMDFDialog = new OpenSaveDialog("Open MDF file", "Open", 1, this);
    openMDFDialog->show();
    connect(openMDFDialog, SIGNAL(fileSelectedSignal(QString,QString)), this, SLOT(openMDFSlot(QString,QString)));
}

void MeasuringWindow::on_actionClose_triggered()
{
    this->close();
}
