#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include "ARToolkitWidget.h"

class GameWidget : public ARToolkitWidget
{
public:
    GameWidget(QWidget* parent = 0);

signals:
//    void arChipDropped(int column);

protected:
    // HACK
    virtual void mousePressEvent ( QMouseEvent * event );
};

#endif // GAMEWIDGET_H
