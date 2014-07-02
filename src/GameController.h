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
    void setGameWidget(GameWidget* widget);

    void restartGame();
    void startGame();
    void loadGameState();
    QString getGameState();

signals:
    void currentPlayerChange(Player* player);

private slots:
    void colorNameChanged();
    void onMoved(int column);
    void onDataChipDropped(bool success, int column, Player* player);

private:
    Player* m_currentPlayer;
    GameModel* m_model;
    GameWidget* m_widget;
};

#endif // GAMECONTROLLER_H
