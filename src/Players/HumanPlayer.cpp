#include "HumanPlayer.h"

#include "../GameWidget.h"

#include <QDebug>
#include <QString>
#include <string>
using namespace std;

HumanPlayer::HumanPlayer(const QString& name, QObject* parent)
    : Player(name, parent)
    , m_gameWidget(0)
{
}

void HumanPlayer::move(Player* field[6][7])
{
    string a = "";
    int i,j;
    for(i=5; i>=0; i--){
        a = "";
        for(j=0; j<7; j++){
            if(field[i][j]!=NULL){
                if(field[i][j]==this){
                    a += "o";
                }else{
                    a += "x";
                }
            }else{
                a += " ";
            }
            if(j!=6){
                a+= " ";
            }
        }
        qDebug() << QString(a.c_str());
    }
    qDebug() << Q_FUNC_INFO;
}

void HumanPlayer::setGameWidget(GameWidget *gameWidget)
{
    if (m_gameWidget)
    {
        m_gameWidget->disconnect(this);
    }

    m_gameWidget = gameWidget;

    connect(m_gameWidget, SIGNAL(arChipDropped(int)), SIGNAL(moved(int)));
}
