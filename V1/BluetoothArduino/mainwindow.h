#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "device.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Device* d;
public:
    explicit MainWindow(Device* d, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked(bool checked);
    void redMajValues(float yaw, float ax, float ay, float az, float vx, float vy, float vz, float px, float py, float pz);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
