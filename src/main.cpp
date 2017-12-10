#include "mainwindow.h"
#include <QApplication>
#include <QFrame>
#include <QStyle>
#include <QDesktopWidget>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* main_window = new MainWindow;

    main_window->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            main_window->size(),
            qApp->desktop()->availableGeometry()
        )
    );
    main_window->setMinimumSize(800, 600);
    main_window->setMaximumSize(800, 600);
    main_window->show();

    return a.exec();
}
