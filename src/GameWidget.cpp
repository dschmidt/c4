#include "GameWidget.h"

#include <QDebug>

GameWidget::GameWidget(QWidget* parent)
    : ARToolkitWidget(parent)
{
}

void GameWidget::mousePressEvent ( QMouseEvent * event )
{
    int column = qrand() * 6;

    qDebug() << Q_FUNC_INFO << column;

    //emit arChipDropped(column);
}
