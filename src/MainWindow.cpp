#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    connect(m_ui->actionExit, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));
}

MainWindow::~MainWindow()
{
    delete m_ui;
}
