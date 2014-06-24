#include "HumanPlayer.h"

#include "../ARToolkitWidget.h"

HumanPlayer::HumanPlayer(const QString& name, QObject* parent)
    : Player(name, parent)
    , m_gameWidget(0)
{
}

void HumanPlayer::move(Player* field[6][7])
{
}

void HumanPlayer::setGameWidget(ARToolkitWidget *gameWidget)
{
    if (m_gameWidget)
    {
        m_gameWidget->disconnect(this);
    }

    m_gameWidget = gameWidget;

    connect(m_gameWidget, SIGNAL(arChipDropped(int)), SIGNAL(moved(int)));
}
