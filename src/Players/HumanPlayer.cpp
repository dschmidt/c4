#include "HumanPlayer.h"

#include "../ARToolkitWidget.h"

void HumanPlayer::move()
{
}

void HumanPlayer::setGameWidget(ARToolkitWidget *gameWidget)
{
    gameWidget->disconnect(this);
    m_gameWidget = gameWidget;

    connect(m_gameWidget, SIGNAL(arChipDropped(int)), SIGNAL(moved(int)));
}
