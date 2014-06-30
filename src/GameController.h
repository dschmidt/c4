#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>

class Player;
class GameModel;
class ARToolkitWidget;

class GameController : public QObject
{
    Q_OBJECT

public:
    explicit GameController(QObject* parent = 0);
    void setGameModel(GameModel* model);
    void setGameWidget(ARToolkitWidget* model);
    void startGame();
    void restartGame();

private slots:
    void onMoved(int column);
    void onDataChipDropped(bool success, int column, Player* player);

private:
    Player* m_currentPlayer;
    GameModel* m_model;
    ARToolkitWidget* m_widget;
};

#endif // GAMECONTROLLER_H
