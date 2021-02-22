#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

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
    void loadConfigValues();
    void saveConfigValues();
    
private:
    Ui::SettingsDialog *ui;
};
}
#endif // SETTINGSDIALOG_H
