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


        void crypted_networks_filter();

        void free_networks_filter();

        void all_networks_filter();

        void channel_filter();

        void show_setup();

};

#endif // MAINWINDOW_H
