#ifndef GLOBJECT_H
#define GLOBJECT_H

#include <QObject>

class GlObject : public QObject
{
    Q_OBJECT
public:
    GlObject();

    virtual void draw() = 0;
};

#endif // GLOBJECT_H
