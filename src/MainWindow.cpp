#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "GameWidget.h"
#include "GameModel.h"
#include "GameController.h"
#include "SettingsDialog.h"
#include "Settings.h"
#include "GameResult.h"

#include <QDebug>
#include <QMessageBox>

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

    /*qDebug() << "***** Current settings *****";
    qDebug() << "Player name" << s->playerName();
    qDebug() << "Player color" << s->playerColor();
    qDebug();
    qDebug() << "AI name" << s->aiName();
    qDebug() << "AI color" << s->aiColor();
    qDebug() << "AI level" << s->aiLevel();
    qDebug();*/

    m_ui->setupUi(this);
    m_ui->statusbar->setVisible(false);

    //connect actions to functions
    connect(m_ui->actionExit, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));
    connect(m_ui->action640x480, SIGNAL(triggered()), this, SLOT(resolutionChange()));
    connect(m_ui->action800x600, SIGNAL(triggered()), this, SLOT(resolutionChange()));
    connect(m_ui->action1920x1080, SIGNAL(triggered()), this, SLOT(resolutionChange()));
    connect(m_ui->actionPlayer, SIGNAL(triggered()), this, SLOT(openSettingsDialog()));
    connect(m_ui->actionNew_Game, SIGNAL(triggered()), this, SLOT(newGame()));

    connect(m_ui->actionQuicksave, SIGNAL(triggered()), this, SLOT(quickSave()));
    connect(m_ui->actionQuickload, SIGNAL(triggered()), this, SLOT(quickLoad()));
    connect(m_ui->actionImpressum_2, SIGNAL(triggered()), this, SLOT(showImpressum()));
    connect(m_ui->actionHow_to_play, SIGNAL(triggered()), this, SLOT(showRules()));

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
    connect(m_model, SIGNAL(gameFinishedWithResult(GameResult*)), SLOT(onGameFinishedWithResult(GameResult*)));

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
    QString resolutionString = QString::number(s->cameraWidth(),10).append("x");
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
    m_controller->restartGame();
}

void MainWindow::onGameFinishedWithResult(GameResult *result)
{
    QString resultString("%1 wins");
    if(result->winner)
    {
        resultString = resultString.arg(result->winner->name());
    }
    else
    {
        resultString = resultString.arg("Noone");
    }

    m_ui->resultWidget->addItem(new QListWidgetItem(resultString, m_ui->resultWidget));


    m_ui->player1Label->setText(QString("%1: %2").arg(result->player1->name()).arg(m_model->wins(result->player1)));
    m_ui->player2Label->setText(QString("%1: %2").arg(result->player2->name()).arg(m_model->wins(result->player2)));

    m_controller->restartGame();
}

void MainWindow::quickSave()
{
    Settings::instance()->setSaveGame(m_controller->saveGame());
    qDebug()<< "Game saved!";
}

void MainWindow::quickLoad()
{
    QStringList saveGame = Settings::instance()->saveGame().split("|");
    if ((saveGame.length() < 3)||(saveGame.at(3).length() < 42)){
        return;
    }
    m_controller->loadGame(saveGame.at(3), saveGame.at(0)+"|"+saveGame.at(1), saveGame.at(2).toInt(0,10));
    qDebug()<< ("load complete: Players: " + saveGame.at(0) + " vs " + saveGame.at(1));
}

void MainWindow::showRules()
{
    QMessageBox::information(this, "Rules", "http://en.wikipedia.org/wiki/Connect_Four",QMessageBox::Default, QMessageBox::Default);
}

void MainWindow::showImpressum()
{
    QMessageBox::information(this, "Impressum", "Fachprojekt:Visual Computing",QMessageBox::Default, QMessageBox::Default);
}
