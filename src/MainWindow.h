#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class ARToolkitWidget;
class GameModel;
class GameController;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void setupGame();

    Ui::MainWindow* m_ui;
    ARToolkitWidget*  m_gameWidget;
    GameModel* m_model;
    GameController* m_controller;
};

#endif // MAINWINDOW_H
