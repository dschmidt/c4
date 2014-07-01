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
        return;
    }



    bool found = false;
    int j;
    int targetCounter = 0;
    for(i=0;i<7;i++){
        targetRows[i]=-1;
    }
    for(j=0;j<7;j++){
        for(i=0;i<6;i++ ){
            if(field[i][j]== NULL){
                if(i==0){
                    targetRows[j] = 0;
                    targetCounter++;
                    break;
                }else if(field[i-1][j]!= NULL){
                    targetRows[j] = i;
                    targetCounter++;
                    break;
                }
            }
        }
    }

    for(i=0;i<7;i++){
        if(targetRows[i] >= 0){
            found = check4Win(targetRows[i],i,field);
        }
        if(found){
            emit moved(i);
            return;
        }
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
    //checks if targeted move would let the other player win and removes those targets
    for(i=0;i<7;i++){
        if(targetCounter > 1){
            if(targetRows[i] >= 0 && targetRows[i] < 5){
                field[targetRows[i]][i] = this;
                if(check4Lost(targetRows[i]+1, i, field)){
                    field[targetRows[i]][i] = NULL;
                    targetRows[i] = -1;
                    targetCounter--;
                }else{
                    field[targetRows[i]][i] = NULL;
                }
            }
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
// checks if the other player can finish with a chip in field[row][column] after the AiMove
bool AiPlayerGood::check4Lost(int row, int column, Player *field[6][7])
{
    // for the row
    int i;
    int counter = 0;
    for(i=0;i<7;i++){
        if(field[row][i]!=NULL){
            if(field[row][i] != this){
                counter++;
            }else{
                counter = 0;
            }
        }else if(i==column){
            if(counter >= 3){
                return true;
            }
            if(counter == 2 && column<6){
                if(field[row][column+1] != NULL){
                    if(field[row][column+1] != this){
                        return true;
                    }
                }
            }
            if(counter == 1 && column<5){
                if(field[row][column+1] != NULL && field[row][column+2] != NULL){
                    if(field[row][column+1] != this && field[row][column+2] != this){
                        return true;
                    }
                }
            }
            if(column<4){
                if(field[row][column+1] != NULL && field[row][column+2] != NULL && field[row][column+3]!= NULL){
                    if(field[row][column+1] != this && field[row][column+2] != this && field[row][column+3] != this){
                       return true;
                    }
                }
            }
        }else{
            counter = 0;
        }
    }
    //for the /-diagonal
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
            if(field[i][j] != this){
                counter++;
            }else{
                counter = 0;
            }
        }else if(i==row && j==column){
            if(counter >= 3){
                return true;
            }
            if(counter == 2 && column<6 && row<5){
                if(field[row+1][column+1] != NULL){
                    if(field[row+1][column+1] != this){
                        return true;
                    }
                }
            }
            if(counter == 1 && column<5 && row<4){
                if(field[row+1][column+1] != NULL && field[row+2][column+2] != NULL){
                    if(field[row+1][column+1] != this && field[row+2][column+2] != this){
                        return true;
                    }
                }
            }
            if(column<4 && row<3){
                if(field[row+1][column+1] != NULL && field[row+2][column+2] != NULL && field[row+3][column+3] != NULL){
                    if(field[row+1][column+1] != this && field[row+2][column+2] != this && field[row+3][column+3] != this){
                        return true;
                    }
                }
            }

        }else{
            counter = 0;
        }
    }
    //for the \-diagonal
    counter = 0;
    yAchsenSchnitt = row+column;
    if(yAchsenSchnitt < 6){
        i = yAchsenSchnitt;
        j = 0;
    }else{
        i = 5;
        j = yAchsenSchnitt-5;
    }
    for(;i>=0 && j<7;i--,j++){
        if(field[i][j]!= NULL){
            if(field[i][j] != this){
                counter++;
            }else{
                counter = 0;
            }
        }else if(i==row && j==column){
            if(counter >= 3){
                return true;
            }
            if(counter == 2 && column<6 && row>0){
                if(field[row-1][column+1] != NULL){
                    if(field[row-1][column+1] != this){
                        return true;
                    }
                }
            }
            if(counter == 1 && column<5 && row>1){
                if(field[row-1][column+1] != NULL && field[row-2][column+2] != NULL){
                    if(field[row-1][column+1] != this && field[row-2][column+2] != this){
                        return true;
                    }
                }
            }
            if(column<4 && row>2){
                if(field[row-1][column+1] != NULL && field[row-2][column+2] != NULL && field[row-3][column+3] != NULL){
                    if(field[row-1][column+1] != this && field[row-2][column+2] != this && field[row-3][column+3] != this){
                        return true;
                    }
                }
            }

        }else{
            counter = 0;
        }
    }
    return false;
}
