#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "../Player.h"

class GameWidget;

class HumanPlayer : public Player
{
public:
    HumanPlayer(const QString& name, QObject* parent = 0);

    void move(Player *field[6][7]);

    void setGameWidget(GameWidget* gameWidget);

//private slots:
//    void onArChipDropped(int column);

private:
    GameWidget* m_gameWidget;
};

#endif // HUMANPLAYER_H
