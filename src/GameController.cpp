#include "GameController.h"

#include "Players/HumanPlayer.h"
#include "Players/AiPlayer.h"
#include "GameModel.h"

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
    HumanPlayer* player1 = new HumanPlayer(QLatin1String("Human"), this);
    player1->setColor(QColor(Qt::red));
    player1->setGameWidget(m_widget);

    m_model->setPlayer1(player1);
    connect(player1, SIGNAL(moved(int)), SLOT(onMoved(int)));

    Player* player2 = new AiPlayer(QLatin1String("Ai"), this);
    player2->setColor(QColor(Qt::yellow));
    m_model->setPlayer2(player2);
    connect(player2, SIGNAL(moved(int)), SLOT(onMoved(int)));


    m_currentPlayer = player2;
    m_currentPlayer->move(m_model->field);
}


void GameController::onMoved(int column)
{
    Player* player = qobject_cast<Player*>(sender());

    qDebug() << "Player" <<  player->name() << "moved: " << column;

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
