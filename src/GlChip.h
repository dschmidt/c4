#ifndef GLCHIP_H
#define GLCHIP_H

#include "GlObject.h"
#include <QColor>

class GlChip : public GlObject
{
public:
    GlChip(QObject *parent = 0);
    void draw();

    const QColor color() const;
    void setColor(const QColor& color);

private:
    QColor m_color;
};

#endif // GLCHIP_H
