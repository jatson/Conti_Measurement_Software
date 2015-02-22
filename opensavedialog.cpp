#include "opensavedialog.h"
#include "ui_opensavedialog.h"

OpenSaveDialog::OpenSaveDialog(QString windowName, QString buttonText, int isOpen, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenSaveDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(windowName);
    ui->pushButton_2->setText(buttonText);
    open = isOpen;
    model = new QDirModel(this);
    model->setReadOnly(false);
    model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);

    ui->treeView->setModel(model);

    ui->pushButton_2->setFocus();
}

OpenSaveDialog::~OpenSaveDialog()
{
    delete ui;
}

void OpenSaveDialog::on_pushButton_3_clicked()
{
    this->close();
}

void OpenSaveDialog::on_pushButton_clicked()
{
    QModelIndex index = ui->treeView->currentIndex();
    if(!index.isValid()) return;
    if(!model->isDir(index)) return;
    QString name = QInputDialog::getText(this, "Name", "Enter a name");
    if(name.isEmpty()) return;

    model->mkdir(index, name);
}

void OpenSaveDialog::on_treeView_clicked(const QModelIndex &index)
{
    if(open){
        if(model->isDir(index)) return;
        name = model->fileName(index);
        if(!name.endsWith(".mdf") && !name.endsWith(".prof")){
            ui->lineEdit->clear();
            name.clear();
            path.clear();
            return;
        }
        ui->lineEdit->setText(name);
        path = model->filePath(index);
        path.remove(name);
    }
    else
    {
        if(!model->isDir(index)) return;
        path = model->filePath(index);
    }
}

void OpenSaveDialog::on_pushButton_2_clicked()
{
    if(!open) name = ui->lineEdit->text();
    if(name.isEmpty() || path.isEmpty()) return;
    if(!open && !name.endsWith(".prof")) name += ".prof";
    emit fileSelectedSignal(path, name);
    this->close();
}
