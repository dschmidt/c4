#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "../Player.h"

class ARToolkitWidget;

class HumanPlayer : public Player
{
public:
    HumanPlayer(const QString& name, QObject* parent = 0);

    void move(Player *field[6][7]);

    void setGameWidget(ARToolkitWidget* gameWidget);

//private slots:
//    void onArChipDropped(int column);

private:
    ARToolkitWidget* m_gameWidget;
};

#endif // HUMANPLAYER_H
