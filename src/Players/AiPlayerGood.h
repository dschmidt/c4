#ifndef AIPLAYERGOOD_H
#define AIPLAYERGOOD_H

#include "../Player.h"

class AiPlayerGood : public Player
{
public:
    AiPlayerGood(const QString& name, QObject* parent = 0);

    void move(Player *field[6][7]);
    bool check4(int row, int column, Player *field[6][7]);


private:
    int targetRows[7];
};

#endif // AIPLAYERGOOD_H
