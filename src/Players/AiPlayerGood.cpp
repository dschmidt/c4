#include "AiPlayerGood.h"

#include <QDebug>
#include <ctime>

AiPlayerGood::AiPlayerGood(const QString& name, QObject* parent)
    : AiPlayer(name, parent)
{
}

void AiPlayerGood::move(Player* field[6][7])
{
    qDebug() << Q_FUNC_INFO;


    int i;
    bool isEmpty = true;
    for(i=0;i<7;i++){
        if(field[0][i] != NULL){
            isEmpty = false;
        }
    }
    if(isEmpty){
        emit moved(3);
    }



    bool found = false;
    int j;
    for(i=0;i<7;i++){
        targetRows[i]=-1;
    }
    for(j=0;j<7;j++){
        for(i=0;i<6;i++ ){
            if(field[i][j]== NULL){
                if(i==0){
                    targetRows[j] = 0;
                    break;
                }else if(field[i-1][j]!= NULL){
                    targetRows[j] = i;
                    break;
                }
            }
        }
    }
    for(i=0;i<7;i++){
            qDebug() << targetRows[i];
    }
    for(i=0;i<7;i++){
        if(targetRows[i] >= 0){
            found = check4(targetRows[i],i,field);
        }
        if(found){
            emit moved(i);
            return;
        }
    }
    //default: random drop
    int random;
    srand(time(0));
    for(i=0;i<10;i++){
        random = rand()%7;
        if(targetRows[random]>=0){
            emit moved(random);
            return;
        }
    }
    //if random drop fails
    for(i=0;i<7;i++){
        if(targetRows[i]>=0){
            emit moved(i);
            return;
        }
    }

}
