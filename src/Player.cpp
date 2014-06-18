#include "Player.h"

Player::Player(const QString &name, QObject* parent)
    : QObject(parent)
    , m_name(name)
{

}

Player::~Player()
{
}

const QString Player::name() const
{
    return m_name;
}
