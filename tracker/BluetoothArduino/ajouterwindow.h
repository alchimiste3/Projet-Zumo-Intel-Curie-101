#ifndef AJOUTERWINDOW_H
#define AJOUTERWINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QDebug>

#include "action.h"

namespace Ui {
class AjouterWindow;
}

class AjouterWindow : public QDialog
{
    Q_OBJECT
    Action* a;

public:
    explicit AjouterWindow(QWidget *parent = 0);
    ~AjouterWindow();
    Action* getAction();

private slots:

    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::AjouterWindow *ui;
};

#endif // AJOUTERWINDOW_H
