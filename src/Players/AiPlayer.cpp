#include "AiPlayer.h"

#include <QDebug>

AiPlayer::AiPlayer(const QString& name, QObject* parent)
    : Player(name, parent)
{
}

void AiPlayer::move(Player* field[6][7])
{
    qDebug() << Q_FUNC_INFO;

    emit moved(4);
    return;

    bool found = false;
    int i,j;
    for(i=0;i<7;i++){
        targetRows[i]=-1;
    }
    for(j=0;j<7;j++){
        for(i=0;i<6;i++ ){
            if(field[i][j]== NULL && i>0){
                if(field[i-1][j]!= NULL){
                    targetRows[j] = i;
                    break;
                }
            }
        }
    }
    for(i=0;i<7;i++){
        if(targetRows[i] >= 0){
            found = check4(targetRows[i],i,field);
        }
        if(found){
            emit moved(i);
        }
    }

}
// checks if the AiPlayer can get 4 or avoid oponents 4 at field[row][column]
bool AiPlayer::check4(int row, int column, Player* field[6][7]){
    Player* tempPlayer;

    // for the column
    if(row > 2){
       tempPlayer = field[row-1][column];
       if(field[row-2][column]==tempPlayer && field[row-3][column]==tempPlayer){
           return true;
       }
    }

    // for the row
    int i;
    int counter = 0;
    for(i=0;i<7;i++){
        if(field[row][i]!=NULL){
            if(tempPlayer==NULL){
                tempPlayer = field[row][i];
                counter = 1;
            }else if(tempPlayer == field[row][i]){
                counter++;
            }else{
                tempPlayer = field[row][i];
                counter = 1;
            }
        }else if(i==column){
            if(counter >= 3){
                return true;
            }else if(counter == 2 && column<6){
                if(tempPlayer==field[row][column+1]){
                    return true;
                }
            }else if(counter == 1 && column<5){
                if(tempPlayer==field[row][column+1] && tempPlayer==field[row][column+2]){
                    return true;
                }
            }else if(column<4){
                if(tempPlayer==field[row][column+1] && tempPlayer==field[row][column+2] && tempPlayer==field[row][column+3]){
                    return true;
                }
            }
        }
    }

    //for the diagonals
    // i :: row ; j :: column
    counter = 0;
    int yAchsenSchnitt = row-column;
    int j;
    if(yAchsenSchnitt >=0){
        i = yAchsenSchnitt;
        j = 0;
    }else{
        i = 0;
        j = -yAchsenSchnitt;
    }
    for(;i<6 && j<7;i++,j++){
        if(field[i][j]!= NULL){
            if(field[i][j] == tempPlayer){
                counter++;
            }else{
                counter = 1;
                tempPlayer = field[i][j];
            }
        }else if(i==row && j==column){

        }
    }


    return false;
}
