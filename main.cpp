#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    #ifdef Q_WS_MAC
        QApplication::setGraphicsSystem("raster");
    #endif

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
