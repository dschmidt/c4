#ifndef GLFIELD_H
#define GLFIELD_H

#include "GlObject.h"

class Player;

class GameModel;

class GlField : public GlObject
{
    Q_OBJECT
public:
    GlField(QWidget *parent = 0);
    void draw();

public slots:
    void onDataChipDropped(bool success, int column, Player* currentPlayer);
};

#endif // GLFIELD_H
