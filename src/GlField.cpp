#include "GlField.h"

#include <GL/glew.h>

GlField::GlField()
{
}

void GlField::draw()
{
    static GLuint polyList = 0;
    float fSize = 0.5f;
    long f, i;
    const GLfloat field_vertices [8][3] = {
        {7.0, 0.50, 5.0}, {7.0, -0.50, 5.0}, {-7.0, -0.50, 5.0}, {-7.0, 0.50, 5.0},
        {7.0, 0.50, -1.0}, {7.0, -0.50, -1.0}, {-7.0, -0.5, -1.0}, {-7.0, 0.5, -1.0} };

    const GLfloat field_vertices2 [56][3] = {
        {7.0, 0.50, 5.0}, {7.0, -0.50, 5.0}, {5.0, -0.50, 5.0}, {5.0, 0.50, 5.0},
        {7.0, 0.50, -1.0}, {7.0, -0.50, -1.0}, {5.0, -0.5, -1.0}, {5.0, 0.5, -1.0},

        {5.0, 0.50, 5.0}, {5.0, -0.50, 5.0}, {3.0, -0.50, 5.0}, {3.0, 0.50, 5.0},
        {5.0, 0.50, -1.0}, {5.0, -0.50, -1.0}, {3.0, -0.5, -1.0}, {3.0, 0.5, -1.0},

        {3.0, 0.50, 5.0}, {3.0, -0.50, 5.0}, {1.0, -0.50, 5.0}, {1.0, 0.50, 5.0},
        {3.0, 0.50, -1.0}, {3.0, -0.50, -1.0}, {1.0, -0.5, -1.0}, {1.0, 0.5, -1.0},

        {1.0, 0.50, 5.0}, {1.0, -0.50, 5.0}, {-1.0, -0.50, 5.0}, {-1.0, 0.50, 5.0},
        {1.0, 0.50, -1.0}, {1.0, -0.50, -1.0}, {-1.0, -0.5, -1.0}, {-1.0, 0.5, -1.0},

        {-1.0, 0.50, 5.0}, {-1.0, -0.50, 5.0}, {-3.0, -0.50, 5.0}, {-3.0, 0.50, 5.0},
        {-1.0, 0.50, -1.0}, {-1.0, -0.50, -1.0}, {-3.0, -0.5, -1.0}, {-3.0, 0.5, -1.0},

        {-3.0, 0.50, 5.0}, {-3.0, -0.50, 5.0}, {-5.0, -0.50, 5.0}, {-5.0, 0.50, 5.0},
        {-3.0, 0.50, -1.0}, {-3.0, -0.50, -1.0}, {-5.0, -0.5, -1.0}, {-5.0, 0.5, -1.0},

        {-5.0, 0.50, 5.0}, {-5.0, -0.50, 5.0}, {-7.0, -0.50, 5.0}, {-7.0, 0.50, 5.0},
        {-5.0, 0.50, -1.0}, {-5.0, -0.50, -1.0}, {-7.0, -0.5, -1.0}, {-7.0, 0.5, -1.0} };


    GLint field_num_faces = 6;
    const short field_faces [6][4] = {
    {3, 2, 1, 0}, {2, 3, 7, 6}, {0, 1, 5, 4}, {3, 0, 4, 7}, {1, 2, 6, 5}, {4, 5, 6, 7} };
    GLint field_num_faces2 = 35;
    const short field_faces2 [35][4] = {
    //{3, 2, 1, 0},
        {2, 3, 7, 6}, {0, 1, 5, 4}, {3, 0, 4, 7}, {1, 2, 6, 5},
        {4, 5, 6, 7},
    //{11, 10, 9, 8},
        {10, 11, 15, 14}, {8, 9, 13, 12}, {11, 8, 12, 15}, {9, 10, 14, 13},
        {12, 13, 14, 15},
    //{19, 18, 17, 16},
        {18, 19, 23, 22}, {16, 17, 21, 20}, {19, 16, 20, 23}, {17, 18, 22, 21},
        {20, 21, 22, 23},
    //{27, 26, 25, 24},
        {26, 27, 31, 30}, {24, 25, 29, 28}, {27, 24, 28, 31}, {25, 26, 30, 29},
        {28, 29, 30, 31},
    //{35, 34, 33, 32},
        {34, 35, 39, 38}, {32, 33, 37, 36}, {35, 32, 36, 39}, {33, 34, 38, 37},
        {36, 37, 38, 39},
    //{43, 42, 41, 40},
        {42, 43, 47, 46}, {40, 41, 45, 44}, {43, 40, 44, 47}, {41, 42, 46, 45},
        {44, 45, 46, 47},
    //{51, 50, 49, 48},
        {50, 51, 55, 54}, {48, 49, 53, 52}, {51, 48, 52, 55}, {49, 50, 54, 53},
        {52, 53, 54, 55},


    };

    if (!polyList) {
        polyList = glGenLists (1);
        glNewList(polyList, GL_COMPILE);

        glColor3f (0.0, 0.0, 0.0);
        for (f = 0; f < field_num_faces2; f++) {
            glBegin (GL_LINE_LOOP);
            for (i = 0; i < 4; i++)
                glVertex3f(field_vertices2[field_faces2[f][i]][0] * fSize, field_vertices2[field_faces2[f][i]][1] * fSize, field_vertices2[field_faces2[f][i]][2] * fSize);
            glEnd ();
        }

        glBegin (GL_QUADS);

        for (f = 4; f < field_num_faces2; f=f+5)
            for (i = 0; i < 4; i++) {
                glColor4f(0.137255, 0.137255, 0.556863, 0.950);
                glVertex3f(field_vertices2[field_faces2[f][i]][0] * fSize, field_vertices2[field_faces2[f][i]][1] * fSize, field_vertices2[field_faces2[f][i]][2] * fSize);
            }
        for (f = 0; f < field_num_faces2; f=f+5)
            for (i = 0; i < 4; i++) {
                glColor4f(0.137255, 0.137255, 0.556863, 0.650);
                glVertex3f(field_vertices2[field_faces2[f][i]][0] * fSize, field_vertices2[field_faces2[f][i]][1] * fSize, field_vertices2[field_faces2[f][i]][2] * fSize);
            }
        for (f = 1; f < field_num_faces2; f=f+5)
            for (i = 0; i < 4; i++) {
                glColor4f(0.137255, 0.137255, 0.556863, 0.650);
                glVertex3f(field_vertices2[field_faces2[f][i]][0] * fSize, field_vertices2[field_faces2[f][i]][1] * fSize, field_vertices2[field_faces2[f][i]][2] * fSize);
            }
        for (f = 0; f < field_num_faces2; f++)
            for (i = 0; i < 4; i++) {
                glColor4f(0.137255, 0.137255, 0.556863, 0.350);
                glVertex3f(field_vertices2[field_faces2[f][i]][0] * fSize, field_vertices2[field_faces2[f][i]][1] * fSize, field_vertices2[field_faces2[f][i]][2] * fSize);
            }
        glEnd ();

        glColor3f (0.0, 0.0, 0.0);
        for (f = 0; f < field_num_faces; f++) {
            glBegin (GL_LINE_LOOP);
            for (i = 0; i < 4; i++)
                glVertex3f(field_vertices[field_faces[f][i]][0] * fSize, field_vertices[field_faces[f][i]][1] * fSize, field_vertices[field_faces[f][i]][2] * fSize);
            glEnd ();
        }

        glEndList ();
    }

    glPushMatrix(); // Save world coordinate system.
    glTranslatef(0.0, 0.0, 0.5); // Place base of field on marker surface.
//    glRotatef(gDrawRotateAngle, 0.0, 0.0, 1.0); // Rotate about z axis.
    glDisable(GL_LIGHTING);	// Just use colours.
    glCallList(polyList);	// Draw the field.
    glPopMatrix();	// Restore world coordinate system.

}

void GlField::onDataChipDropped(bool success, int column, Player *currentPlayer)
{

}
