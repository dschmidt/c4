#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include "ARToolkitWidget.h"

class GlChip;
class GlField;

class GameWidget : public ARToolkitWidget
{
    Q_OBJECT

public:
    GameWidget(QWidget *parent = 0);
    void drawObjects();
    void setGameModel(GameModel* model);

signals:
    void arChipDropped(int column);

protected:
    void keyPressEvent( QKeyEvent* event );
    virtual void timerEvent(QTimerEvent* event);

private:
    Pattern* pattChip;
    Pattern* pattField;
    GlChip* chip;
    GlField* field;
    GameModel* m_model;
};

#endif // GAMEWIDGET_H
