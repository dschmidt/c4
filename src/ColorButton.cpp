#include "ColorButton.h"

#include <QColorDialog>

ColorButton::ColorButton(QWidget* parent)
    : QPushButton(parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(openColorDialog()));
}

void ColorButton::setColor(const QColor &color)
{
    m_color = color;

    setStyleSheet("ColorButton { background-color: " + color.name() + " }");
}

const QColor ColorButton::color() const
{
    return m_color;
}

void ColorButton::openColorDialog()
{
    QColorDialog* colorDialog = new QColorDialog(this);
    colorDialog->setModal(true);

    connect(colorDialog, SIGNAL(colorSelected(QColor)), this, SLOT(setColor(QColor)));
    colorDialog->open();
}


