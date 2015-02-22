#include "signalselect.h"
#include "ui_signalselect.h"

SignalSelect::SignalSelect(QStringList *selectedSignals, QStringList *notSelectedSignals, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignalSelect)
{
    ui->setupUi(this);

    oldSelectedSignals = selectedSignals;
    oldNotSelectedSignals = notSelectedSignals;
    oldNotSelectedSignals->sort(Qt::CaseInsensitive);

    this->selectedSignals = new QStringList(*selectedSignals);
    this->notSelectedSignals = new QStringList(*notSelectedSignals);
    this->filteredSignals = new QStringList(*notSelectedSignals);

    refreshWidgets(ui->listWidget->currentIndex());

    ui->listWidget->setAlternatingRowColors(true);
    ui->listWidget->setToolTip("Choose the signals, which you want to see.");

    ui->listWidget_2->setAlternatingRowColors(true);
    ui->listWidget_2->setToolTip("Selected signals.");

    ui->listWidget->setUniformItemSizes(true);
    ui->listWidget_2->setUniformItemSizes(true);

    ui->lineEdit->setFocus();

    this->setWindowTitle("Select signals");
}

SignalSelect::~SignalSelect()
{
    delete ui;
}

void SignalSelect::on_pushButton_clicked()                      //select the current signal
{
    QModelIndex current = ui->listWidget->currentIndex();
    if(current.isValid())
    {
        QModelIndex index = updateWidgets(current,true);

        if(index.row() < ui->listWidget->count() - 1){
            ui->listWidget->setCurrentIndex(index);
        }
    }
}

void SignalSelect::on_pushButton_2_clicked()                    //deselect the current signal
{
    if(ui->listWidget_2->currentIndex().isValid())
    {
        QModelIndex current = ui->listWidget_2->currentIndex();

        QModelIndex index = updateWidgets(current,false);

        if(index.row() < ui->listWidget->count() - 1){
            ui->listWidget_2->setCurrentIndex(index);
        }
    }
}

void SignalSelect::on_pushButton_5_clicked()                    //OK buttok (close with save)
{
    oldSelectedSignals->clear();
    oldNotSelectedSignals->clear();
    oldSelectedSignals->append(*selectedSignals);
    oldNotSelectedSignals->append(*notSelectedSignals);
    emit updateSignalsSignal();
    this->close();
}

void SignalSelect::on_pushButton_6_clicked()                    //CANCEL button (close without save)
{
    this->close();
}

void SignalSelect::on_pushButton_3_clicked()                    //UP button (change the signal position)
{
    QModelIndex current = ui->listWidget_2->currentIndex();
    if(current.isValid())
    {
        selectedSignals->move(current.row(), current.row() - 1);
        QModelIndex newIndex = refreshWidgets(ui->listWidget_2->currentIndex());
        newIndex = newIndex.sibling(newIndex.row() - 1, newIndex.column());
        ui->listWidget_2->setCurrentIndex(newIndex);
    }
}

void SignalSelect::on_pushButton_4_clicked()                    //DOWN button (change the signal position)
{
    QModelIndex current = ui->listWidget_2->currentIndex();
    if(current.isValid())
    {
        selectedSignals->move(current.row(), current.row() + 1);
        ui->listWidget_2->setCurrentIndex(refreshWidgets(ui->listWidget_2->currentIndex()));
    }
}

QModelIndex SignalSelect::refreshWidgets(QModelIndex index)
{
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    ui->listWidget->addItems(*filteredSignals);
    ui->listWidget_2->addItems(*selectedSignals);
    return index;
}

QModelIndex SignalSelect::updateWidgets(QModelIndex index, bool select)
{
    if(select)
    {
        QString str = filteredSignals->at(index.row());
        notSelectedSignals->removeOne(str);
        filteredSignals->removeOne(str);
        selectedSignals->append(str);
    }
    else
    {
        QString str = selectedSignals->at(index.row());
        selectedSignals->removeOne(str);
        notSelectedSignals->append(str);
        emit on_lineEdit_textChanged(ui->lineEdit->text());
    }
    refreshWidgets(index);
    if(!(index.isValid())) index = index.sibling(index.row() - 1, index.column());
    return index;
}

void SignalSelect::keyPressEvent(QKeyEvent* event)
{
    if((event->modifiers().testFlag(Qt::ControlModifier)) && (event->key() == Qt::Key_F))
    {
        ui->lineEdit->setFocus();
        ui->lineEdit->selectAll();
    }
}

void SignalSelect::on_pushButton_7_clicked()                        //REFRESH button (delete the changes)
{
    selectedSignals = new QStringList(*oldSelectedSignals);
    notSelectedSignals = new QStringList(*oldNotSelectedSignals);
    filteredSignals = new QStringList(*oldNotSelectedSignals);
    refreshWidgets(ui->listWidget->currentIndex());
    ui->lineEdit->clear();
}

void SignalSelect::on_lineEdit_textChanged(const QString &arg1)     //filter for signal list (emit when a character typed)
{
    if(arg1.size() <= 2){                 //if the writed text size as same as or shorter than this integer, the filter don't start
        filteredSignals = new QStringList(*notSelectedSignals);
        refreshWidgets(ui->listWidget->currentIndex());
        ui->lineEdit_2->setText("n.a.");
    }
    else
    {
        if(ui->checkBox->isChecked())
        {
            filteredSignals = new QStringList(notSelectedSignals->filter(ui->lineEdit->text(), Qt::CaseSensitive));
        }
        else
        {
            filteredSignals = new QStringList(notSelectedSignals->filter(ui->lineEdit->text(), Qt::CaseInsensitive));
        }
        refreshWidgets(ui->listWidget->currentIndex());
        ui->lineEdit_2->setText(QString::number(filteredSignals->size()));
    }
}

void SignalSelect::on_checkBox_clicked()                        //case sensitive filtering
{
    QPalette p = ui->checkBox->palette();
    QColor blue(0, 0, 255);
    p.setColor(QPalette::Active, QPalette::Highlight, blue);
    ui->checkBox->setPalette(p);
    emit on_lineEdit_textChanged(ui->lineEdit->text());
}

void SignalSelect::on_listWidget_doubleClicked(const QModelIndex&)
{
    emit on_pushButton_clicked();
    ui->pushButton_5->setFocus();
}

void SignalSelect::on_listWidget_2_doubleClicked(const QModelIndex&)
{
    emit on_pushButton_2_clicked();
    ui->pushButton_5->setFocus();
}


