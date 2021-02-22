#include <QApplication>
#include "parser/parser.h"
#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "config.h"

using namespace client;

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    loadConfigValues();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::loadConfigValues()
{
    Config& cfg = Config::instance();
    cfg.refresh();
    QString grp("game");
    ui->spinBox->setValue(cfg.readInt(grp, "card-size"));
    ui->lineEdit->setText(cfg.readString("player", "password"));
    ui->lineEdit_2->setText(cfg.readString("player", "name"));
}

void SettingsDialog::saveConfigValues()
{
    Config& cfg = Config::instance();
    QString grp("create-game-dialog");
    cfg.store();
}
