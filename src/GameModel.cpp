#include "GameModel.h"
#include "GameResult.h"

#include <QDebug>

GameModel::GameModel(QObject *parent)
    : QObject(parent)
    , m_player1(0)
    , m_player2(0)
    , m_gameFinished(false)
{
    resetField();

    connect(this, SIGNAL(gameFinished(Player*)), SLOT(onGameFinished(Player*)));
}

GameModel::~GameModel()
{
    qDeleteAll(m_results);
}

Player* GameModel::player1() const
{
    return m_player1;
}

void GameModel::setPlayer1(Player *player1)
{
    m_player1 = player1;
}

Player* GameModel::player2() const
{
    return m_player2;
}

void GameModel::setPlayer2(Player *player2)
{
    m_player2 = player2;
}

void GameModel::resetField()
{
    m_gameFinished = false;

    for(int i=0;i<6;i++){
        for(int j=0;j<7;j++){
            field[i][j] = NULL;
        }
    }
}

void GameModel::dropChip(int column, Player *currentPlayer)
{
    if(m_gameFinished) {
         emit dataChipDropped(false, column, currentPlayer);
        return;
    }

    // ChipDrop failed if column is full
    if(field[5][column] != NULL){
        emit dataChipDropped(false, column, currentPlayer);
        return;
    }
    // drop the chip
    int i,row;
    for(i=0;i<6;i++){
        if(field[i][column] == NULL){
            row = i;
            break;
        }
    }
    field[row][column] = currentPlayer;
    emit dataChipDropped(true, column, currentPlayer);
    // check for finished game
    if(checkFinished(row, column, currentPlayer)){
        emit gameFinished(currentPlayer);
        return;
    }
    bool isFull = true;
    for(i=0;i<7;i++){
        if(field[5][i] == NULL){
            isFull = false;
            break;
        }
    }
    if(isFull){
        emit gameFinished(NULL);
    }
}

bool GameModel::checkFinished(int row, int column, Player *currentPlayer){

    // for the column
    if(row > 2){
       if(field[row-1][column]==currentPlayer && field[row-2][column]==currentPlayer && field[row-3][column]==currentPlayer){
           return true;
       }
    }

    // for the row
    int i;
    int counter = 0;
    for(i=0;i<7;i++){
        if(field[row][i]!=NULL){
            if(currentPlayer == field[row][i]){
                counter++;
                if(counter == 4){
                    return true;
                }
            }else{
                counter = 0;
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
            if(field[i][j] == currentPlayer){
                counter++;
                if(counter == 4){
                    return true;
                }
            }else{
                counter = 0;
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
            if(field[i][j] == currentPlayer){
                counter++;
                if(counter == 4){
                    return true;
                }
            }else{
                counter = 0;
            }
        }else{
            counter = 0;
        }
    }


    return false;
}


void GameModel::onGameFinished(Player* winner)
{
    m_gameFinished = true;

    GameResult* result = new GameResult;
    result->player1 = m_player1;
    result->player2 = m_player2;
    result->winner = winner;
    m_results.append(result);

    emit gameFinishedWithResult(result);
}

int GameModel::wins(Player* player) const
{
    int wins = 0;
    foreach(GameResult* currentResult, m_results)
    {
        if(currentResult->winner == player)
        {
            wins++;
        }
    }

    return wins;
}

QString GameModel::getGame(){
    QString fieldSave;
    for(int i=0;i<6;i++){
        for(int j=0;j<7;j++){
            if(field[i][j] == NULL)
            {
                fieldSave.append("0");
            }
            else if (field[i][j] == player2())
            {
                fieldSave.append("2");
            }
            else
            {
                fieldSave.append("1");
            }
        }
    }
    return fieldSave;
}

void GameModel::setGame(QString saveGame){
    QString helper = saveGame.left(1);
    for(int i=0;i<6;i++){
        for(int j=0;j<7;j++){
            if(helper.toInt(0,10) == 0)
            {
                field[i][j] = NULL;
                saveGame.remove(0,1);
                helper = saveGame.left(1);
            }
            else if (helper.toInt(0,10) == 2)
            {
                field[i][j] = player2();
                saveGame.remove(0,1);
                helper = saveGame.left(1);
            }
            else
            {
                field[i][j] = player1();
                saveGame.remove(0,1);
                helper = saveGame.left(1);
            }
        }
    }
}
