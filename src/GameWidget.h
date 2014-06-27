#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include "ARToolkitWidget.h"

class GlChip;
class GlField;
class Player;

class GameWidget : public ARToolkitWidget
{
    Q_OBJECT

public:
    GameWidget(QWidget *parent = 0);
    void setGameModel(GameModel* model);
    GameModel* gameModel();

signals:
    void arChipDropped(int column);
    void arHighlightColumn(int column);

protected:
    void keyPressEvent( QKeyEvent* event );
    virtual void timerEvent(QTimerEvent* event);

private slots:
    void onGameFinished(Player* winner);

private:
    Pattern* pattChip;
    Pattern* pattField;
    GlChip* chip;
    GlField* field;
    GameModel* m_model;
    bool alreadyEmitted;
};

#endif // GAMEWIDGET_H
