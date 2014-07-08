#include "GameController.h"

#include "Players/HumanPlayer.h"
#include "Players/AiPlayer.h"
#include "Players/AiPlayerGood.h"
#include "GameModel.h"
#include "Settings.h"
#include "GameWidget.h"

#include <QDebug>
#include <QTimer>

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
    connect(Settings::instance(), SIGNAL(settingsChanged()),this , SLOT(onColorNameChanged()));
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

void GameController::onColorNameChanged()
{
    startGame();
}

void GameController::startGame()
{
    Player* player1 = createPlayerWithLevel(Settings::instance()->playerName(),Settings::instance()->playerLevel());
    player1->setColor(Settings::instance()->playerColor());
    if (m_model->player1() != NULL)
    {
        m_model->player1()->deleteLater();
        m_model->player1()->disconnect();
    }
    m_model->setPlayer1(player1);
    Player* player2 = createPlayerWithLevel(Settings::instance()->aiName(),Settings::instance()->aiLevel());
    player2->setColor(Settings::instance()->aiColor());
    if (m_model->player2() != NULL)
    {
        m_model->player2()->deleteLater();
        m_model->player2()->disconnect();
    }
    m_model->setPlayer2(player2);
    emit gameStarted();
    restartGame();
}

Player* GameController::createPlayerWithLevel(QString name, int level)
{
    Player* player;
    switch (level)
    {
        case 1:
            player = new AiPlayer(name, this);
            break;
        case 2:
            player = new AiPlayerGood(name, this);
            break;
        case 3:
            //AI Player Hard still missing
            player = new AiPlayerGood(name, this);
            break;
        case 4:
            //AI Player Chuck Norris still missing
            player = new AiPlayerGood(name, this);
            break;
        default:
            player = new HumanPlayer(name, this);
            ((HumanPlayer*)player)->setGameWidget(m_widget);
    }
    return player;
}

void GameController::restartGame()
{
    qDebug() << "****** Start new game";

    m_model->resetField();

    int playerNumber = qrand() % 2;
    if(playerNumber == 0)
    {
        m_currentPlayer = m_model->player1();
    }
    else
    {
        m_currentPlayer = m_model->player2();
    }
    //connect signals of current player
    connect(m_currentPlayer, SIGNAL(moved(int)), SLOT(onMoved(int)));
    emit currentPlayerChange(m_currentPlayer);
    m_currentPlayer->move(m_model->field);
}

void GameController::onMoved(int column)
{
    Player* player = qobject_cast<Player*>(sender());

    //qDebug() << "Player" <<  player->name() << "moved: " << column+1;

    if(m_model && m_currentPlayer == player)
    {
        m_model->dropChip(column, player);
    }
    else
    {
        //qDebug() << "Player" << player->name() << "tried to move although it wasn't his turn";
    }
}

void GameController::onDataChipDropped(bool success, int column, Player *player)
{
    if(success)
    {
        m_currentPlayer->disconnect(SIGNAL(moved(int)));
        QTimer::singleShot(200,this, SLOT(onNextPlayer()));
        //m_currentPlayer->move(m_model->field);
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "Move failed, let player repeat input";
    }
}

void GameController::onNextPlayer()
{
    if(m_currentPlayer == m_model->player1())
    {
        m_currentPlayer = m_model->player2();
    }
    else
    {
        m_currentPlayer = m_model->player1();
    }
    connect(m_currentPlayer, SIGNAL(moved(int)), SLOT(onMoved(int)));
    m_currentPlayer->move(m_model->field);
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
