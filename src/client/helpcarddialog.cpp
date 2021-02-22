#include <QApplication>
#include "parser/parser.h"
#include "helpcarddialog.h"
#include "ui_helpcarddialog.h"
#include "config.h"

using namespace client;

HelpCardDialog::HelpCardDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpCardDialog)
{
    ui->setupUi(this);
    setStyleSheet(styleSheet() + "\n"
        "#HelpCardDialog {\n"
        "   border-image: url(\"" + Config::dataPathString() + "gfx/cards/tutorial.png\")0 0 0 0 stretch stretch;\n"
        "}\n\n");
}

HelpCardDialog::~HelpCardDialog()
{
    delete ui;
}


