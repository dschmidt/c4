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

signals:
    void dataChipDropped( bool success, int column, Player* player );
    void gameFinished();
};

#endif // GAMEMODEL_H
