#include "GlChip.h"

#include <GL/glu.h>

GlChip::GlChip(QObject *parent)
    : GlObject(parent)
{
    m_color.setRgbF(1.0, 0.0, 0.0);
}

void GlChip::draw()
{
    // Colour cube data.
    static GLuint polyList = 0;

    GLUquadricObj *quadric;
    quadric = gluNewQuadric();


    if (!polyList) {
        polyList = glGenLists (1);
        glNewList(polyList, GL_COMPILE);

        gluDisk(quadric,0.0,0.4,32,32);
        gluCylinder(quadric, 0.4, 0.4, 0.1, 32, 32);
        glEndList ();
    }
    glPushMatrix(); // Save world coordinate system.
    glTranslatef(0.0, 0.0, 0.0); // Place base of chip on marker surface.
    //glRotatef(gDrawRotateAngle, 0.0, 0.0, 1.0); // Rotate about z axis.
    glDisable(GL_LIGHTING);	// Just use colours.
    glColor3f (m_color.redF(), m_color.greenF(), m_color.blueF());
    glCallList(polyList);	// Draw the cube.
    glPopMatrix();	// Restore world coordinate system.

}


const QColor GlChip::color() const
{
    return m_color;
}

void GlChip::setColor(const QColor& color)
{
    m_color = color;
}
