#include "signallabel.h"

SignalLabel::SignalLabel(QCheckBox *chb, const QString &text)
{
    this->setText(text);
    checkbox = chb;
    dataPrecision = 2;
}

SignalLabel::SignalLabel(QCheckBox *chb, int index, QList<double>* data, const QString &unit, int row, SignalChart* chart)
{
    checkbox = chb;
    this->data = data;
    this->setText(QString::number(data->at(index)));
    this->unit = new SignalLabel(chb, unit);
    dataPrecision = 2;
    this->row = row;
    connect(checkbox, SIGNAL(clicked()), this, SLOT(checkboxCheckedSlot()));
    this->chart = chart;
}

void SignalLabel::setData(int index)
{
    this->setText(QString::number(data->at(index),'f', dataPrecision));
}

SignalLabel *SignalLabel::getUnitLabel()
{
    return unit;
}

int SignalLabel::getNumOfData()
{
    return data->size();
}

void SignalLabel::setActions(QAction *color, QAction *vertShift, QAction *vertStretch)
{
    colorAct = color;
    vertShiftAct = vertShift;
    vertStretchAct = vertStretch;
    QPixmap* pixmap = new QPixmap(20,20);
    pixmap->fill(*(chart->getColor()));
    QIcon* icon = new QIcon(*pixmap);
    colorAct->setIcon(*icon);

    connect(colorAct, SIGNAL(triggered()), this, SLOT(colorActTriggSlot()));
    connect(vertShiftAct, SIGNAL(triggered()), this, SLOT(vertShiftActTriggSlot()));
    connect(vertStretchAct, SIGNAL(triggered()), this, SLOT(vertStretchActTriggSlot()));
}

void SignalLabel::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton) checkbox->setChecked(!checkbox->isChecked());
}

void SignalLabel::checkboxCheckedSlot()
{
    emit selectRowSignal(row);
}

void SignalLabel::colorActTriggSlot()
{
    ColorChangeDialog* dialog = new ColorChangeDialog(chart->getColorIndex(), this);
    dialog->show();
    connect(dialog, SIGNAL(colorChangedSignal(int)), this, SLOT(changeColorSlot(int)));
}

void SignalLabel::vertShiftActTriggSlot()
{
    int value = QInputDialog::getInt(this, "Vertical offset", "Enter the vertical offset [pixel]", chart->getOffsetY(), -1000, 1000, 10);
    chart->setOffsetY(value);
}

void SignalLabel::vertStretchActTriggSlot()
{
    double value = QInputDialog::getDouble(this, "Vertical stretch", "Enter the vertical stretch [rate]", chart->getRateY(), 0.1, 100, 1);
    chart->setRateY(value);
}

void SignalLabel::changeColorSlot(int index)
{
    chart->changeColor(index);

    QPixmap* pixmap = new QPixmap(20,20);
    pixmap->fill(*(chart->getColor()));
    QIcon* icon = new QIcon(*pixmap);
    colorAct->setIcon(*icon);
}
