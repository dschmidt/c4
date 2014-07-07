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

    s_ui->settingsP2Settings->clear();
    Settings::instance()->setAiNameList("reset");
    QStringList aiList = Settings::instance()->aiNameList().split("|");
    s_ui->settingsP2Settings->addItems(aiList);
    s_ui->settingsP2Settings->setCurrentIndex(s->aiLevel());
    connect(s_ui->settingsP2Settings, SIGNAL(currentIndexChanged(int)), this, SLOT(p2SettingsChanged()));
    connect(s_ui->buttonBox, SIGNAL(rejected()),this, SLOT(cancel()));
    connect(s_ui->buttonBox, SIGNAL(accepted()), this, SLOT(save()));
}

SettingsDialog::~SettingsDialog()
{
    delete s_ui;
}

void SettingsDialog::p2SettingsChanged()
{
    if (s_ui->settingsP2Settings->currentIndex() == 0)
    {
        s_ui->settingsName2Textbox->setReadOnly(false);
        s_ui->settingsName2Textbox->setText("Player2");
        return;
    }
    s_ui->settingsName2Textbox->setReadOnly(true);
    s_ui->settingsName2Textbox->setText(s_ui->settingsP2Settings->currentText());
}

void SettingsDialog::save()
{
    //save playername and ai-name to settings
    Settings::instance()->setPlayerName(s_ui->settingsName1Textbox->text().replace("|",""));
    Settings::instance()->setAiLevel(s_ui->settingsP2Settings->currentIndex());
    //QStringList aiList = Settings::instance()->aiNameList().split("|");
    //Settings::instance()->setAiName(aiList.at(s_ui->settingsAiBox->currentIndex()));
    Settings::instance()->setAiName(s_ui->settingsName2Textbox->text().replace("|",""));
    //save the colors in settings
    Settings::instance()->setPlayerColor(s_ui->settingsColor1Button->color());
    Settings::instance()->setAiColor(s_ui->settingsColor2Button->color());
}

void SettingsDialog::cancel(){

}
