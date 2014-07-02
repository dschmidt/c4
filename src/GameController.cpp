#include "GameController.h"

#include "Players/HumanPlayer.h"
#include "Players/AiPlayer.h"
#include "Players/AiPlayerGood.h"
#include "GameModel.h"
#include "Settings.h"

#include <QDebug>

GameController::GameController( QObject* parent )
    : QObject(parent)
    , m_currentPlayer(0)
    , m_model(0)
{
}

void GameController::setGameModel( GameModel* model )
{
    if(m_model)
    {
        m_model->disconnect(this);
    }

    m_model = model;
    connect(m_model, SIGNAL(dataChipDropped(bool, int, Player*)), SLOT(onDataChipDropped(bool, int, Player*)));
}

void GameController::setGameWidget( ARToolkitWidget* widget )
{
    m_widget = widget;
}


void GameController::startGame()
{
    HumanPlayer* player1 = new HumanPlayer(Settings::instance()->playerName(), this);
    player1->setColor(Settings::instance()->playerColor());
    player1->setGameWidget(m_widget);

    m_model->setPlayer1(player1);
    connect(player1, SIGNAL(moved(int)), SLOT(onMoved(int)));

    Player* player2 = new AiPlayer(Settings::instance()->aiName(), this);
    player2->setColor(Settings::instance()->aiColor());
    //Player* player2 = new AiPlayerGood(QLatin1String("Ai"), this);
    player2->setColor(QColor(Qt::yellow));
    m_model->setPlayer2(player2);
    connect(player2, SIGNAL(moved(int)), SLOT(onMoved(int)));

    restartGame();
}

void GameController::restartGame()
{
    qDebug() << "****** Start new game";

    m_model->resetField();

    int playerNumber = qrand() % 1;
    if(playerNumber == 0)
    {
        m_currentPlayer = m_model->player1();
    }
    else
    {
        m_currentPlayer = m_model->player2();
    }

    m_currentPlayer->move(m_model->field);
}

void GameController::onMoved(int column)
{
    Player* player = qobject_cast<Player*>(sender());

    qDebug() << "Player" <<  player->name() << "moved: " << column+1;

    if(m_model && m_currentPlayer == player)
    {
        m_model->dropChip(column, player);
    }
    else
    {
        qDebug() << "Player" << player->name() << "tried to move although it wasn't his turn";
    }
}

void GameController::onDataChipDropped(bool success, int column, Player *player)
{
    if(success)
    {
        qDebug() << Q_FUNC_INFO << "Successful move, over to the next player";
        if(m_currentPlayer == m_model->player1())
        {
            m_currentPlayer = m_model->player2();
        }
        else
        {
            m_currentPlayer = m_model->player1();
        }

        m_currentPlayer->move(m_model->field);
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "Move failed, let player repeat input";
    }
}

QString GameController::saveGame(){
        QString save(m_model->player1()->name()+"|"+m_model->player2()->name() + "|"+ Settings::instance()->aiLevel() +"|");
        return save + m_model->getGame();
}

void GameController::loadGame(QString save,QString players, int aiLevel){
    //loads player names and ai configuration out of a string into the gamemodel
    if (save.length() < 42)
    {
        return;
    }
    size_t mid;
    mid = players.toStdString().find_first_of("|",0);
    Settings::instance()->setAiLevel(aiLevel);
    Settings::instance()->setPlayerName(players.left(static_cast<int>(mid)));
    Settings::instance()->setAiName(players.remove(0,static_cast<unsigned int>(mid)+1));
    startGame();
    //string with chip-position given to the gamemodel
    m_model->setGame(save);
}
