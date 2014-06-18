#include "GameWidget.h"
#include "GlChip.h"
#include "GlField.h"
#include "Pattern.h"

#include <QVector>

GameWidget::GameWidget(QWidget *parent) : ARToolkitWidget(parent)
{
    pattChip = loadPattern("patt.hiro");
    pattField = loadPattern("patt.kanji");
    addPattern(pattChip);
    addPattern(pattField);

    chip = new GlChip();
    field = new GlField();
}

void GameWidget::drawObjects()
{
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
}
