#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H
#include <QDir>
#include <QtWidgets/QDialog>

namespace Ui {
class SettingsDialog;
}

namespace client {
class SettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SettingsDialog(QWidget *parent = 0);
    virtual ~SettingsDialog();
    
private slots:
    void on_buttonOk_accepted();
    void validateInput();

    void on_pushButton_clicked();

private:
    void showEvent(QShowEvent* event);
    void saveConfigValues();
    void loadConfigValues();

    Ui::SettingsDialog *ui;
    bool is_opening;
    QDir currentDir;
};
}
#endif // SETTINGSDIALOG_H
