#include "GameModel.h"

GameModel::GameModel(QObject *parent)
    : QObject(parent)
{
}

void GameModel::setPlayer1(Player *player1)
{
    m_player1 = player1;
}

void GameModel::setPlayer2(Player *player2)
{
    m_player2 = player2;
}
