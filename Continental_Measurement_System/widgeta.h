#ifndef WIDGETA_H
#define WIDGETA_H

#include <QWidget>
#include "modelmanager.h"

namespace Ui {
class WidgetA;
}

class WidgetA : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetA(QWidget *parent = 0);
    ~WidgetA();

    ModelManager* m_modelManager;

    void setModel(ModelManager * model);

private:
    Ui::WidgetA *ui;

public slots:
    void dataChangedOnModel();
};

#endif // WIDGETA_H
