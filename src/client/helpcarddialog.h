#ifndef  HELPCARDDIALOG_H
#define HELPCARDDIALOG_H

#include <QtWidgets/QDialog>


namespace Ui {
class HelpCardDialog;
}

namespace client {
class HelpCardDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit HelpCardDialog(QWidget *parent = 0);
    virtual ~HelpCardDialog();
    
private:
    Ui::HelpCardDialog *ui;
};

}

#endif

