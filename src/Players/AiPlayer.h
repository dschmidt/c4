#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "../Player.h"

class AiPlayer : public Player
{
public:
    AiPlayer(const QString& name, QObject* parent = 0);

    void move();
};

#endif // AIPLAYER_H
