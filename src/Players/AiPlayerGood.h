#ifndef AIPLAYERGOOD_H
#define AIPLAYERGOOD_H

#include "AiPlayer.h"

class AiPlayerGood : public AiPlayer
{
public:
    AiPlayerGood(const QString& name, QObject* parent = 0);

    void move(Player *field[6][7]);
    bool check4Lost(int row, int column, Player *field[6][7]);


private:
    int targetRows[7];
};

#endif // AIPLAYERGOOD_H
