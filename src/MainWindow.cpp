#include "MainWindow.h"
#include "ui_MainWindow.h"


#include "ARToolkitWidget.h"
#include "GameModel.h"
#include "GameController.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
    , m_model(0)
    , m_controller(0)

{
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
    m_gameWidget = new ARToolkitWidget(this);
    m_model = new GameModel(this);
    m_controller = new GameController(this);


    m_controller->setGameModel(m_model);
    m_gameWidget->setGameModel(m_model);


    m_controller->startGame();

    setCentralWidget(m_gameWidget);
}
