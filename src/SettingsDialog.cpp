#include "SettingsDialog.h"
#include "Settings.h"
#include "ui_SettingsDialog.h"

#include <QColorDialog>
#include <QStringList>
#include <QDebug>

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

    connect(s_ui->settingsP1Settings, SIGNAL(currentIndexChanged(int)), this, SLOT(onPlayerSettingsChanged()));
    connect(s_ui->settingsP2Settings, SIGNAL(currentIndexChanged(int)), this, SLOT(onPlayerSettingsChanged()));
    connect(s_ui->buttonBox, SIGNAL(rejected()),this, SLOT(cancel()));
    connect(s_ui->buttonBox, SIGNAL(accepted()), this, SLOT(save()));
}

SettingsDialog::~SettingsDialog()
{
    delete s_ui;
}

void SettingsDialog::onPlayerSettingsChanged()
{
    QComboBox *caller = qobject_cast <QComboBox*>(sender());
    QLineEdit *playerTextBox;
    if (caller == s_ui->settingsP1Settings){
        playerTextBox = s_ui->settingsName1Textbox;
    }
    else
    {
        playerTextBox = s_ui->settingsName2Textbox;
    }
    playerTextBox->setReadOnly(false);
    switch (caller->currentIndex())
    {
    case 1:
        playerTextBox->setText("Bob");
        break;
    case 2:
        playerTextBox->setText("Hilde");
        break;
    case 3:
        //AI Player Hard still missing
        playerTextBox->setText("Roger");
        break;
    case 4:
        //AI Player Chuck Norris still missing
        playerTextBox->setText("Chuck Norris");
        playerTextBox->setReadOnly(true);
        break;
    default:
        playerTextBox->setText("Player2");
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
