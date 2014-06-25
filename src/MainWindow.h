#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>

using namespace std;
namespace Ui {
class MainWindow;
}

class GameWidget;
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
    GameWidget*  m_gameWidget;
    GameModel* m_model;
    GameController* m_controller;
    QString activeResolutionWidth;
    QString activeResolutionHeight;
    QString playerName;
    int aiPlayer;
    QColor playerColor;

private slots:
    void resolutionChange();
    void openSettingsDialog();
    void saveOptions();
    void loadOptions();
};

#endif // MAINWINDOW_H
