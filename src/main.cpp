#include "src/headers/mainwindow.h"
#include "src/headers/queue.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.constructor();
    qDebug("showing window");
    w.show();
    qDebug("cancelling to show window");
    a.exec();
    qDebug("program cancelled");
    return 0;
}
