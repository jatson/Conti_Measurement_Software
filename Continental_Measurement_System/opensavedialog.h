#ifndef OPENSAVEDIALOG_H
#define OPENSAVEDIALOG_H

#include <QDialog>
#include <QtCore>
#include <QDirModel>
#include <QInputDialog>

namespace Ui {
class OpenSaveDialog;
}

class OpenSaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpenSaveDialog(QString windowName, QString buttonText, int isOpen,  QWidget *parent = 0);
    ~OpenSaveDialog();

private:
    Ui::OpenSaveDialog *ui;
    QDirModel *model;
    QString name;
    QString path;
    int open;

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void on_treeView_clicked(const QModelIndex &index);
    void on_pushButton_2_clicked();

signals:
    void fileSelectedSignal(QString path, QString fileName);
};

#endif // OPENSAVEDIALOG_H
