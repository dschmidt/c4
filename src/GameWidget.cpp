#include "GameWidget.h"
#include "GlChip.h"
#include "GlField.h"
#include "Pattern.h"

GameWidget::GameWidget(QWidget *parent) : ARToolkitWidget(parent)
{
    pattChip = loadPattern("patt.hiro");
    pattField = loadPattern("patt.kanji");
    addPattern(pattChip);
    addPattern(pattField);

    chip = new GlChip();
    field = new GlField();
}

//void GameWidget::drawObjects()
//{
//    if (pattChip->found)
//        chip->draw();
//    if (pattField->found)
//        field->draw();
//}
