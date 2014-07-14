#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QTimer>

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
    void gameStarted();

private slots:
    void onColorNameChanged();
    void onMoved(int column);
    void onDataChipDropped(bool success, int column, Player* player);
    void onNextPlayer();
    Player* createPlayerWithLevel(QString name, int level);

private:
    Player* m_currentPlayer;
    GameModel* m_model;
    GameWidget* m_widget;
    QTimer m_turnChangeTimer;
};

#endif // GAMECONTROLLER_H
