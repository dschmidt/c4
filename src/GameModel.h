#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include "Player.h"

#include <QObject>

class GameResult;

class GameModel : public QObject
{
    Q_OBJECT
public:
    explicit GameModel( QObject *parent = 0 );
    virtual ~GameModel();

    void dropChip( int column, Player* currentPlayer );

    Player* player1() const;
    void setPlayer1(Player* player1);

    Player* player2() const;
    void setPlayer2(Player* player2);

    Player* field[6][7];
    void resetField();

    int wins(Player* player) const;

    QString getGame();
    void setGame(QString saveGame);

signals:
    void dataChipDropped( bool success, int column, Player* player );
    void gameFinished(Player* winner);
    void gameFinishedWithResult(GameResult* result);

private slots:
    void onGameFinished(Player* winner);

private:
    bool m_gameFinished;
    Player* m_player1;
    Player* m_player2;

    QList< GameResult* > m_results;

    bool checkFinished(int row, int column, Player* currentPlayer);
};

#endif // GAMEMODEL_H
