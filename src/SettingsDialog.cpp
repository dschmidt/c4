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

    s_ui->settingsNameTextbox->setText(Settings::instance()->playerName());
    s_ui->settingsColorButton->setStyleSheet("background-color: " + Settings::instance()->playerColor().name());
    s_ui->settingsAiColorButton->setStyleSheet("background-color: " + Settings::instance()->aiColor().name());
    s_ui->settingsAiBox->clear();
    QString aiNames = "Bob|Weak|Normal|Strong|Chuck Norris";
    QStringList aiList;
    aiList = aiNames.split("|");
    s_ui->settingsAiBox->addItems(aiList);

    connect(s_ui->settingsColorButton, SIGNAL(clicked()), this, SLOT(openColorDialog()));
    connect(s_ui->settingsAiColorButton, SIGNAL(clicked()), this, SLOT(openColorDialog()));
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
}

void SettingsDialog::cancel(){

}

void SettingsDialog::openColorDialog()
{
    QObject *caller = sender();
    QColorDialog* colorDialog = new QColorDialog(this);
    colorDialog->setModal(true);
    isAi = false;
    if (caller->objectName().contains("Ai"))
    {
        isAi = true;
    }
    connect(colorDialog, SIGNAL(colorSelected(QColor)), this, SLOT(setNewColor(QColor)));
    colorDialog->open();
}

void SettingsDialog::setNewColor(QColor color)
{
    {
        if(isAi)
        {
            Settings::instance()->setAiColor(color);
            if(Settings::instance()->aiColor().isValid())
            {
                s_ui->settingsAiColorButton->setStyleSheet("background-color: " + Settings::instance()->aiColor().name());
                return;
            }
        }
        Settings::instance()->setPlayerColor(color);
        if(Settings::instance()->playerColor().isValid())
            s_ui->settingsColorButton->setStyleSheet("background-color: " + Settings::instance()->playerColor().name());
    }
}
