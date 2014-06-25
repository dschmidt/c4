#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include "Player.h"

#include <QObject>

class GameModel : public QObject
{
    Q_OBJECT
public:
    explicit GameModel( QObject *parent = 0 );
    void dropChip( int column, Player* currentPlayer );

    Player* player1() const;
    void setPlayer1(Player* player1);

    Player* player2() const;
    void setPlayer2(Player* player2);


    Player* field[6][7];

signals:
    void dataChipDropped( bool success, int column, Player* player );
    void gameFinished(Player* winner);

private:
    Player* m_player1;
    Player* m_player2;

    bool checkFinished(int row, int column, Player* currentPlayer);
};

#endif // GAMEMODEL_H
