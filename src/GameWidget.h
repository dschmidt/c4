#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include "ARToolkitWidget.h"

class GlChip;
class GlField;

class GameWidget : public ARToolkitWidget
{
public:
    GameWidget(QWidget *parent = 0);
    void drawObjects();

private:
    Pattern* pattChip;
    Pattern* pattField;
    GlChip* chip;
    GlField* field;

signals:
//    void arChipDropped(int column);

protected:
    virtual void timerEvent(QTimerEvent* event);
    // HACK
    virtual void mousePressEvent(QMouseEvent* event);
};

#endif // GAMEWIDGET_H
