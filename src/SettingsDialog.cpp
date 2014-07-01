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

    s_ui->settingsNameTextbox->setText(s->playerName());
    s_ui->settingsColorButton->setColor(s->playerColor());

    s_ui->settingsAiColorButton->setColor(s->aiColor());

    s_ui->settingsAiBox->clear();
    QString aiNames = "Bob|Weak|Normal|Strong|Chuck Norris";
    QStringList aiList;
    aiList = aiNames.split("|");
    s_ui->settingsAiBox->addItems(aiList);

    connect(s_ui->buttonBox, SIGNAL(rejected()),this, SLOT(cancel()));
    connect(s_ui->buttonBox, SIGNAL(accepted()), this, SLOT(save()));
}


SettingsDialog::~SettingsDialog()
{
    delete s_ui;
}

void SettingsDialog::save()
{
    Settings::instance()->setPlayerName(s_ui->settingsNameTextbox->text());
    Settings::instance()->setAiLevel(s_ui->settingsAiBox->currentIndex());
    Settings::instance()->setPlayerColor(s_ui->settingsColorButton->color());
    Settings::instance()->setAiColor(s_ui->settingsAiColorButton->color());
}

void SettingsDialog::cancel(){

}
