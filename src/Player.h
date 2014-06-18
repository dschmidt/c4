#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class Player : public QObject
{
    Q_OBJECT

public:
    Player(const QString& name, QObject* parent = 0);
    virtual ~Player();

    virtual const QString name() const;
    virtual void move() = 0;

signals:
    void moved(int column);

private:
    QString m_name;
};

#endif // PLAYER_H
