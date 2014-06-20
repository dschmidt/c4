#include "GameController.h"

#include "Players/HumanPlayer.h"
#include "Players/AiPlayer.h"
#include "GameModel.h"

GameController::GameController( QObject* parent )
    : QObject(parent)
    , m_currentPlayer(0)
    , m_model(0)
{
}

void GameController::setGameModel( GameModel* model )
{
    m_model = model;
}

void GameController::setGameWidget( ARToolkitWidget* widget )
{
    m_widget = widget;
}


void GameController::startGame()
{
    HumanPlayer* player1 = new HumanPlayer(QLatin1String("Knalltuete"), this);
    player1->setGameWidget(m_widget);
    m_model->setPlayer1(player1);
    connect(player1, SIGNAL(moved(int)), SLOT(onMoved(int)));


    Player* player2 = new AiPlayer(QLatin1String("Hans Wurst"), this);
    m_model->setPlayer2(player2);


    m_currentPlayer = player1;
}


void GameController::onMoved(int column)
{

}
