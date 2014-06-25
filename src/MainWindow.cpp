#include "MainWindow.h"
#include "ui_MainWindow.h"


#include "GameWidget.h"
#include "GameModel.h"
#include "GameController.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <string>
#include <iostream>
#include <sstream>
#include "settingsDialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
    , m_model(0)
    , m_controller(0)

{
    m_ui->setupUi(this);
    m_ui->statusbar->setVisible(false);

    connect(m_ui->actionExit, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));
    connect(m_ui->action640x480, SIGNAL(triggered()), this, SLOT(resolutionChange()));
    connect(m_ui->action800x600, SIGNAL(triggered()), this, SLOT(resolutionChange()));
    connect(m_ui->action1920x1080, SIGNAL(triggered()), this, SLOT(resolutionChange()));
    connect(m_ui->actionSave, SIGNAL(triggered()), this, SLOT(saveOptions()));
    connect(m_ui->actionPlayer, SIGNAL(triggered()), this, SLOT(openSettingsDialog()));
    loadOptions();

    setupGame();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}


void MainWindow::setupGame()
{
    m_gameWidget = new GameWidget(this);
    m_model = new GameModel(this);
    m_controller = new GameController(this);


    m_controller->setGameModel(m_model);
    m_gameWidget->setGameModel(m_model);

    m_controller->setGameWidget(m_gameWidget);


    m_controller->startGame();

    setCentralWidget(m_gameWidget);
}

void MainWindow::resolutionChange(){
    QAction *caller = qobject_cast <QAction*>(sender());
    QString resolutionString = caller->text();
    size_t mid;
    mid = resolutionString.toStdString().find_first_of("x",0);
    activeResolutionWidth = resolutionString.left(static_cast<unsigned int>(mid));
    activeResolutionHeight = resolutionString.remove(0,static_cast<unsigned int>(mid)+1);
    resolutionString = caller->text();
    QList <QAction*> actionsToUncheck = m_ui->menuResolution->actions();
    actionsToUncheck.removeLast();
    for(unsigned int i = 0; i < actionsToUncheck.length(); i++){
        qobject_cast <QAction*>(actionsToUncheck.at(i))->  setChecked(false);
    }
    caller->setChecked(true);
    //Fenser neu initialisieren mit neuer Auflösung!
}

void MainWindow::openSettingsDialog(){
    string name = playerName.toStdString();
    //Dialogbox definieren und enthaltene Elemente eintragen
    CustomDialog playerSettings("Player options", this);
    playerSettings.addLabel("Change your options");
    playerSettings.addLineEdit("Playername: ", &name, "Insert the name your want to have");
    playerSettings.addColorSel("Playercolor: ",&playerColor, "Choose the Color of your chips");
    playerSettings.addComboBox("Ai Player: ", "Bob|Easy|Normal|Hard|ChuckNorris", &aiPlayer);

    playerSettings.exec();//Warten bis der Spieler den Dialog wieder schließt

    if(playerSettings.wasCancelled()){
        return;
    }
    else{
        //Variablen übertragen falls nötig
        playerName.fromStdString(name);
    }
}

void MainWindow::loadOptions(){
    //QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"), "",tr("Data Text (*.txt);;All Files (*)"));
    QString fileName = fileName.fromStdString("Options.txt");
    //Voreinstellungen für den Laden_Dialog
    if (fileName.isEmpty()){
        //Wenn Datei leer Standarddaten laden
        activeResolutionWidth.fromStdString("640");
        activeResolutionHeight.fromStdString("480");
        playerName.fromStdString("Knalltuete");
        playerColor.setNamedColor("Red");
        aiPlayer = 1;
    }
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            //Bei Fehler Fehlerdialog ausgeben
            QMessageBox::information(this, tr("Unable to open file"),file.errorString());
            //Wenn Fehler beim laden der Datei Standarddateien laden
            activeResolutionWidth.fromStdString("640");
            activeResolutionHeight.fromStdString("480");
            playerName.fromStdString("Knalltuete");
            playerColor.setNamedColor("Red");
            aiPlayer = 1;

        }
        else{
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_4_8);

        //Einlesen der Daten in die Variablen, Reihenfolge des entscheidend!
        in >> activeResolutionWidth;
        in >> activeResolutionHeight;
        in >> playerName;
        QString helper;
        in >> helper;
        playerColor.setNamedColor(helper);
        in >> helper;
        aiPlayer = helper.toInt();
        }
    }
    //Checken der Actionen im Dropdown Menue
    QList <QAction*> actionsToUncheck = m_ui->menuResolution->actions();
    actionsToUncheck.removeLast();
    for(unsigned int i = 0; i < actionsToUncheck.length(); i++){
        qobject_cast <QAction*>(actionsToUncheck.at(i))-> setChecked(false);
        if ((qobject_cast <QAction*>(actionsToUncheck.at(i))->text().contains(activeResolutionWidth))&&(qobject_cast <QAction*>(actionsToUncheck.at(i))->text().contains(activeResolutionHeight))){
            qobject_cast <QAction*>(actionsToUncheck.at(i))-> setChecked(true);
        }
    }
}

void MainWindow::saveOptions(){
    //QString fileName = QFileDialog::getSaveFileName(this,tr("Save File"), "",tr("Data Text (*.txt);;All Files (*)"));
    QString fileName = fileName.fromStdString("Options.txt");
    if (fileName.isEmpty()){
        return;              }
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            //Bei Fehler Fehlerdialog ausgeben
            QMessageBox::information(this, tr("Unable to open file"),file.errorString());
            return;
        }
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_4_8);

        playerName.fromStdString("Knalltuete");
        //Variablen in den Outputstream jagen, in der Reihenfolge wie sie geladen werden
        QString helper;
        out << activeResolutionWidth;
        out << activeResolutionHeight;
        out << playerName;
        out << playerColor.name();
        out << helper.number(aiPlayer);
    }
}
