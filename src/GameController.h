#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>

class Player;
class GameModel;
class GameWidget;

class GameController : public QObject
{
    Q_OBJECT

public:
    explicit GameController(QObject* parent = 0);
    void setGameModel(GameModel* model);
    void startGame();

private slots:
    void onMoved(int column);

private:
    Player* m_currentPlayer;
    GameModel* m_model;
    GameWidget* m_widget;
};

#endif // GAMECONTROLLER_H
