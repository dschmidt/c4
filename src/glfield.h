#ifndef GLFIELD_H
#define GLFIELD_H

#include "globject.h"

class Player;

class GlField : public GlObject
{
    Q_OBJECT
public:
    GlField();
    void draw();

public slots:
    void onDataChipDropped(bool success, int column, Player* currentPlayer);
};

#endif // GLFIELD_H
