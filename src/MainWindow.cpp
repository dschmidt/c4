#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "GameWidget.h"
#include "GameModel.h"
#include "GameController.h"
#include "SettingsDialog.h"
#include "Settings.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
    , m_model(0)
    , m_controller(0)

{
    // instantiate settings once here
    new Settings(this);

    // acces them later on via instance()
    Settings* s = Settings::instance();

    qDebug() << "***** Current settings *****";
    qDebug() << "Player name" << s->playerName();
    qDebug() << "Player color" << s->playerColor();
    qDebug();
    qDebug() << "AI name" << s->aiName();
    qDebug() << "AI color" << s->aiColor();
    qDebug() << "AI level" << s->aiLevel();
    qDebug();
    qDebug() << "Camera width" << s->cameraWidth();
    qDebug() << "Camera height" << s->cameraHeight();
    qDebug();

    m_ui->setupUi(this);
    m_ui->statusbar->setVisible(false);

    //connect actions to functions
    connect(m_ui->actionExit, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));
    connect(m_ui->action640x480, SIGNAL(triggered()), this, SLOT(resolutionChange()));
    connect(m_ui->action800x600, SIGNAL(triggered()), this, SLOT(resolutionChange()));
    connect(m_ui->action1920x1080, SIGNAL(triggered()), this, SLOT(resolutionChange()));
    connect(m_ui->actionPlayer, SIGNAL(triggered()), this, SLOT(openSettingsDialog()));
    connect(m_ui->actionNew_Game, SIGNAL(triggered()), this, SLOT(newGame()));
    
    setupGame();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}


void MainWindow::setupGame()
{
    //load all options needed
    loadOptions();
    m_gameWidget = new GameWidget(this);
    m_model = new GameModel(this);
    m_controller = new GameController(this);

    m_controller->setGameModel(m_model);
    m_gameWidget->setGameModel(m_model);
    m_controller->setGameWidget(m_gameWidget);


    m_controller->startGame();

    setCentralWidget(m_gameWidget);
}

void MainWindow::resolutionChange()
{
    Settings* s = Settings::instance();
    //get calling action and extract height and weight
    QAction *caller = qobject_cast <QAction*>(sender());
    QString resolutionString = caller->text();
    size_t mid;
    mid = resolutionString.toStdString().find_first_of("x",0);
    s->setCameraWidth(resolutionString.left(static_cast<int>(mid)).toInt());
    s->setCameraHeight(resolutionString.remove(0,static_cast<unsigned int>(mid)+1).toInt());
    //uncheck actions and check choosen action
    resolutionString = caller->text();
    QList <QAction*> actionsToUncheck = m_ui->menuResolution->actions();
    actionsToUncheck.removeLast();
    for(int i = 0; i < actionsToUncheck.length(); i++)
    {
        qobject_cast <QAction*>(actionsToUncheck.at(i))->  setChecked(false);
    }
    caller->setChecked(true);
}

void MainWindow::openSettingsDialog()
{
    //create new SettingsDialog and open it
    SettingsDialog* playerSettings = new SettingsDialog(this);
    playerSettings->setModal(true);
    playerSettings->open();
}

void MainWindow::loadOptions()
{
    //load the resolution and check the right action in the mainwindow
    Settings* s = Settings::instance();
    QString resolutionString = QString("x").arg(s->cameraWidth());
    QList <QAction*> actionsToUncheck = m_ui->menuResolution->actions();
    actionsToUncheck.removeLast();
    for(int i = 0; i < actionsToUncheck.length(); i++){
        if (actionsToUncheck.at(i)->text().contains(resolutionString)){
            qobject_cast <QAction*>(actionsToUncheck.at(i))->setChecked(true);
        }
        else{
            qobject_cast <QAction*>(actionsToUncheck.at(i))->setChecked(false);}
    }
}

void MainWindow::newGame()
{
    m_model->resetField();
    m_controller->startGame();
}


