#include <QApplication>
#include <QDir>
#include "parser/parser.h"
#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "config.h"

using namespace client;

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog), is_opening(false)
{
    ui->setupUi(this);
    currentDir = QDir::current();
    ui->txt_logdir->setText(currentDir.absolutePath());

    connect(ui->lineEdit, SIGNAL(textChanged(const QString&)),
            this, SLOT(validateInput()));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::showEvent(QShowEvent* event) {
    if (is_opening) return;

    is_opening = true;
    QDialog::showEvent(event);
    loadConfigValues();
    is_opening = false;
}

void client::SettingsDialog::on_buttonOk_accepted()
{
    saveConfigValues();
}

void SettingsDialog::loadConfigValues()
{
    Config& cfg = Config::instance();
    cfg.refresh();
    QString grp("game");
    ui->spinBox->setValue(cfg.readInt(grp, "card-size"));
    ui->spinBoxZoom->setValue(cfg.readInt(grp, "card-zoom"));
    ui->lineEdit->setText(cfg.readString("player", "name"));
    ui->lineEdit_2->setText(cfg.readString("player", "password"));
    ui->checkBox->setChecked(cfg.readString("game", "fullscreen") == "true");
    ui->comboBox_2->setCurrentText(cfg.readString("game", "music"));
    ui->comboBox->setCurrentText(cfg.readString("game", "bgimage"));
}


void SettingsDialog::validateInput()
{
     ui->buttonOk->setEnabled(! ui->lineEdit->text().isEmpty());
}


void SettingsDialog::saveConfigValues()
{
    Config& cfg = Config::instance();
    cfg.writeString("player", "name", ui->lineEdit->text());
    cfg.writeString("player", "password", ui->lineEdit_2->text());

    cfg.writeString("game", "fullscreen", ui->checkBox->isChecked() ? "true" : "false");
    cfg.writeString("game", "music", ui->comboBox_2->currentText());
    cfg.writeString("game", "bgimage", ui->comboBox->currentText());
    cfg.writeInt("game", "card-size", ui->spinBox->value());
    cfg.writeInt("game", "card-zoom", ui->spinBoxZoom->value());

    cfg.store();
}

void client::SettingsDialog::on_pushButton_clicked()
{
  currentDir.setNameFilters(QStringList() << "*.log");
  currentDir.setFilter(QDir::Files);
  foreach(QString dirFile, currentDir.entryList())
  {
      currentDir.remove(dirFile);
  }
}
