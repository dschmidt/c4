#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>

class Player;

class GameController : public QObject
{
    Q_OBJECT

public:
    explicit GameController(QObject* parent = 0);

private slots:
    void onMoved(int column);

private:
    Player* m_currentPlayer;
};

#endif // GAMECONTROLLER_H
