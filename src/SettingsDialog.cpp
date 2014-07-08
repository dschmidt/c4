#include "SettingsDialog.h"
#include "Settings.h"
#include "ui_SettingsDialog.h"

#include <QColorDialog>
#include <QStringList>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    s_ui(new Ui::SettingsDialog)
{
    s_ui->setupUi(this);

    Settings* s = Settings::instance();

    s_ui->settingsName1Textbox->setText(s->playerName());
    s_ui->settingsColor1Button->setColor(s->playerColor());
    s_ui->settingsName2Textbox->setText(s->aiName());
    s_ui->settingsColor2Button->setColor(s->aiColor());

    s_ui->settingsP1Settings->clear();
    s_ui->settingsP2Settings->clear();
    QStringList aiList = Settings::instance()->aiNameList().split("|");
    s_ui->settingsP1Settings->addItems(aiList);
    s_ui->settingsP1Settings->setCurrentIndex(s->playerLevel());

    s_ui->settingsP2Settings->addItems(aiList);
    s_ui->settingsP2Settings->setCurrentIndex(s->aiLevel());

    connect(s_ui->settingsP1Settings, SIGNAL(currentIndexChanged(int)), this, SLOT(onP1SettingsChanged()));
    connect(s_ui->settingsP2Settings, SIGNAL(currentIndexChanged(int)), this, SLOT(onP2SettingsChanged()));
    connect(s_ui->buttonBox, SIGNAL(rejected()),this, SLOT(cancel()));
    connect(s_ui->buttonBox, SIGNAL(accepted()), this, SLOT(save()));
}

SettingsDialog::~SettingsDialog()
{
    delete s_ui;
}

void SettingsDialog::onP2SettingsChanged()
{
    s_ui->settingsName2Textbox->setReadOnly(false);
    switch (s_ui->settingsP2Settings->currentIndex())
    {
        case 1:
            s_ui->settingsName2Textbox->setText("Bob");
            break;
        case 2:
            s_ui->settingsName2Textbox->setText("Hilde");
            break;
        case 3:
            //AI Player Hard still missing
            s_ui->settingsName2Textbox->setText("Roger");
            break;
        case 4:
            //AI Player Chuck Norris still missing
            s_ui->settingsName2Textbox->setText("Chuck Norris");
            s_ui->settingsName2Textbox->setReadOnly(true);
            break;
        default:
            s_ui->settingsName2Textbox->setText("Player2");
    }
}

void SettingsDialog::onP1SettingsChanged()
{
    s_ui->settingsName1Textbox->setReadOnly(false);
    switch (s_ui->settingsP1Settings->currentIndex())
    {
        case 1:
            s_ui->settingsName1Textbox->setText("Bob");
            break;
        case 2:
            s_ui->settingsName1Textbox->setText("Hilde");
            break;
        case 3:
            //AI Player Hard still missing
            s_ui->settingsName1Textbox->setText("Roger");
            break;
        case 4:
            //AI Player Chuck Norris still missing
            s_ui->settingsName1Textbox->setText("Chuck Norris");
            s_ui->settingsName1Textbox->setReadOnly(true);
            break;
        default:
            s_ui->settingsName1Textbox->setText("Player1");
    }
}

void SettingsDialog::save()
{
    //save playersettings for player1(player) und player2(ai) to settings
    Settings::instance()->setPlayerName(s_ui->settingsName1Textbox->text().replace("|",""));
    Settings::instance()->setAiName(s_ui->settingsName2Textbox->text().replace("|",""));
    Settings::instance()->setPlayerLevel(s_ui->settingsP1Settings->currentIndex());
    Settings::instance()->setAiLevel(s_ui->settingsP2Settings->currentIndex());
    Settings::instance()->setPlayerColor(s_ui->settingsColor1Button->color());
    Settings::instance()->setAiColor(s_ui->settingsColor2Button->color());
}

void SettingsDialog::cancel(){

}
