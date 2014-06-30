#include "GlField.h"
#include "GlChip.h"
#include "GameWidget.h"
#include "GameModel.h"

#include <QDebug>

GlField::GlField(QWidget* parent)
    : GlObject(parent)
{
}

void GlField::draw()
{
    static GLuint polyList = 0;
    float fSize = 0.5f;
    long f, i;

    GameWidget* widget = qobject_cast<GameWidget*>(parent());
    GameModel* model = widget ? widget->gameModel() : 0;

    if(model)
    {
        for (int y = 0; y < 6; y++)
        {
            for (int x = 0; x < 7; x++)
            {
                glPushMatrix();
                glTranslatef(float(x) - 3.0f, 0.5f, float(y) + 0.5f);
                glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

                if (model && model->field[y][x])
                {
                    GlChip drawingChip(this);
                    drawingChip.setColor(model->field[y][x]->color());
                    drawingChip.draw();
                }

                glPopMatrix();
            }
       }
   }

    const GLfloat field_vertices [32][3] = {
        //rear upper vertices
        {7.0, 0.50, 11.0}, {5.0, 0.50, 11.0}, {3.0, 0.50, 11.0}, {1.0, 0.50, 11.0},
        {-1.0, 0.50, 11.0}, {-3.0, 0.50, 11.0}, {-5.0, 0.50, 11.0}, {-7.0, 0.50, 11.0},

        //front upper vertices
        {-7.0, -0.50, 11.0}, {-5.0, -0.50, 11.0}, {-3.0, -0.50, 11.0}, {-1.0, -0.50, 11.0},
        {1.0, -0.50, 11.0}, {3.0, -0.50, 11.0}, {5.0, -0.50, 11.0}, {7.0, -0.50, 11.0},

        //rear lower vertices
        {7.0, 0.50, -1.0}, {5.0, 0.50, -1.0}, {3.0, 0.50, -1.0}, {1.0, 0.50, -1.0},
        {-1.0, 0.50, -1.0}, {-3.0, 0.50, -1.0}, {-5.0, 0.50, -1.0}, {-7.0, 0.50, -1.0},

        //front lower vertices
        {-7.0, -0.50, -1.0}, {-5.0, -0.50, -1.0}, {-3.0, -0.50, -1.0}, {-1.0, -0.50, -1.0},
        {1.0, -0.50, -1.0}, {3.0, -0.50, -1.0}, {5.0, -0.50, -1.0}, {7.0, -0.50, -1.0} };

    GLint field_num_faces = 29;
    const short field_faces [29][4] = {

        //1. column
        {9, 8, 24, 25}, {6, 7, 23, 22},
        //2. column
        {10, 9, 25, 26}, {5, 6, 22, 21},
        //3. column
        {11, 10, 26, 27}, {4, 5, 21, 20},
        //4. column
        {12, 11, 27, 28}, {3, 4, 20, 19},
        //5. column
        {13, 12, 28, 29}, {2, 3, 19, 18},
        //6. column
        {14, 13, 29, 30}, {1, 2, 18, 17},
        //7. column
        {15, 14, 30, 31}, {0, 1, 17, 16},

        //separating walls
        {0, 15, 31, 16},
        {1, 14, 30, 17},
        {2, 13, 29, 18},
        {3, 12, 28, 19},
        {4, 11, 27, 20},
        {5, 10, 26, 21},
        {6, 9, 25, 22},
        {7, 8, 24, 23},

        //bottom
        {16, 17, 30, 31},
        {17, 18, 29, 30},
        {18, 19, 28, 29},
        {19, 20, 27, 28},
        {20, 21, 26, 27},
        {21, 22, 25, 26},
        {22, 23, 24, 25},

    };

    if (!polyList) {
        polyList = glGenLists (1);
        glNewList(polyList, GL_COMPILE);

        glBegin (GL_QUADS);
        for (f = 14; f < field_num_faces; f++)
            for (i = 0; i < 4; i++) {
                glColor4f(0.137255, 0.137255, 0.556863, 0.650);
                glVertex3f(field_vertices[field_faces[f][i]][0] * fSize, field_vertices[field_faces[f][i]][1] * fSize, field_vertices[field_faces[f][i]][2] * fSize);
            }
        glEnd();

        glBegin (GL_QUADS);
        for (f = 0; f < 14 ; f=f+2)
            for (i = 0; i < 4; i++) {
                glColor4f(0.137255, 0.137255, 0.556863, 0.350);
                glVertex3f(field_vertices[field_faces[f][i]][0] * fSize, field_vertices[field_faces[f][i]][1] * fSize, field_vertices[field_faces[f][i]][2] * fSize);
            }
        glEnd();

        glBegin (GL_QUADS);
        for (f = 1; f < 14 ; f=f+2)
            for (i = 0; i < 4; i++) {
                glColor4f(0.137255, 0.137255, 0.556863, 0.250);
                glVertex3f(field_vertices[field_faces[f][i]][0] * fSize, field_vertices[field_faces[f][i]][1] * fSize, field_vertices[field_faces[f][i]][2] * fSize);

            }
        glEnd();

        glBegin (GL_LINE_LOOP);
        for (f = 0; f < field_num_faces; f++) {
            glColor3f (0.0, 0.0, 0.0);
            for (i = 0; i < 4; i++)
                glVertex3f(field_vertices[field_faces[f][i]][0] * fSize, field_vertices[field_faces[f][i]][1] * fSize, field_vertices[field_faces[f][i]][2] * fSize);
        }
        glEnd ();

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

void GlField::onHighlightColumn(int column)
{
    m_highlightedColumn = column;
}
