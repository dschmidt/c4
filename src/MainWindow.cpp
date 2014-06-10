#include "MainWindow.h"
#include "ui_MainWindow.h"


#include "ARToolkitWidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);


    connect(m_ui->actionExit, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));

    m_gameWidget = new ARToolkitWidget(this);
    setCentralWidget(m_gameWidget);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}
