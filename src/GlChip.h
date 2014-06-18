#ifndef GLCHIP_H
#define GLCHIP_H

#include "GlObject.h"
#include <QColor>

class GlChip : public GlObject
{
public:
    GlChip();
    void draw();

private:
    QColor color;
};

#endif // GLCHIP_H
