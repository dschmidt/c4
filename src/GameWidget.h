#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include "ARToolkitWidget.h"

class GameWidget : public ARToolkitWidget
{
public:
    GameWidget();

signals:
    void arChipDropped();
};

#endif // GAMEWIDGET_H
