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

    void setPlayer1(Player* player1);
    void setPlayer2(Player* player2);

signals:
    void dataChipDropped( bool success, int column, Player* player );
    void gameFinished();

private:
    Player* m_player1;
    Player* m_player2;
};

#endif // GAMEMODEL_H
