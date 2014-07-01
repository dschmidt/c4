#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "../Player.h"

class AiPlayer : public Player
{
public:
    AiPlayer(const QString& name, QObject* parent = 0);

    void move(Player *field[6][7]);

    bool check4(int row, int column, Player *field[6][7]);
    bool check4Win(int row, int column, Player *field[6][7]);


private:
    int targetRows[7];


};

#endif // AIPLAYER_H
