#ifndef APPRENDREWINDOW_H
#define APPRENDREWINDOW_H

#include <QDialog>
#include <QAbstractButton>
#include <QDebug>

namespace Ui {
class ApprendreWindow;
}

class ApprendreWindow : public QDialog
{
    Q_OBJECT
    QString commandeApprendre;

public:
    explicit ApprendreWindow(QWidget *parent = 0);
    ~ApprendreWindow();
    QString getCommandeApprendre();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::ApprendreWindow *ui;
};

#endif // APPRENDREWINDOW_H
