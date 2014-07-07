#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

private:
    Ui::SettingsDialog *s_ui;
    bool isAi;

private slots:
    void p2SettingsChanged();
    void cancel();
    void save();
};

#endif // SETTINGSDIALOG_H
