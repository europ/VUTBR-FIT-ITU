#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "analyser.hpp"
#include <QLine>
#include <QDebug>
#include <QTimer>
#include <QFrame>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MainWindow *new_window;

private slots:
        //slot for button 2
        void button2_press();

        void button3_press();

        void update();

        void show_network_info();
};

#endif // MAINWINDOW_H
