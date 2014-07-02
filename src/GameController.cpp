#include "GameController.h"

#include "Players/HumanPlayer.h"
#include "Players/AiPlayer.h"
#include "Players/AiPlayerGood.h"
#include "GameModel.h"
#include "Settings.h"
#include "GameWidget.h"

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
    connect(Settings::instance(), SIGNAL(settingsChanged()),this , SLOT(colorNameChanged()));
}

void GameController::setGameWidget(GameWidget* widget )
{
    if(m_widget)
    {
        disconnect(m_widget);
    }

    m_widget = widget;
    connect(this, SIGNAL(currentPlayerChange(Player*)), m_widget, SLOT(onCurrentPlayerChanged(Player*)));
}

void GameController::colorNameChanged()
{
    startGame();
}

void GameController::startGame()
{
    HumanPlayer* player1 = new HumanPlayer(Settings::instance()->playerName(), this);
    player1->setColor(Settings::instance()->playerColor());
    player1->setGameWidget(m_widget);
    if (m_model->player1() != NULL)
    {
        m_model->player1()->deleteLater();
        m_model->player1()->disconnect();

    }
    m_model->setPlayer1(player1);
    connect(player1, SIGNAL(moved(int)), SLOT(onMoved(int)));
    Player* player2;
    if (Settings::instance()->aiLevel() == 0)
    {
        player2 = new HumanPlayer(Settings::instance()->aiName(), this);
        player2->setColor(Settings::instance()->aiColor());
        ((HumanPlayer*)player2)->setGameWidget(m_widget);
    }
    else
    {
        player2 = new AiPlayer(Settings::instance()->aiName(), this);
        player2->setColor(Settings::instance()->aiColor());
    }
    if (m_model->player2() != NULL)
    {
        m_model->player2()->deleteLater();
        m_model->player2()->disconnect();
    }
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

    // change current player
    emit currentPlayerChange(m_currentPlayer);
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

QString GameController::getGameState(){
        QString save(m_model->player1()->name()+"|"+m_model->player2()->name() + "|"+ Settings::instance()->aiLevel() +"|");
        return save + m_model->getGame();
}

void GameController::loadGameState(){
    //loads player names and ai configuration out of a string into the gamemodel
    QStringList saveGame = Settings::instance()->quickSave().split("|");
    if ((saveGame.length() < 3)||(saveGame.at(3).length() < 42)){
        startGame();
        return;
    }
    Settings::instance()->setAiLevel(saveGame.at(2).toInt());
    Settings::instance()->setPlayerName(saveGame.at(0));
    Settings::instance()->setAiName(saveGame.at(1));
    startGame();
    //string with chip-position given to the gamemodel
    m_model->setGame(saveGame.at(3));
    qDebug()<< ("load complete: Players: " + saveGame.at(0) + " vs " + saveGame.at(1));
}
