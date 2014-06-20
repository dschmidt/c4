#include "GameWidget.h"
#include "GlChip.h"
#include "GlField.h"
#include "Pattern.h"

#include <QDebug>

GameWidget::GameWidget(QWidget* parent)
    : ARToolkitWidget(parent)
{
#ifdef ARTOOLKIT_FOUND
    pattChip = loadPattern("patt.hiro");
    pattField = loadPattern("patt.kanji");
    addPattern(pattChip);
    addPattern(pattField);

    chip = new GlChip();
    field = new GlField();
#endif
}

void GameWidget::drawObjects()
{
#ifdef ARTOOLKIT_FOUND
    GLdouble m[16];
    if (pattChip->found) {

        // Calculate the camera position relative to the marker.
        // Replace VIEW_SCALEFACTOR with 1.0 to make one drawing unit equal to 1.0 ARToolKit units (usually millimeters).
        arglCameraViewRH(pattChip->trans, m, VIEW_SCALEFACTOR);
        glLoadMatrixd(m);

        // All lighting and geometry to be drawn relative to the marker goes here.
        chip->draw();

    } // gPatt->found
    if (pattField->found) {

        // Calculate the camera position relative to the marker.
        // Replace VIEW_SCALEFACTOR with 1.0 to make one drawing unit equal to 1.0 ARToolKit units (usually millimeters).
        arglCameraViewRH(pattField->trans, m, VIEW_SCALEFACTOR);
        glLoadMatrixd(m);

        // All lighting and geometry to be drawn relative to the marker goes here.
        field->draw();

    } // gPatt->found
#endif
}

void GameWidget::mousePressEvent ( QMouseEvent * event )
{
    int column = qrand() * 6;

    qDebug() << Q_FUNC_INFO << column;

    //emit arChipDropped(column);
}
