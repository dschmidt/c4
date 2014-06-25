#include "MainWindow.h"
#include "ui_MainWindow.h"


#include "GameWidget.h"
#include "GameModel.h"
#include "GameController.h"
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

    connect(m_ui->actionExit, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));

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
