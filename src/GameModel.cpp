#include "GameModel.h"

GameModel::GameModel(QObject *parent)
    : QObject(parent)
    , m_player1(0)
    , m_player2(0)
{
}

Player* GameModel::player1() const
{
    return m_player1;
}

void GameModel::setPlayer1(Player *player1)
{
    m_player1 = player1;
}

Player* GameModel::player2() const
{
    return m_player2;
}

void GameModel::setPlayer2(Player *player2)
{
    m_player2 = player2;
}

void GameModel::dropChip(int column, Player *currentPlayer)
{
    emit dataChipDropped(true, column, currentPlayer);
    emit gameFinished();
}
