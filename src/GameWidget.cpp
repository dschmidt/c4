#include "GameWidget.h"
#include "GlChip.h"
#include "GlField.h"
#include "Pattern.h"
#include "Player.h"
#include "GameModel.h"

#include <QDebug>
#include <QKeyEvent>

GameWidget::GameWidget(QWidget* parent)
    : ARToolkitWidget(parent)
    , m_model(0)
{
#ifdef ARTOOLKIT_FOUND
    pattChip = loadPattern("patt.hiro");
    pattField = loadPattern("patt.kanji");
    addPattern(pattChip);
    addPattern(pattField);

    chip = new GlChip();
    field = new GlField(this);
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

void GameWidget::timerEvent(QTimerEvent* event)
{
    ARToolkitWidget::timerEvent(event);
    if (pattField->found && pattChip->found)
    {
        double vect[3];
        double diff[3];
        // calculate relative position difference
        diff[0] = pattChip->trans[0][3] - pattField->trans[0][3];
        diff[1] = pattChip->trans[1][3] - pattField->trans[1][3];
        diff[2] = pattChip->trans[2][3] - pattField->trans[2][3];
        // apply transformation matrix from pattField to the vector
        vect[0] = pattField->trans[0][0] * diff[0] + pattField->trans[0][1] * diff[1] + pattField->trans[0][2] * diff[2];
        vect[1] = pattField->trans[1][0] * diff[0] + pattField->trans[1][1] * diff[1] + pattField->trans[1][2] * diff[2];
        vect[2] = pattField->trans[2][0] * diff[0] + pattField->trans[2][1] * diff[1] + pattField->trans[2][2] * diff[2];
        // print transformed vector to debug output
        qDebug() << Q_FUNC_INFO << vect[0] << " " << vect[1] << " " << vect[2];

        int column = (vect[0] + 100) / 28;
        if (vect[1] < 200 && column >= 0 && column <= 6)
        {
            if (!alreadyEmitted)
                emit arChipDropped(column);
            alreadyEmitted = true;
        }
        else
            alreadyEmitted = false;
    }
}

void GameWidget::keyPressEvent(QKeyEvent* event)
{
    int column = 0;
    switch(event->key())
    {
        case Qt::Key_1:
            column = 1;
            break;

        case Qt::Key_2:
            column = 2;
            break;

        case Qt::Key_3:
            column = 3;
            break;

        case Qt::Key_4:
            column = 4;
            break;

        case Qt::Key_5:
            column = 5;
            break;

        case Qt::Key_6:
            column = 6;
            break;

        case Qt::Key_7:
            column = 7;
            break;
    }

    if(column > 0) {
        qDebug() << "number pressed" << column;
        emit arChipDropped(column - 1);
    }
}

void GameWidget::setGameModel(GameModel* model)
{
    if(m_model){
        m_model->disconnect(this);
    }
    m_model = model;
    connect(m_model, SIGNAL(gameFinished(Player*)), SLOT(onGameFinished(Player*)));
}

void GameWidget::onGameFinished(Player *winner)
{
    if(winner != NULL){
        qDebug() << Q_FUNC_INFO << winner->name() << "won the game";
    }else{
        qDebug() << Q_FUNC_INFO << "Field is full...Game is over";
    }

}


GameModel* GameWidget::gameModel()
{
    return m_model;
}
