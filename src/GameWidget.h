#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include "ARToolkitWidget.h"

class GlChip;
class GlField;

class GameWidget : public ARToolkitWidget
{
public:
    GameWidget(QWidget *parent);
    void drawObjects();

private:
    Pattern* pattChip;
    Pattern* pattField;
    GlChip* chip;
    GlField* field;

signals:
    void arChipDropped();
};

#endif // GAMEWIDGET_H
