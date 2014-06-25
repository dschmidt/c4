#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QString>
#include <QColor>

class Player : public QObject
{
    Q_OBJECT

public:
    Player(const QString& name, QObject* parent = 0);
    virtual ~Player();

    virtual const QString name() const;
    virtual void move(Player* field[6][7]) = 0;

    const QColor color() const;
    void setColor(const QColor& color);

signals:
    void moved(int column);

private:
    QString m_name;
    QColor m_color;
};

#endif // PLAYER_H
