#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class GameWidget;
class GameModel;
class GameController;
class GameResult;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onGameFinishedWithResult(GameResult* result);

private:
    void setupGame();

    Ui::MainWindow* m_ui;
    GameWidget*  m_gameWidget;
    GameModel* m_model;
    GameController* m_controller;

private slots:
    void resolutionChange();
    void openSettingsDialog();
    void loadOptions();
    void newGame();
};

#endif // MAINWINDOW_H
