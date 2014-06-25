#include "GlChip.h"

#include <GL/glew.h>

GlChip::GlChip()
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

        glColor3f (m_color.redF(), m_color.greenF(), m_color.blueF());
        gluDisk(quadric,0.0,0.4,32,32);
        gluCylinder(quadric, 0.4, 0.4, 0.1, 32, 32);
        glEndList ();
    }
    glPushMatrix(); // Save world coordinate system.
    glTranslatef(0.0, 0.0, 0.5); // Place base of chip on marker surface.
    //glRotatef(gDrawRotateAngle, 0.0, 0.0, 1.0); // Rotate about z axis.
    glDisable(GL_LIGHTING);	// Just use colours.
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
