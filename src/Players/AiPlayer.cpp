#include "AiPlayer.h"

#include <QDebug>
#include <ctime>

AiPlayer::AiPlayer(const QString& name, QObject* parent)
    : Player(name, parent)
{
}

void AiPlayer::move(Player* field[6][7])
{
    qDebug() << Q_FUNC_INFO;



    bool found = false;
    int i,j;
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
// checks if the AiPlayer can get 4 or avoid oponents 4 at field[row][column]
bool AiPlayer::check4(int row, int column, Player* field[6][7]){
    Player* tempPlayer = this;

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
            if(counter == 0){
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
            }
            if(counter == 2 && column<6){
                if(field[row][column+1] != NULL){
                    if(tempPlayer==field[row][column+1]){
                        return true;
                    }
                }
            }
            if(counter == 1 && column<5){
                if(field[row][column+1] != NULL && field[row][column+2] != NULL){
                    if(tempPlayer==field[row][column+1] && tempPlayer==field[row][column+2]){
                        return true;
                    }
                }
            }
            if(column<4){
                if(field[row][column+1] != NULL && field[row][column+2] != NULL && field[row][column+3]!= NULL){
                    tempPlayer = field[row][column+1];
                    if(tempPlayer==field[row][column+2] && tempPlayer==field[row][column+3]){
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
            if(counter == 0){
                tempPlayer = field[i][j];
                counter = 1;
            }else if(field[i][j] == tempPlayer){
                counter++;
            }else{
                counter = 1;
                tempPlayer = field[i][j];
            }
        }else if(i==row && j==column){
            if(counter >= 3){
                return true;
            }
            if(counter == 2 && column<6 && row<5){
                if(field[row+1][column+1] != NULL){
                    if(tempPlayer==field[row+1][column+1]){
                        return true;
                    }
                }
            }
            if(counter == 1 && column<5 && row<4){
                if(field[row+1][column+1] != NULL && field[row+2][column+2] != NULL){
                    if(tempPlayer==field[row+1][column+1] && tempPlayer==field[row+2][column+2]){
                        return true;
                    }
                }
            }
            if(column<4 && row<3){
                if(field[row+1][column+1] != NULL && field[row+2][column+2] != NULL && field[row+3][column+3] != NULL){
                    tempPlayer = field[row+1][column+1];
                    if(tempPlayer==field[row+2][column+2] && tempPlayer==field[row+3][column+3]){
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
            if(counter == 0){
                tempPlayer = field[i][j];
                counter = 1;
            }else if(field[i][j] == tempPlayer){
                counter++;
            }else{
                counter = 1;
                tempPlayer = field[i][j];
            }
        }else if(i==row && j==column){
            if(counter >= 3){
                return true;
            }
            if(counter == 2 && column<6 && row>0){
                if(field[row-1][column+1] != NULL){
                    if(tempPlayer==field[row-1][column+1]){
                        return true;
                    }
                }
            }
            if(counter == 1 && column<5 && row>1){
                if(field[row-1][column+1] != NULL && field[row-2][column+2] != NULL){
                    if(tempPlayer==field[row-1][column+1] && tempPlayer==field[row-2][column+2]){
                        return true;
                    }
                }
            }
            if(column<4 && row>2){
                if(field[row-1][column+1] != NULL && field[row-2][column+2] != NULL && tempPlayer==field[row-3][column+3]){
                    tempPlayer = field[row-1][column+1];
                    if(tempPlayer==field[row-2][column+2] && tempPlayer==field[row-3][column+3]){
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

bool AiPlayer::check4Win(int row, int column, Player* field[6][7])
{
    // for the column
    if(row > 2){
       if(field[row-1][column]==this && field[row-2][column]==this && field[row-3][column]==this){
           return true;
       }
    }
    // for the row
    int i;
    int counter = 0;
    for(i=0;i<7;i++){
        if(field[row][i]!=NULL){
            if(field[row][i] == this){
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
                    if(field[row][column+1] == this){
                        return true;
                    }
                }
            }
            if(counter == 1 && column<5){
                if(field[row][column+1] != NULL && field[row][column+2] != NULL){
                    if(field[row][column+1] == this && field[row][column+2] == this){
                        return true;
                    }
                }
            }
            if(column<4){
                if(field[row][column+1] != NULL && field[row][column+2] != NULL && field[row][column+3]!= NULL){
                    if(field[row][column+1] == this && field[row][column+2] == this && field[row][column+3] == this){
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
            if(field[i][j] == this){
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
                    if(field[row+1][column+1] == this){
                        return true;
                    }
                }
            }
            if(counter == 1 && column<5 && row<4){
                if(field[row+1][column+1] != NULL && field[row+2][column+2] != NULL){
                    if(field[row+1][column+1] == this && field[row+2][column+2] == this){
                        return true;
                    }
                }
            }
            if(column<4 && row<3){
                if(field[row+1][column+1] != NULL && field[row+2][column+2] != NULL && field[row+3][column+3] != NULL){
                    if(field[row+1][column+1] == this && field[row+2][column+2] == this && field[row+3][column+3] == this){
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
            if(field[i][j] == this){
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
                    if(field[row-1][column+1] == this){
                        return true;
                    }
                }
            }
            if(counter == 1 && column<5 && row>1){
                if(field[row-1][column+1] != NULL && field[row-2][column+2] != NULL){
                    if(field[row-1][column+1] == this && field[row-2][column+2] == this){
                        return true;
                    }
                }
            }
            if(column<4 && row>2){
                if(field[row-1][column+1] != NULL && field[row-2][column+2] != NULL && field[row-3][column+3] != NULL){
                    if(field[row-1][column+1] == this && field[row-2][column+2] == this && field[row-3][column+3] == this){
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
